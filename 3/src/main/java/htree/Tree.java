package htree;

public class Tree {
    private final TreeBaseNode root;

    public Tree(Integer weight, char element) {
        this.root = new TreeLeafNode(element, weight);
    }

    public Tree(Integer weight, TreeBaseNode left, TreeBaseNode right) {
        this.root = new TreeInternalNode(weight, left, right);
    }

    public TreeBaseNode getRoot() {
        return this.root;
    }

    public Integer getWeight() {
        return this.root.weight();
    }

    public Integer compareTo(TreeBaseNode element) {
        if (this.root.weight() < element.weight()) {
            return -1;
        } else if (this.root.weight() == element.weight()) {
            return 0;
        } else {
            return 1;
        }
    }
}
