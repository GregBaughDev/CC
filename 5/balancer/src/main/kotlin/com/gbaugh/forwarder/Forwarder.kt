package com.gbaugh.forwarder

import io.ktor.client.*
import io.ktor.client.engine.cio.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import kotlinx.coroutines.delay

class Forwarder(
    private val client: HttpClient = HttpClient(CIO), // todo: Not sure if we need multiple servers for making concurrent requests
    ports: List<Int> = listOf(8081, 8082, 8083, 8084), // todo: get this from shared config
    private val healthCheckTimeout: Long = 10000
) {
    private val servers: MutableList<Server> = mutableListOf()
    private var currServer = -1

    init {
        ports.forEach {
            servers.add(Server(it))
        }
    }

    // curr state
    // do the parallel requests in the challenge
    // handle diff http methods
    // add auth so only the balancer can call the servers
    // todos

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

    suspend fun sendRequest(): HttpResponse {
        return client.get("http://localhost:${getServer()}")
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