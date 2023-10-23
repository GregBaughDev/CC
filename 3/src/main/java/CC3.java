import compression.Compression;
import htree.HuffResult;
import htree.HuffmanNode;
import htree.TreeHandler;

import java.util.Map;

public class CC3 {
    public static void main (String[] args) throws Exception {
        if (args.length == 0) {
            throw new Exception("File name must be supplied");
        }
        String filename = args[0];
        Compression compression = new Compression(filename);
        TreeHandler treeHandler = new TreeHandler();

        Map<Character, Integer> mappedResults = compression.readFile();
        mappedResults.forEach((k, v) -> treeHandler.addNodeItemToHeap(new HuffmanNode(k, v)));
        HuffmanNode huffTree = treeHandler.createHuffTree();
        // Example
        HuffResult prefix = treeHandler.findElement('A', huffTree);
    }
}
