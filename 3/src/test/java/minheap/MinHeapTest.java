package minheap;

import htree.TreeLeafNode;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MinHeapTest {
    MinHeap minHeap = new MinHeap();

    @Test
    void minHeapTestInsertAndDeleteValues_evenElems() {
        TreeLeafNode C = new TreeLeafNode('C', 10);
        TreeLeafNode D = new TreeLeafNode('D', 20);
        TreeLeafNode F = new TreeLeafNode('F', 19);
        TreeLeafNode X = new TreeLeafNode('X', 2);
        TreeLeafNode P = new TreeLeafNode('P', 5);
        TreeLeafNode G = new TreeLeafNode('G', 12);

        minHeap.insertValue(C);
        minHeap.insertValue(D);
        minHeap.insertValue(F);
        minHeap.insertValue(X);
        minHeap.insertValue(P);
        minHeap.insertValue(G);

        assertEquals(6, minHeap.length);
        assertEquals(X, minHeap.delete());
        assertEquals(P, minHeap.delete());
        assertEquals(C, minHeap.delete());
        assertEquals(G, minHeap.delete());
        assertEquals(2, minHeap.length);
    }

    @Test
    void minHeapTestInsertAndDeleteValues_oddElems() {
        TreeLeafNode C = new TreeLeafNode('C', 10);
        TreeLeafNode D = new TreeLeafNode('D', 20);
        TreeLeafNode F = new TreeLeafNode('F', 19);
        TreeLeafNode X = new TreeLeafNode('X', 2);
        TreeLeafNode P = new TreeLeafNode('P', 5);
        TreeLeafNode G = new TreeLeafNode('G', 12);
        TreeLeafNode M = new TreeLeafNode('M', 100);

        minHeap.insertValue(C);
        minHeap.insertValue(D);
        minHeap.insertValue(F);
        minHeap.insertValue(X);
        minHeap.insertValue(P);
        minHeap.insertValue(G);
        minHeap.insertValue(M);

        assertEquals(7, minHeap.length);
        assertEquals(X, minHeap.delete());
        assertEquals(P, minHeap.delete());
        assertEquals(C, minHeap.delete());
        assertEquals(G, minHeap.delete());
        assertEquals(3, minHeap.length);
    }

}