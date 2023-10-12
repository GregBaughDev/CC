package compression;

import org.junit.jupiter.api.*;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

@TestInstance(TestInstance.Lifecycle.PER_CLASS)
class CompressionTest {
    String FILENAME = "test.txt";
    PrintWriter writer = new PrintWriter(FILENAME);
    Compression compression = new Compression(FILENAME);

    CompressionTest() throws IOException {}

    @AfterEach
    public void afterEach() {
        writer.println("");
        writer.close();
    }

    @AfterAll
    public void afterAll() throws IOException {
        Files.delete(Path.of(FILENAME));
    }

    @Test
    public void shouldReturnCorrectCharacterNumber() throws IOException {
        writer.println("this is a string that contains 10 instances of the letter 't'");
        writer.close();
        assertEquals(10, compression.readFile().get('t'));
    }
}