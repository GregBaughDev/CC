package com.gbaugh.forwarder

import io.ktor.client.*
import io.ktor.client.engine.cio.*
import io.ktor.client.request.*

class Forwarder(
    private val client: HttpClient = HttpClient(CIO), // todo: Not sure if we need multiple servers for making concurrent requests
    private val servers: List<Int> = listOf(8081, 8082, 8083, 8084), // todo: get this from shared config
) {
    private var currServer = 0

    private fun getServer(): Int {
        currServer++
        if (currServer == servers.count()) {
            currServer = 0;
        }
        return servers[currServer]
    }

    suspend fun sendRequest() {
        client.get("http://localhost:${getServer()}")
    }
}