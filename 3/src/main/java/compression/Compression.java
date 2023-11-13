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

    public void writeToOutputFile(Map<Character, String> prefixMap) throws IOException {
        writeFileHeader(prefixMap);
        compressText(prefixMap);
    }

    private void writeFileHeader(Map<Character, String> prefixMap) throws FileNotFoundException {
        try (PrintWriter writer = new PrintWriter("H_" + outputFile)) {
            writer.println("H_START");
            prefixMap.forEach((k, v) -> {
                writer.println(k + v);
            });
            writer.println(HEADER_END);
        }
    }

    private void compressText(Map<Character, String> prefixMap) throws IOException {
        try (
            Scanner s = new Scanner(fileToParse);
            FileOutputStream fos = new FileOutputStream(outputFile)
        ) {
            while (s.hasNext()) {
                // Append the prefix strings to prefixLine
                char[] tmp = s.nextLine().toCharArray();
                if (tmp.length == 0) {
                    continue;
                }

                StringBuilder prefixLine = new StringBuilder();
                for (char c : tmp) {
                    prefixLine.append(prefixMap.get(c));
                }

                List<String> byteStrings = getStringByteList(prefixLine);
                byteStrings.forEach(it -> {
                    try {
                        if (it.length() % 8 == 0) {
                            fos.write(createByte(it));
                        } else {
                            StringBuilder tmpStr = new StringBuilder(it);
                            while (tmpStr.length() % 8 != 0) {
                                tmpStr.append('0');
                            }
                            fos.write(createByte(tmpStr.toString()));
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                });
                fos.write('\n');
                fos.flush();
            }
        }
    }

    public List<String> getStringByteList(StringBuilder prefixLine) {
        List<String> byteStrings = new ArrayList<>();
        StringBuilder bsBuilder = new StringBuilder();
        for (var i = 1; i < prefixLine.length() + 1; i++) {
            bsBuilder.append(prefixLine.charAt(i - 1));
            if (i == prefixLine.length()) {
                byteStrings.add(bsBuilder.toString());
                break;
            }
            if (i % 8 == 0) {
                byteStrings.add(bsBuilder.toString());
                bsBuilder = new StringBuilder();
            }
        }
        return byteStrings;
    }

    private byte createByte(String strToByte) {
        if (strToByte.length() != 8) {
            throw new RuntimeException("String must be 8 characters");
        }
        char[] splitString = strToByte.toCharArray();
        BitSet bs = new BitSet(8);
        for (var i = 0; i < 8; i++) {
            bs.set(i, splitString[i] == '1');
        }
        if (bs.isEmpty()) {
            return (byte) '0';
        }
        return bs.toByteArray()[0];
    }
}
