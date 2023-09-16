package parser

import parser.analysers.Lexical
import java.io.File
import java.util.Scanner

class Parser(fileName: String) {
    private val file = File(fileName)
    private val scanner = Scanner(file)
    private val lexical = Lexical()

    fun lexicalParse(): List<Char> {
        return lexical.parseFile(scanner)
    }
}