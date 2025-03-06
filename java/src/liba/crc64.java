package liba;

import java.nio.ByteBuffer;

/** 64-bit Cyclic Redundancy Check */
public class crc64 {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    final native void init(long poly, boolean reversed);

    /**
     * construct a new {@link crc64} object
     *
     * @param poly polynomial that is CRC's divisor
     */
    public crc64(long poly) {
        init(poly, false);
    }

    /**
     * construct a new {@link crc64} object
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    public crc64(long poly, boolean reversed) {
        init(poly, reversed);
    }

    /**
     * get table for 64-bit Cyclic Redundancy Check
     *
     * @return filter coefficient [0,1]
     */
    public final native long[] table();

    /**
     * generate for 64-bit Cyclic Redundancy Check
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     * @return {@link crc64}
     */
    public final native crc64 gen(long poly, boolean reversed);

    /**
     * compute for 64-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    public final native long eval(byte[] block, long value);

    /**
     * compute for 64-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @return output value
     */
    public long eval(byte[] block) {
        return eval(block, 0);
    }

    /**
     * pack a block and its CRC-64 value
     *
     * @param block block to be processed
     * @param value initial value
     * @return packed block
     */
    public final native byte[] pack(byte[] block, long value);

    /**
     * pack a block and its CRC-64 value
     *
     * @param block block to be processed
     * @return packed block
     */
    public byte[] pack(byte[] block) {
        return pack(block, 0);
    }
}
