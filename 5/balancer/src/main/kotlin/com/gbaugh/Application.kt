package com.gbaugh

import com.gbaugh.forwarder.Forwarder
import com.gbaugh.plugins.*
import io.ktor.server.application.*
import io.ktor.server.engine.*
import io.ktor.server.netty.*
import kotlinx.coroutines.coroutineScope
import kotlinx.coroutines.launch

val forwarder = Forwarder()

suspend fun main() {
    coroutineScope {
        launch {
            embeddedServer(Netty, port = 8080, host = "0.0.0.0", module = Application::module)
                .start(wait = true)
        }
        launch {
            forwarder.healthCheck()
        }
    }
}

fun Application.module() {
    configureRouting(forwarder)
}

