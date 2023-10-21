package minheap;

import htree.HuffmanNode;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MinHeapTest {
    MinHeap minHeap = new MinHeap();

    @Test
    void minHeapTestInsertAndDeleteValues_evenElems() {
        HuffmanNode C = new HuffmanNode('C', 1010292);
        HuffmanNode D = new HuffmanNode('D', 2031);
        HuffmanNode F = new HuffmanNode('F', 19);
        HuffmanNode X = new HuffmanNode('X', 2);
        HuffmanNode H = new HuffmanNode('H', 1);
        HuffmanNode P = new HuffmanNode('P', 51239);
        HuffmanNode G = new HuffmanNode('G', 120000000);

        minHeap.insertValue(C);
        minHeap.insertValue(D);
        minHeap.insertValue(F);
        minHeap.insertValue(X);
        minHeap.insertValue(P);
        minHeap.insertValue(G);
        minHeap.insertValue(H);

        assertEquals(7, minHeap.length);
        assertEquals(H, minHeap.delete());
        assertEquals(X, minHeap.delete());
        assertEquals(F, minHeap.delete());
        assertEquals(D, minHeap.delete());
        assertEquals(P, minHeap.delete());
        assertEquals(2, minHeap.length);
    }

    @Test
    void minHeapTestInsertAndDeleteValues_oddElems() {
        HuffmanNode C = new HuffmanNode('C', 10);
        HuffmanNode D = new HuffmanNode('D', 20);
        HuffmanNode F = new HuffmanNode('F', 19);
        HuffmanNode X = new HuffmanNode('X', 2);
        HuffmanNode P = new HuffmanNode('P', 5);
        HuffmanNode G = new HuffmanNode('G', 12);
        HuffmanNode M = new HuffmanNode('M', 100);

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