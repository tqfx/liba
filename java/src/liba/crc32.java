package liba;

import java.nio.ByteBuffer;

/** 32-bit Cyclic Redundancy Check */
public class crc32 {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    final native void init(int poly, boolean reversed);

    /**
     * construct a new {@link crc32} object
     *
     * @param poly polynomial that is CRC's divisor
     */
    public crc32(int poly) {
        init(poly, false);
    }

    /**
     * construct a new {@link crc32} object
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    public crc32(int poly, boolean reversed) {
        init(poly, reversed);
    }

    /**
     * get table for 32-bit Cyclic Redundancy Check
     *
     * @return filter coefficient [0,1]
     */
    public final native int[] table();

    /**
     * generate for 32-bit Cyclic Redundancy Check
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     * @return {@link crc32}
     */
    public final native crc32 gen(int poly, boolean reversed);

    /**
     * calculate for 32-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    public final native int eval(byte[] block, int value);

    /**
     * calculate for 32-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @return output value
     */
    public int eval(byte[] block) {
        return eval(block, 0);
    }

    /**
     * pack a block and its CRC-32 value
     *
     * @param block block to be processed
     * @param value initial value
     * @return packed block
     */
    public final native byte[] pack(byte[] block, int value);

    /**
     * pack a block and its CRC-32 value
     *
     * @param block block to be processed
     * @return packed block
     */
    public byte[] pack(byte[] block) {
        return pack(block, 0);
    }
}
