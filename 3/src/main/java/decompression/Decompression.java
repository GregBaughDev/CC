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
                if (b == 10) { // 10 = newline
                    stringList.add(sb.toString());
                    sb = new StringBuilder();
                    continue;
                }
                int eightBigInt = b & (0xFF);
                String binString = Integer.toBinaryString(eightBigInt);
                sb.append(reverseBitsAndPad(binString));
            }
        }
        return stringList
                .stream()
                .filter(it -> it.length() > 0)
                .map(this::stringMinusEndBitPad)
                .toList();
    }

    public String reverseBitsAndPad(String bitString) {
        if (bitString.length() > 8 || bitString.length() == 0) {
            throw new RuntimeException("String must be between 1 and 8 characters");
        }
        StringBuilder sb = new StringBuilder(bitString).reverse();
        while (sb.length() % 8 != 0) {
            sb.append("0");
        }
        return sb.toString();
    }

    public String stringMinusEndBitPad(String bitString) {
        for(var i = bitString.length() - 1; i >= 0; i--) {
            if (bitString.charAt(i) == '1') {
                return bitString.substring(0, i);
            }
        }
        throw new RuntimeException("String invalid");
    }
}
