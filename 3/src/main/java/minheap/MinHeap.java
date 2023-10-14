package minheap;

import htree.TreeLeafNode;

import java.util.ArrayList;

public class MinHeap {
    ArrayList<TreeLeafNode> data;
    int length;

    public MinHeap() {
        this.data = new ArrayList<>();
        this.length = 0;
    }

    public void insertValue(TreeLeafNode value) {
        this.data.add(this.length, value);
        this.heapifyUp(this.length);
        this.length++;
    }

    public TreeLeafNode delete() {
        if (this.length == 0) {
            return null;
        }
        TreeLeafNode out = this.data.get(0);
        this.length--;

        if (this.length == 0) {
            this.data = new ArrayList<>();
            return out;
        }
        this.data.set(0, this.data.get(this.length));
        this.heapifyDown(0);
        return out;
    }

    private void heapifyDown(int idx) {
        int leftIndex = this.getLeftChildIndex(idx);
        int rightIndex = this.getRightChildIndex(idx);

        if (leftIndex >= this.length || rightIndex >= this.length) {
            return;
        }

        TreeLeafNode leftValue = this.data.get(leftIndex);
        TreeLeafNode rightValue = this.data.get(rightIndex);
        TreeLeafNode value = this.data.get(idx);

        if (leftValue.weight() > rightValue.weight() && value.weight() > rightValue.weight()) {
            this.data.set(idx, rightValue);
            this.data.set(rightIndex, value);
            this.heapifyDown(rightIndex);
        } else if (rightValue.weight() > leftValue.weight() && value.weight() > leftValue.weight()) {
            this.data.set(idx, leftValue);
            this.data.set(leftIndex, value);
            this.heapifyDown(leftIndex);
        }
    }

    private void heapifyUp(int idx) {
        if (length == 0) {
            return;
        }

        int parent = this.getParentIndex(idx);
        TreeLeafNode parentValue = this.data.get(parent);
        TreeLeafNode value = this.data.get(idx);

        if (parentValue.weight() > value.weight()) {
            this.data.set(idx, parentValue);
            this.data.set(parent, value);
            this.heapifyUp(parent);
        }
    }

    private int getParentIndex(int idx) {
        return (idx - 1) / 2;
    }

    private int getLeftChildIndex(int idx) {
        return idx * 2 + 1;
    }

    private int getRightChildIndex(int idx) {
        return idx * 2 + 2;
    }
}
