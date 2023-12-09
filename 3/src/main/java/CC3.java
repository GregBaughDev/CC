import compression.Compression;
import decompression.Decompression;
import htree.HuffResult;
import htree.HuffmanNode;
import htree.TreeHandler;

import java.io.PrintWriter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

enum Mode {
    ENCODE, DECODE
}

public class CC3 {
    public static void main (String[] args) throws Exception {
        handleArgs(args);
        Mode flag = Objects.equals(args[0], "-e") ? Mode.ENCODE : Mode.DECODE;

        String fileToParse;
        String outputFile;
        String decompressedFile;

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
            compression.writeToOutputFile(mappedResults, prefixCodeTable);
        } else {
            fileToParse = args[1];
            decompressedFile = args[2];
            String headerFile = "H_" + fileToParse;
            Decompression decompression = new Decompression(fileToParse, headerFile);
            TreeHandler treeHandler = new TreeHandler();
            Map<String, Integer> mappedHeader = decompression.parseHeader();
            mappedHeader.forEach((k, v) -> treeHandler.addNodeItemToHeap(new HuffmanNode(k.toCharArray()[0], v)));
            HuffmanNode huffTree = treeHandler.createHuffTree();
            List<String> stringList = decompression.parseFile();

            try (PrintWriter pw = new PrintWriter(decompressedFile)) {
                for (var i = 0; i < (long) stringList.size(); i++) {
                    int idx = 0;
                    while (idx < stringList.get(i).length()) {
                        HuffResult res = treeHandler.findChar(stringList.get(i), idx, huffTree);
                        if (res.getElem() == null || res.getElem() == '\n') {
                            break;
                        }
                        pw.write(res.getElem());
                        idx = res.getPrefixIndex();
                    }
                    if (i != stringList.size() - 1) {
                        pw.write("\n");
                    }
                }
            }
        }
    }

    private static void handleArgs(String[] args) throws Exception {
        if (args.length == 0) {
            throw new Exception("Mode and file names must be supplied");
        }
        if (args.length < 3) {
            throw new Exception("File names must be supplied");
        }
        if (args.length > 3) {
            throw new Exception("Too many arguments supplied");
        }
    }
}
