package decompression;

import java.io.*;
import java.util.*;

import static compression.Compression.HEADER_END;

public class Decompression {
    File headerFile;
    File compressedFile;

    public Decompression(String compressedFile, String headerFile) {
        this.compressedFile = new File(compressedFile);
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

    public List<String> parseFile() throws IOException {
        List<String> stringList = new ArrayList<>();
        try (BufferedInputStream s = new BufferedInputStream(new FileInputStream(compressedFile))) {
            byte[] arr = s.readAllBytes();
            StringBuilder sb = new StringBuilder();
            for (byte b : arr) {
                if (b == 10) {
                    stringList.add(sb.toString());
                    sb = new StringBuilder();
                    continue;
                }
                int eightBigInt = (0xFF) & b;
                String binString = Integer.toBinaryString(eightBigInt);
                while (binString.length() != 8) {
                    binString = "0" + binString;
                }
                stringList.add(binString);
            }
        }
        return stringList;
    }

    // TO DO ->
    // Get the whole string and traverse the tree - return a character
    // remove the already traversed digits - right now we are going back and forth for the string pos
    // to rememedy this we need to cut? the string
    // build up the text
}
