package htree;

import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

class TreeHandlerTest {

    @Test
    void shouldReturnChar() {
        Map<String, Integer> testMap = new HashMap<>();
        testMap.put("G", 35);
        testMap.put("x", 1);
        testMap.put("A", 123);
        testMap.put(":", 64);
        testMap.put("h", 709);
        testMap.put("l", 34);
        testMap.put("P", 91);
        testMap.put("d", 12);
        testMap.put("j", 2);
        testMap.put("^", 2);
        testMap.put("6", 23);
        testMap.put("q", 2);
        testMap.put("Q", 45);
        testMap.put("1", 12);
        TreeHandler treeHandler = new TreeHandler();
        testMap.forEach((k, v) -> treeHandler.addNodeItemToHeap(new HuffmanNode(k.toCharArray()[0], v)));
        HuffmanNode huffTree = treeHandler.createHuffTree();
        Map<Character, String> prefixCodeTable = new HashMap<>();
        testMap.forEach((k, __) -> {
            HuffResult prefix = treeHandler.findElement(k.toCharArray()[0], huffTree);
            prefixCodeTable.put(k.toCharArray()[0], prefix.getPrefixCode());
        });
        assertEquals('G', treeHandler.findChar(prefixCodeTable.get('G'), 0, huffTree).getElem());
        assertEquals('x', treeHandler.findChar(prefixCodeTable.get('x'), 0, huffTree).getElem());
        assertEquals('A', treeHandler.findChar(prefixCodeTable.get('A'), 0, huffTree).getElem());
        assertEquals(':', treeHandler.findChar(prefixCodeTable.get(':'), 0, huffTree).getElem());
        assertEquals('h', treeHandler.findChar(prefixCodeTable.get('h'), 0, huffTree).getElem());
        assertEquals('l', treeHandler.findChar(prefixCodeTable.get('l'), 0, huffTree).getElem());
        assertEquals('P', treeHandler.findChar(prefixCodeTable.get('P'), 0, huffTree).getElem());
        assertEquals('d', treeHandler.findChar(prefixCodeTable.get('d'), 0, huffTree).getElem());
        assertEquals('j', treeHandler.findChar(prefixCodeTable.get('j'), 0, huffTree).getElem());
        assertEquals('^', treeHandler.findChar(prefixCodeTable.get('^'), 0, huffTree).getElem());
        assertEquals('6', treeHandler.findChar(prefixCodeTable.get('6'), 0, huffTree).getElem());
        assertEquals('q', treeHandler.findChar(prefixCodeTable.get('q'), 0, huffTree).getElem());
        assertEquals('Q', treeHandler.findChar(prefixCodeTable.get('Q'), 0, huffTree).getElem());
        assertEquals('1', treeHandler.findChar(prefixCodeTable.get('1'), 0, huffTree).getElem());
    }
}