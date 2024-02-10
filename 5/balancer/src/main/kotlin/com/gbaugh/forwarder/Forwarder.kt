package com.gbaugh.forwarder

import io.ktor.client.*
import io.ktor.client.engine.cio.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import kotlinx.coroutines.delay

class Forwarder(
    private val client: HttpClient = HttpClient(CIO), // todo: Not sure if we need multiple servers for making concurrent requests
    private val ports: List<Int> = listOf(8081, 8082, 8083, 8084), // todo: get this from shared config
    private val servers: MutableList<Server> = mutableListOf()
) {
    init {
        ports.forEach {
            servers.add(Server(it))
        }
    }

    private var currServer = 0

    private fun getServer(): Int {
        // HERE -> Need to only return port if it's healthy
        currServer++
        if (currServer == servers.count()) {
            currServer = 0;
        }
        return ports[currServer]
    }

    suspend fun sendRequest(): HttpResponse {
        return client.get("http://localhost:${getServer()}")
    }

    suspend fun healthCheck() {
        // currstate - need to run this with a timeout
        // need to also not send requests in the health fails
        // but keep pinging to check when it's healthy again
        while (true) {
            delay(10000) // pass through the time to constructor
            servers.forEach {
                client.get("http://localhost:${it.port}/ping").let { res ->
                    if (res.status.isSuccess()) {
                        println("Server: ${it.port} is healthy")
                    } else {
                        println("Server: ${it.port} is down")
                        it.healthy = false
                    }
                }
            }
        }
    }

    inner class Server(val port: Int, var healthy: Boolean = true)
}