package ccwc

import ccwc.inputhandler.InputHandler
import java.io.File

class CCWC(fileName: String) {
    private val inputHandler = InputHandler()
    private val file = File(fileName)

    fun run(type: String?): FileResult {
        return inputHandler.handleInput(type, file)
    }
}