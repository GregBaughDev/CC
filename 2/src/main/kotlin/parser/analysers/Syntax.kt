package parser.analysers

enum class ObjectChars {
    START {
        override fun toChar(): Char {
            return '{'
        }
    },
    END {
        override fun toChar(): Char {
            return '}'
        }
    };

    abstract fun toChar(): Char
}

class Syntax {
    // Syntactic analysis
    // Work through the symbols and use some sort of tree DS
    fun analyse(parsedList: List<String>): Boolean {
        // probs use a for loop
        var result = false
        for (i in parsedList) {
            // have a method here which handles the first character and deals with it appropriately
            val charArray = i.toCharArray()
            result = handleSymbol(charArray[0])
        }
        return result
    }
    // will need to pass first char and then the whole string/object/boolean in
    private fun handleSymbol(char: Char): Boolean {
        return when (char) {
            '{', '}' -> isObjectChar(char)
            else -> false
        }
    }

    private fun isObjectChar(char: Char): Boolean {
        return char == ObjectChars.START.toChar() || char == ObjectChars.END.toChar()
    }
}