package inputHandler

import java.io.File
import java.util.Scanner

class InputHandler {
    fun handleInput(handleType: String?, file: File) {
        when (handleType) {
            "c" -> println(toBytesLength(file))
            "l" -> println(toLinesLength(file))
            "w" -> println(toWordsLength(file))
            "m" -> println(toCharactersLength(file))
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
        var count = 0
        Scanner(file).use {
            while (it.hasNext()) {
                it.forEach { _ ->
                    count++
                }
            }
        }
        return count
    }

    private fun toCharactersLength(file: File): Int {
        return file.readLines().toString().toCharArray().count()
    }
}



