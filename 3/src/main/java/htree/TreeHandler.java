package htree;

import java.util.Objects;
import java.util.PriorityQueue;

public class TreeHandler {
    private final PriorityQueue<HuffmanNode> queue;

    public TreeHandler() {
        this.queue = new PriorityQueue<>((o1, o2) -> {
            if (o1.getWeight() < o2.getWeight()) {
                return -1;
            } else if (o1.getWeight() == o2.getWeight()) {
                return 0;
            } else {
                return 1;
            }
        });
    }

    public HuffmanNode createHuffTree() {
        HuffmanNode tmp1, tmp2, tmp3 = null;

        while (queue.toArray().length > 1) {
            tmp1 = queue.poll();
            tmp2 = queue.poll();
            tmp3 = new HuffmanNode(tmp1.getWeight() + tmp2.getWeight(), tmp1, tmp2);
            queue.add(tmp3);
        }
        return tmp3;
    }

    public void addNodeItemToHeap(HuffmanNode item) {
        queue.add(item);
    }

    public HuffResult findElement(char elem, HuffmanNode node) {
        String prefix = "";
        HuffResult result = new HuffResult();
        return searchHuffman(elem, prefix, node, result);
    }

    private HuffResult searchHuffman(char elem, String prefix, HuffmanNode node, HuffResult result) {
        if (node.getElement() == elem) {
            result.setHuffResult(elem, prefix);
        }

        if (node.getLeft() != null) {
            searchHuffman(elem, prefix + "0", node.getLeft(), result);
        }

        if (node.getRight() != null) {
            searchHuffman(elem, prefix + "1", node.getRight(), result);
        }
        return result;
    }

    public HuffResult findChar(String prefixString, HuffmanNode node) {
        HuffResult result = new HuffResult();
        return getCharFromPrefix(prefixString, 0, node, result);
    }

    private HuffResult getCharFromPrefix(String prefixString, int prefixIndex, HuffmanNode node, HuffResult result) {
        if (node.isLeaf()) {
            result.setHuffResult(node.getElement(), prefixIndex);
        }

        if (prefixIndex < prefixString.length() && result.getElem() == null) {
            if (prefixString.charAt(prefixIndex) == '1') {
                getCharFromPrefix(prefixString, prefixIndex + 1, node.getRight(), result);
            }

            if (prefixString.charAt(prefixIndex) == '0') {
                getCharFromPrefix(prefixString, prefixIndex + 1, node.getLeft(), result);
            }
        }
        return result;
    }
}

