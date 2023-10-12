import compression.Compression;

import java.util.Map;

public class CC3 {
    public static void main (String[] args) throws Exception {
        if (args.length == 0) {
            throw new Exception("File name must be supplied");
        }
        String filename = args[0];
        Compression compression = new Compression(filename);
        Map<Character, Integer> c = compression.readFile();
        System.out.println("X: " + c.get('X'));
        System.out.println("t: " + c.get('t'));
    }
}
