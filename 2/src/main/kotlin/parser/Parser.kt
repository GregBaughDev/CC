package parser

import parser.analysers.Lexical
import parser.analysers.Syntax
import java.io.File
import java.util.Scanner

class Parser(fileName: String) {
    private val file = File(fileName)
    private val scanner = Scanner(file)
    private val lexical = Lexical()
    private val syntax = Syntax()

    fun analyse() {
        val parsedList = lexicalParse()
        val result = syntaxAnalyse(parsedList)
        handleResult(result)
    }

    private fun handleResult(result: Boolean) {
        when (result) {
            true -> println("Result: 0")
            false -> println("Result: 1")
        }
    }

    private fun lexicalParse(): List<String> {
        return lexical.parseFile(scanner)
    }

    private fun syntaxAnalyse(parsedList: List<String>): Boolean {
        return syntax.analyse(parsedList)
    }
}