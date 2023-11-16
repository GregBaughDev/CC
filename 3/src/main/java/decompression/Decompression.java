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

    public Map<String, Integer> parseHeader() throws FileNotFoundException {
        HashMap<String, Integer> headerMap = new HashMap<>();
        try (Scanner s = new Scanner(headerFile)) {
            while (s.hasNext()) {
                String inputLine = s.nextLine();
                if (inputLine.equalsIgnoreCase(HEADER_END)) {
                    break;
                }
                headerMap.put(inputLine.substring(0, 1), Integer.parseInt(inputLine.substring(2)));
            }
        }
        return headerMap;
    }

    // TO DO ->
    // Read the file
    // Get the whole string and traverse the tree - return a character
    // remove the already traversed digits
    // build up the text
}
