package com.gbaugh.plugins

import com.gbaugh.forwarder.Forwarder
import io.ktor.client.call.*
import io.ktor.http.*
import io.ktor.server.application.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import kotlinx.coroutines.runBlocking

fun Application.configureRouting(forwarder: Forwarder) {
    routing {
        get("/") {
            runBlocking {
                forwarder.sendRequest().let {
                    if (it.status.isSuccess()) {
                        call.respond(HttpStatusCode.OK, it.body<String>())
                    } else {
                        call.respond(HttpStatusCode.BadRequest)
                    }
                }
            }
        }
    }
}


