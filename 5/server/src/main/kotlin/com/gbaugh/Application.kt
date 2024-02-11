package com.gbaugh

import com.gbaugh.plugins.configureRouting
import io.ktor.server.application.*
import io.ktor.server.engine.*
import io.ktor.server.netty.*
import kotlinx.coroutines.coroutineScope
import kotlinx.coroutines.launch

suspend fun main() {
    coroutineScope {
        listOf(8081, 8082, 8083, 8084).forEach {
            launch {
                embeddedServer(Netty, port = it, host = "0.0.0.0", module = Application::module)
                    .start(wait = true)
            }
        }
    }
}

fun Application.module() {
    configureRouting()
}
