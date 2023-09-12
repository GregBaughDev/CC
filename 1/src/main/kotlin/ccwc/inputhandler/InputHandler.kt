package ccwc.inputhandler

import ccwc.FileResult
import java.io.File
import java.util.Scanner

class InputHandler {
    fun handleInput(handleType: String?, file: File): FileResult {
        return FileResult().apply {
            when (handleType) {
                "c" -> bytes = toBytesLength(file)
                "l" -> lines = toLinesLength(file)
                "w" -> words = toWordsLength(file)
                "m" -> characters = toCharactersLength(file)
                else -> {
                    bytes = toBytesLength(file)
                    lines = toLinesLength(file)
                    words = toWordsLength(file)
                    characters = toCharactersLength(file)
                }
            }
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



