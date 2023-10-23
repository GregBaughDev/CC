package htree;

public class HuffmanNode {
    private char element;
    private final int weight;
    private HuffmanNode left;
    private HuffmanNode right;

    public HuffmanNode (int weight, HuffmanNode left, HuffmanNode right) {
        this.weight = weight;
        this.left = left;
        this.right = right;
    }

    public HuffmanNode (char c, int weight) {
        this.element = c;
        this.weight = weight;
    }

    public Boolean isLeaf() {
        return this.left == null && this.right == null;
    }

    public char getElement() {
        return this.element;
    }

    public int getWeight() {
        return this.weight;
    }

    public HuffmanNode getLeft() {
        return this.left;
    }

    public HuffmanNode getRight() {
        return this.right;
    }
}
