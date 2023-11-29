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
}