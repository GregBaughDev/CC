package inputHandler

import java.io.File

class InputHandler {
    fun handleInput(handleType: String?, file: File) {
        when (handleType) {
            "c" -> println(toBytesLength(file))
            "l" -> println(toLinesLength(file))
            "w" -> println(toWordsLength(file))
            "m" -> println("characters")
            else -> println("all")
        }
    }

    private fun toBytesLength(file: File): Int {
        return file.readBytes().count()
    }

    private fun toLinesLength(file: File): Int {
        return file.readLines().count()
    }

    private fun toWordsLength(file: File): Int {
        // This is the issue atm - try char isWhiteSpace fn
        return file.readLines().toString().split(" ").count()
    }


}



