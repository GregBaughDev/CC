package parser.analysers

class Syntax {
    val lexDict = mapOf('{' to listOf("\"", "}"))

    // Syntactic analysis
    // Work through the symbols and use some sort of tree DS
    fun analyse(parsedList: List<String>): Boolean {
        // probs use a for loop
        var result = false
        for (i in parsedList) {
            println("i: $i")
            // have a method here which handles the first character and deals with it appropriately
            val charArray = i.toCharArray()
            val charArrayIndices = charArray.indices
            for (i in charArrayIndices) {
                if (charArray[i] == '{') {
                    for (j in charArrayIndices) {
                        if (charArray[j] == '}')
                            result = true
                            break
                    }
                }
            }
        }
        return result
    }
}