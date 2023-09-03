package InputHandler

import InputHandler.Handlers.ByteReader
import InputHandler.Handlers.LineReader

class InputHandler {
    // all the methods will take a filehandler maybe?
    fun handleInput(handleType: String?, fileName: String) {
        when (handleType) {
            "c" -> println(ByteReader.toBytesLength(fileName))
            "l" -> println(LineReader.toLinesLength(fileName))
            "w" -> println("words")
            "m" -> println("characters")
            else -> println("all")
        }
    }
}