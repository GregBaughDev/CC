import parser.Parser

fun main (args: Array<String>) {
    // Check here to make sure there's a file
    val filename = args[0]
    val parser = Parser(filename)
    parser.analyse()
}
