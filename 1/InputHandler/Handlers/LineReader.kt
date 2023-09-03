package InputHandler.Handlers

import java.io.File

class LineReader {
    companion object {
        fun toLinesLength(fileName: String): Int {
            return File(fileName).readLines().count()
        }
    }
}