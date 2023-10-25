package compression;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Compression {
    File fileToParse;
    File outputFile;
    PrintWriter writer;

    public Compression(String fileToParse, String outputFile) throws FileNotFoundException {
        this.fileToParse = new File(fileToParse);
        this.outputFile = new File(outputFile);
        this.writer = new PrintWriter(outputFile);
    }

    public Map<Character, Integer> readFile() throws FileNotFoundException {
        HashMap<Character, Integer> charResults = new HashMap<>();
        try (Scanner s = new Scanner(fileToParse)) {
            while (s.hasNext()) {
                char[] tmp = s.nextLine().toCharArray();
                for (char c : tmp) {
                    if (charResults.containsKey(c)) {
                        charResults.put(c, charResults.get(c) + 1);
                    } else {
                        charResults.put(c, 1);
                    }
                }
            }
        }
        return charResults;
    }

    public void writeToOutputFile(Map<Character, String> prefixMap) {
        writeFileHeader(prefixMap);

        // now need a similar method to read file which reads the file and gets each character
        // we get the character from the map and append it to the file


        writer.close();
    }

    private void writeFileHeader(Map<Character, String> prefixMap) {
        writer.println("FILE_HEADER_BEGIN");
        writer.println("| CHAR | PREFIX");
        prefixMap.forEach((k, v) -> {
            writer.println("| " + k + " | " + v);
        });
        writer.println("FILE_HEADER_END");
    }
}
