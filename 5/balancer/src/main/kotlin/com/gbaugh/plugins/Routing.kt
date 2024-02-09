package com.gbaugh.plugins

import com.gbaugh.forwarder.Forwarder
import io.ktor.server.application.*
import io.ktor.server.request.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import kotlinx.coroutines.runBlocking

fun Application.configureRouting() {
    val forwarder = Forwarder()

    routing {
        get("/") {
            call.respondText("Hello World!")
            val req = call.request.headers
            req.forEach { h, list -> list.forEach { println(it) } }

            // currstate - sending requests to all the servers
            runBlocking {
                forwarder.sendRequest()
            }
        }
    }
}


