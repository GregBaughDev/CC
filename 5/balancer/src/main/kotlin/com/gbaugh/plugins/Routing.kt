package com.gbaugh.plugins

import com.auth0.jwk.JwkProviderBuilder
import com.auth0.jwt.JWT
import com.auth0.jwt.algorithms.Algorithm
import com.gbaugh.forwarder.Forwarder
import io.ktor.client.call.*
import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.http.content.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import kotlinx.coroutines.runBlocking
import java.io.File
import java.security.KeyFactory
import java.security.interfaces.RSAPrivateKey
import java.security.interfaces.RSAPublicKey
import java.security.spec.PKCS8EncodedKeySpec
import java.util.*
import java.util.concurrent.TimeUnit

fun Application.configureRouting(forwarder: Forwarder) {
    val privateKeyString = "MIIBVQIBADANBgkqhkiG9w0BAQEFAASCAT8wggE7AgEAAkEAtfJaLrzXILUg1U3N1KV8yJr92GHn5OtYZR7qWk1Mc4cy4JGjklYup7weMjBD9f3bBVoIsiUVX6xNcYIr0Ie0AQIDAQABAkEAg+FBquToDeYcAWBe1EaLVyC45HG60zwfG1S4S3IB+y4INz1FHuZppDjBh09jptQNd+kSMlG1LkAc/3znKTPJ7QIhANpyB0OfTK44lpH4ScJmCxjZV52mIrQcmnS3QzkxWQCDAiEA1Tn7qyoh+0rOO/9vJHP8U/beo51SiQMw0880a1UaiisCIQDNwY46EbhGeiLJR1cidr+JHl86rRwPDsolmeEF5AdzRQIgK3KXL3d0WSoS//K6iOkBX3KMRzaFXNnDl0U/XyeGMuUCIHaXv+n+Brz5BDnRbWS+2vkgIe9bUNlkiArpjWvX+2we"
    val issuer = "http://localhost:8080"
    val audience = "[http://localhost:8081, http://localhost:8082, http://localhost:8083, http://localhost:8084]"
    val jwkProvider = JwkProviderBuilder(issuer)
        .cached(10, 30, TimeUnit.SECONDS)
        .build()

    routing {
        get("/") {
            val publicKey = jwkProvider.get("6f8856ed-9189-488f-9011-0ff4b6c08edc").publicKey
            val keySpecPKCS8 = PKCS8EncodedKeySpec(Base64.getDecoder().decode(privateKeyString))
            val privateKey = KeyFactory.getInstance("RSA").generatePrivate(keySpecPKCS8)
            val token = JWT.create()
                .withAudience(audience)
                .withIssuer(issuer)
                .withExpiresAt(Date(System.currentTimeMillis() + 60000))
                .sign(Algorithm.RSA256(publicKey as RSAPublicKey, privateKey as RSAPrivateKey))

            runBlocking {
                forwarder.sendRequest(token).let {
                    if (it.status.isSuccess()) {
                        call.respondText(it.body(), ContentType.Text.Html)
                    } else {
                        call.respond(HttpStatusCode.BadRequest)
                    }
                }
            }
        }
        staticFiles(".well-known", File("certs"), "jwks.json")
    }
}


