package htree;

public class HuffResult {
    private char elem;
    private String prefixCode = null;

    public HuffResult() {}

    public void setHuffResult(char elem, String prefixCode) {
        this.prefixCode = prefixCode;
        this.elem = elem;
    }

    public void setHuffResult(char elem) {
        this.elem = elem;
    }

    public char getElem() {
        return this.elem;
    }

    public String getPrefixCode() {
        return this.prefixCode;
    }

    @Override
    public String toString() {
        return "HuffResult{" +
                "elem=" + elem +
                "prefix=" + prefixCode +
                '}';
    }
}
