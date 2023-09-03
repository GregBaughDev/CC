fun main(args: Array<String>) {
    // takes -c -l -w -m as args
    // -c bytes in the file
    // -l number of lines
    // -w number of words
    // -m number of characters

    // process the flag and send off to the corresponding function
    // store the result and print at end
    // also need to find out how to call the program with "ccwc"
    // also need to handle if no args are passed and only a file
    val readMethod = if (args.isNotEmpty()) args[0].substring(1) else null
    val fileName = args[1]
    // for the min I'll always access args1
    val ccwc = CCWC(fileName)
    ccwc.run(readMethod)
}