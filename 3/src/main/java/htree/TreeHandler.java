package htree;

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

    // Write some tests to check the weight of the parent node
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
}

