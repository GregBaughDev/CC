package compression;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Compression {
    File file;

    public Compression(String filename) {
        this.file = new File(filename);
    }

    public Map<Character, Integer> readFile() throws FileNotFoundException {
        HashMap<Character, Integer> charResults = new HashMap<>();
        try (Scanner s = new Scanner(file)) {
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
}
