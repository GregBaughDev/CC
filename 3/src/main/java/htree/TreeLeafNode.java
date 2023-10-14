package htree;

public class TreeLeafNode implements TreeBaseNode {
    private final char element;
    private final Integer weight;

    public TreeLeafNode(char element, Integer weight) {
        this.element = element;
        this.weight = weight;
    }

    public char getElement() {
        return this.element;
    }

    @Override
    public boolean isLeaf() {
        return true;
    }

    @Override
    public Integer weight() {
        return this.weight;
    }
}
