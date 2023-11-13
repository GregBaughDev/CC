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

    @Test
    void parseHeader() throws IOException {
        PrintWriter pw = new PrintWriter(HEADER_FILE);
        pw.println("O10011000101010010");
        pw.println("g1001");
        pw.println("\\10010100000001");
        pw.println("?1110");
        pw.println("*10000");
        pw.println("A111111");
        pw.println("b00");
        pw.println(HEADER_END);
        pw.close();

        Decompression decompression = new Decompression(HEADER_FILE);
        Map<String, String> testMap = decompression.parseHeader();
        assertEquals("10011000101010010", testMap.get("O"));
        assertEquals("1001", testMap.get("g"));
        assertEquals("10010100000001", testMap.get("\\"));
        assertEquals("1110", testMap.get("?"));
        assertEquals("10000", testMap.get("*"));
        assertEquals("111111", testMap.get("A"));
        assertEquals("00", testMap.get("b"));
        assertNull(testMap.get(HEADER_END));
        Files.delete(Path.of(HEADER_FILE));
    }
}