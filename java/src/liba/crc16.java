package liba;

import java.nio.ByteBuffer;

/** 16-bit Cyclic Redundancy Check */
public class crc16 {
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    final native void init(short poly, boolean reversed);

    /**
     * construct a new {@link crc16} object
     *
     * @param poly polynomial that is CRC's divisor
     */
    public crc16(short poly) {
        init(poly, false);
    }

    /**
     * construct a new {@link crc16} object
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     */
    public crc16(short poly, boolean reversed) {
        init(poly, reversed);
    }

    /**
     * get table for 16-bit Cyclic Redundancy Check
     *
     * @return filter coefficient [0,1]
     */
    public final native short[] table();

    /**
     * generate for 16-bit Cyclic Redundancy Check
     *
     * @param poly     polynomial that is CRC's divisor
     * @param reversed is reversed?
     * @return {@link crc16}
     */
    public final native crc16 gen(short poly, boolean reversed);

    /**
     * calculate for 16-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @param value initial value
     * @return output value
     */
    public final native short eval(byte[] block, short value);

    /**
     * calculate for 16-bit Cyclic Redundancy Check
     *
     * @param block block to be processed
     * @return output value
     */
    public short eval(byte[] block) {
        return eval(block, (short) 0);
    }

    /**
     * pack a block and its CRC-16 value
     *
     * @param block block to be processed
     * @param value initial value
     * @return packed block
     */
    public final native byte[] pack(byte[] block, short value);

    /**
     * pack a block and its CRC-16 value
     *
     * @param block block to be processed
     * @return packed block
     */
    public byte[] pack(byte[] block) {
        return pack(block, (short) 0);
    }
}
