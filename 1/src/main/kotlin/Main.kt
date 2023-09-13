import ccwc.CCWC
import ccwc.FileResult

fun main(args: Array<String>) {
    if (args.isEmpty()) throw Exception("Must provide program arguments")

    val (readMethod, fileName) = handleArgs(args)
    val ccwc = CCWC(fileName)
    val result = ccwc.run(readMethod)
    handleResults(result, fileName, readMethod)
}

fun handleArgs(args: Array<String>): Pair<String?, String> {
    val method = if (listOf("c", "l", "w", "m").contains(args[0].substring(1))) args[0].substring(1) else null
    val fileName = if (method == null) args[0] else args[1]
    return Pair(method, fileName)
}

fun handleResults(result: FileResult, fileName: String, method: String?) {
    val resultsString = when (method) {
        "c" -> result.bytes
        "l" -> result.lines
        "w" -> result.words
        "m" -> result.characters
        else -> "   ${result.lines}  ${result.words}  ${result.bytes}"
    }
    println("$resultsString $fileName")
}