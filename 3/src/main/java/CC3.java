import compression.Compression;
import htree.HuffResult;
import htree.HuffmanNode;
import htree.TreeHandler;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

enum Mode {
    ENCODE, DECODE
}

public class CC3 {
    public static void main (String[] args) throws Exception {
//        if (args.length == 0) {
//            throw new Exception("File name to be parsed must be supplied");
//        }
//        if (args.length == 1) {
//            throw new Exception("Output file name must be supplied");
//        }
//        if (args.length > 3) {
//            throw new Exception("Too many arguments supplied");
//        }
        Mode flag = Objects.equals(args[0], "-e") ? Mode.ENCODE : Mode.DECODE;

        String fileToParse;
        String outputFile;
        String headerFile;

        if (flag == Mode.ENCODE) {
            fileToParse = args[1];
            outputFile = args[2];
            Compression compression = new Compression(fileToParse, outputFile);
            TreeHandler treeHandler = new TreeHandler();

            Map<Character, Integer> mappedResults = compression.readFile();
            mappedResults.forEach((k, v) -> treeHandler.addNodeItemToHeap(new HuffmanNode(k, v)));
            HuffmanNode huffTree = treeHandler.createHuffTree();

            Map<Character, String> prefixCodeTable = new HashMap<>();
            mappedResults.forEach((k, __) -> {
                HuffResult prefix = treeHandler.findElement(k, huffTree);
                prefixCodeTable.put(k, prefix.getPrefixCode());
            });
            compression.writeToOutputFile(prefixCodeTable);
        } else {
            fileToParse = args[1];
            headerFile = args[2];
            System.out.println("DECODE");
        }
    }
}
