package com.gbaugh.forwarder

import io.ktor.client.*
import io.ktor.client.engine.cio.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import kotlinx.coroutines.delay

class Forwarder(
    private val client: HttpClient = HttpClient(CIO),
    ports: List<Int> = listOf(8081, 8082, 8083, 8084),
    private val healthCheckTimeout: Long = 10000
) {
    private val servers: MutableList<Server> = mutableListOf()
    private var currServer = -1

    init {
        ports.forEach {
            servers.add(Server(it))
        }
    }

    private tailrec fun getServer(): Int {
        currServer++

        if (currServer == servers.count()) {
            currServer = 0
        }

        return if (servers[currServer].healthy) {
            servers[currServer].port
        } else {
            getServer()
        }
    }

    suspend fun sendRequest(token: String): HttpResponse {
        return client.get("http://localhost:${getServer()}") {
            headers {
                append(HttpHeaders.Authorization, "Bearer $token")
            }
        }
    }

    suspend fun healthCheck() {
        while (true) {
            delay(healthCheckTimeout)
            servers.forEach {
                try {
                    client.get("http://localhost:${it.port}/ping").let { res ->
                        if (res.status.isSuccess()) {
                            println("Server: ${it.port} is healthy")
                            it.healthy = true
                        }
                    }
                } catch (e: Exception) {
                    println("Server: ${it.port} is down")
                    it.healthy = false
                }
            }
        }
    }

    inner class Server(val port: Int, var healthy: Boolean = true)
}