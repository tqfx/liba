package liba;

import java.nio.ByteBuffer;

/** 8-bit Cyclic Redundancy Check */
public class crc8 {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        clinit();
    }

    static final native void clinit();

    final native void init(byte poly, boolean reversed);

    /**
     * construct a new {@link crc8} object
     *
     * @param poly polynomial that is CRC's divisor
     */
    public crc8(byte poly) {
        init(poly, false);
    }

    /**
     * construct a new {@link crc8} object
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    public crc8(byte poly, boolean reversed) {
        init(poly, reversed);
    }

    /**
     * get table for 8-bit Cyclic Redundancy Check
     *
     * @return filter coefficient [0,1]
     */
    public final native byte[] table();

    /**
     * generate for 8-bit Cyclic Redundancy Check
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     * @return {@link crc8}
     */
    public final native crc8 gen(byte poly, boolean reversed);

    /**
     * calculate for 8-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    public final native byte eval(byte[] block, byte value);

    /**
     * calculate for 8-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @return output value
     */
    public byte eval(byte[] block) {
        return eval(block, (byte) 0);
    }

    /**
     * pack a block and its CRC-8 value
     *
     * @param block block to be processed
     * @param value initial value
     * @return packed block
     */
    public final native byte[] pack(byte[] block, byte value);

    /**
     * pack a block and its CRC-8 value
     *
     * @param block block to be processed
     * @return packed block
     */
    public byte[] pack(byte[] block) {
        return pack(block, (byte) 0);
    }
}
