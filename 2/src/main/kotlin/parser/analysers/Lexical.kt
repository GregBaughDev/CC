package parser.analysers

import java.util.Scanner

class Lexical {
    fun parseFile(scanner: Scanner): List<Char> {
        return mutableListOf<Char>().apply {
            while (scanner.hasNext()) {
                scanner.forEach { it -> it.forEach { this.add(it) } }
            }
        }
    }
}