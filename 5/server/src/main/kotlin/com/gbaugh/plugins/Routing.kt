package com.gbaugh.plugins

import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.html.*
import io.ktor.server.http.content.*
import io.ktor.server.plugins.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import kotlinx.html.*
import java.io.File

fun Application.configureRouting() {
    routing {
        authenticate("auth-jwt") {
            get("/") {
                val port = call.request.origin.serverPort
                call.respondHtml(HttpStatusCode.OK) {
                    head {
                        title {
                            + "Index Page"
                        }
                    }
                    body {
                        p {
                            + "Hello from the web server running on port $port"
                        }
                    }
                }
            }
        }
        get("/ping") {
            call.respond(HttpStatusCode.OK)
        }
        staticFiles(".well-known", File("certs"), "jwks.json")
    }
}
