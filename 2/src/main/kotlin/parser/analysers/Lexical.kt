package parser.analysers

import java.util.Scanner

class Lexical {
    fun parseFile(scanner: Scanner): List<String> {
        return mutableListOf<String>().apply {
            while (scanner.hasNext()) {
                scanner.forEach { this.add(it) }
            }
        }
    }
}