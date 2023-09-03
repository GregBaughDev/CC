package InputHandler.Handlers

import java.io.File

class ByteReader {
    companion object {
        fun toBytesLength(fileName: String): Int {
            return File(fileName).readBytes().count()
        }
    }
}