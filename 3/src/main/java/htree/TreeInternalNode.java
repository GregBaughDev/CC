package htree;

public class TreeInternalNode implements TreeBaseNode {
    private final Integer weight;
    private final TreeBaseNode left;
    private final TreeBaseNode right;

    public TreeInternalNode(Integer weight, TreeBaseNode left, TreeBaseNode right) {
        this.weight = weight;
        this.left = left;
        this.right = right;
    }

    public TreeBaseNode getLeft() {
        return this.left;
    }

    public TreeBaseNode getRight() {
        return this.right;
    }

    @Override
    public Integer weight() {
        return this.weight;
    }

    @Override
    public boolean isLeaf() {
        return false;
    }
}
