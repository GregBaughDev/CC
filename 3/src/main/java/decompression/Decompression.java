package decompression;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import static compression.Compression.HEADER_END;

public class Decompression {
    File headerFile;

    public Decompression(String headerFile) {
        this.headerFile = new File(headerFile);
    }

    public Map<String, String> parseHeader() throws FileNotFoundException {
        HashMap<String, String> headerMap = new HashMap<>();
        try (Scanner s = new Scanner(headerFile)) {
            while (s.hasNext()) {
                String inputLine = s.nextLine();
                if (inputLine.equalsIgnoreCase(HEADER_END)) {
                    break;
                }
                headerMap.put(inputLine.substring(0, 1), inputLine.substring(1));
            }
        }
        return headerMap;
    }

    // TO DO -> Find the val -> While .notLeaf() - go left, go right
    // Read the file
    // Get the whole string and traverse the tree - return a character
    // remove the already traversed digits
    // build up the text
}
