package com.gbaugh.plugins

import com.auth0.jwk.JwkProviderBuilder
import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.auth.jwt.*
import io.ktor.server.response.*

fun Application.configureSecurity() {
    // The below should be in env var but I'm unable to run multiple servers
    // through the use of application.conf
    val issuer = "http://localhost:8080"
    val jwkProvider = JwkProviderBuilder(issuer).build()

    install(Authentication) {
        jwt("auth-jwt") {
            verifier(jwkProvider, issuer) {
                acceptLeeway(3)
            }
            validate { credential ->
                JWTPrincipal(credential.payload)
            }
            challenge { defaultScheme, realm ->
                call.respond(HttpStatusCode.Unauthorized, "Token not valid")
            }
        }
    }
}