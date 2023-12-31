package decompression;

import org.junit.jupiter.api.Test;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

import static compression.Compression.HEADER_END;
import static org.junit.jupiter.api.Assertions.*;

class DecompressionTest {
    String HEADER_FILE = "testHeader.txt";
    String COMPRESSED_FILE = "testCompressed.txt";

    @Test
    void parseHeader() throws IOException {
        PrintWriter pw = new PrintWriter(HEADER_FILE);
        pw.println("O:345");
        pw.println("g:123");
        pw.println("\\:1");
        pw.println("?:110");
        pw.println("*:89");
        pw.println("A:69");
        pw.println("b:12333");
        pw.println(HEADER_END);
        pw.close();

        Decompression decompression = new Decompression(COMPRESSED_FILE, HEADER_FILE);
        Map<String, Integer> testMap = decompression.parseHeader();
        assertEquals(345, testMap.get("O"));
        assertEquals(123, testMap.get("g"));
        assertEquals(1, testMap.get("\\"));
        assertEquals(110, testMap.get("?"));
        assertEquals(89, testMap.get("*"));
        assertEquals(69, testMap.get("A"));
        assertEquals(12333, testMap.get("b"));
        assertNull(testMap.get(HEADER_END));
        Files.delete(Path.of(HEADER_FILE));
    }

    @Test
    void reverseStringAndPadTest() {
        Decompression decompression = new Decompression(HEADER_FILE, COMPRESSED_FILE);
        String testBitString = "0010";
        assertEquals("01000000", decompression.reverseBitsAndPad(testBitString));
    }

    @Test
    void reverseStringAndPadTestException() {
        Decompression decompression = new Decompression(HEADER_FILE, COMPRESSED_FILE);
        String testBitString = "000011110";
        String testBitStringEmpty = "";
        assertThrows(RuntimeException.class, () -> decompression.reverseBitsAndPad(testBitString), "String must be 8 characters");
        assertThrows(RuntimeException.class, () -> decompression.reverseBitsAndPad(testBitStringEmpty), "String must be 8 characters");
    }

    @Test
    void removeEndBitPadTest() {
        Decompression decompression = new Decompression(HEADER_FILE, COMPRESSED_FILE);
        String testBitString = "00010101001010010000";
        String testBitString2 = "0010101001010";
        assertEquals("000101010010100", decompression.stringMinusEndBitPad(testBitString));
        assertEquals("00101010010", decompression.stringMinusEndBitPad(testBitString2));
    }

    @Test
    void shouldRemoveTheLastOneFromTheString() {
        Decompression decompression = new Decompression(HEADER_FILE, COMPRESSED_FILE);
        String testBitString = "0101001011";
        assertEquals("010100101", decompression.stringMinusEndBitPad(testBitString));
    }
}