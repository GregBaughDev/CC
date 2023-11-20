package htree;

public class HuffResult {
    private Character elem = null;
    private String prefixCode = null;
    private int prefixIndex;

    public HuffResult() {}

    public void setHuffResult(char elem, String prefixCode) {
        this.prefixCode = prefixCode;
        this.elem = elem;
    }

    public void setHuffResult(char elem, int prefixIndex) {
        this.elem = elem;
        this.prefixIndex = prefixIndex;
    }

    public Character getElem() {
        return this.elem;
    }

    public String getPrefixCode() {
        return this.prefixCode;
    }

    public int getPrefixIndex() {
        return this.prefixIndex;
    }

    @Override
    public String toString() {
        return "HuffResult{" +
                "elem=" + elem +
                "prefix=" + prefixCode +
                '}';
    }
}
