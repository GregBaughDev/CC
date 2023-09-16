import parser.Parser

fun main (args: Array<String>) {
    // Check here to make sure there's a file
    val filename = args[0]
    val parser = Parser(filename)
    println(parser.lexicalParse().forEach { println(it) })
}

// Plan
// Lexical analysis
    // Take in the file and parse it
    // Split up the input into an array
    // Quotes need to be escaped -> use toCharArray
// Syntactic analysis
    // Work through the symbols and use some sort of tree DS
