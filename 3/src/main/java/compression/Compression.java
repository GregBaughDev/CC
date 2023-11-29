package compression;

import java.io.*;
import java.util.*;

public class Compression {
    File fileToParse;
    File outputFile;
    public static final String HEADER_END = "H_END";

    public Compression(String fileToParse, String outputFile) {
        this.fileToParse = new File(fileToParse);
        this.outputFile = new File(outputFile);
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

    public void writeToOutputFile(Map<Character, Integer> headerMap, Map<Character, String> prefixMap) throws IOException {
        writeFileHeader(headerMap);
        compressText(prefixMap);
    }

    private void writeFileHeader(Map<Character, Integer> prefixMap) throws FileNotFoundException {
        try (PrintWriter writer = new PrintWriter("H_" + outputFile)) {
            prefixMap.forEach((k, v) -> writer.println(k + ":" + v));
            writer.println(HEADER_END);
        }
    }

    private void compressText(Map<Character, String> prefixMap) throws IOException {
        try (
            Scanner s = new Scanner(fileToParse);
            FileOutputStream fos = new FileOutputStream(outputFile)
        ) {
            while (s.hasNext()) {
                char[] tmp = s.nextLine().toCharArray();
                if (tmp.length == 0) {
                    continue;
                }

                StringBuilder prefixLine = new StringBuilder();
                for (char c : tmp) {
                    prefixLine.append(prefixMap.get(c));
                }

                byte[] stringBytes = createByteArray(prefixLine.toString());
                for (byte b : stringBytes) {
                    try {
                        fos.write(b);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                fos.write('\n');
                fos.flush();
            }
        }
    }

    private byte[] createByteArray(String prefixString) {
        prefixString += "1"; // Add additional 1 bit to maintain accuracy
        char[] splitString = prefixString.toCharArray();
        BitSet bs = new BitSet(splitString.length);
        StringBuilder test = new StringBuilder();
        for (var i = 0; i < splitString.length; i++) {
            test.append(splitString[i] == '1' ? '1' : '0');
            bs.set(i, splitString[i] == '1');
        }
        return bs.toByteArray();
    }
}
