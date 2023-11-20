import compression.Compression;
import decompression.Decompression;
import htree.HuffResult;
import htree.HuffmanNode;
import htree.TreeHandler;

import java.util.HashMap;
import java.util.List;
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
            compression.writeToOutputFile(mappedResults, prefixCodeTable);
        } else {
            fileToParse = args[1];
            headerFile = args[2];
            Decompression decompression = new Decompression(fileToParse, headerFile);
            TreeHandler treeHandler = new TreeHandler();
            Map<String, Integer> mappedHeader = decompression.parseHeader();
            mappedHeader.forEach((k, v) -> treeHandler.addNodeItemToHeap(new HuffmanNode(k.toCharArray()[0], v)));
            HuffmanNode huffTree = treeHandler.createHuffTree();
            List<String> stringList = decompression.parseFile();
            stringList.forEach(it -> System.out.println("stringList: " + it));
            StringBuilder hopefullyResult = new StringBuilder();
            System.out.println("STRINGLIST: " + stringList);

//            int currPos = 0;
//            while (stringList.length() > 0) {
//                HuffResult res = treeHandler.findChar(stringList.substring(currPos), huffTree);
//                currPos = res.getPrefixIndex();
//                stringList = stringList.substring(currPos);
//                hopefullyResult.append(res.getElem());
//            }
//            System.out.println("HOPEFULLY::: " + hopefullyResult);
        }

        // TO DO:
        // Refactor
        // Types throughout - i.e the trees
    }
}
