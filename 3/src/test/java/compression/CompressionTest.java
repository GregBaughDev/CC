package compression;

import org.junit.jupiter.api.*;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

@TestInstance(TestInstance.Lifecycle.PER_CLASS)
class CompressionTest {
    String FILENAME = "test.txt";
    String OUTPUTFILE = "testoutput.txt";
    PrintWriter writer = new PrintWriter(FILENAME);
    Compression compression = new Compression(FILENAME, OUTPUTFILE);

    CompressionTest() throws IOException {}

    @Test
    public void shouldReturnCorrectCharacterNumber() throws IOException {
        writer.println("this is a string that contains 10 instances of the letter 't'");
        writer.close();
        assertEquals(10, compression.readFile().get('t'));
        Files.delete(Path.of(FILENAME));
    }

    @Test
    public void shouldReturnListOfByteStrings() {
        StringBuilder testString = new StringBuilder("1001001101010101101");
        List<String> stringList = compression.getStringByteList(testString);
        assertEquals(3, stringList.size());
        assertEquals(testString.substring(0, 8), stringList.get(0));
        assertEquals(testString.substring(8, 16), stringList.get(1));
        assertEquals(testString.substring(16), stringList.get(2));
    }

    @Test
    public void shouldReturnLongerListOfByteStrings() {
        StringBuilder testString = new StringBuilder("011011110000111110101010000000001111111101010");
        List<String> stringList = compression.getStringByteList(testString);
        assertEquals(6, stringList.size());
        assertEquals(testString.substring(0, 8), stringList.get(0));
        assertEquals(testString.substring(8, 16), stringList.get(1));
        assertEquals(testString.substring(16, 24), stringList.get(2));
        assertEquals(testString.substring(24, 32), stringList.get(3));
        assertEquals(testString.substring(32, 40), stringList.get(4));
        assertEquals(testString.substring(40), stringList.get(5));
    }
}