import InputHandler.InputHandler

class CCWC(val fileName: String) {
    private val inputHandler = InputHandler()

    var bytes = 0
    var lines = 0
    var words = 0
    var characters = 0
    // Above should all be in a data class which is returned at the end

    fun run(type: String?) {
        inputHandler.handleInput(type, fileName)
    }
}