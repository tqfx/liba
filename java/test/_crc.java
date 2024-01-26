import java.util.Arrays;
import liba.crc8;
import liba.crc16;
import liba.crc32;
import liba.crc64;

class _crc {
    public static void main(String[] args) {
        String text = "0123456789";
        {
            crc8 obj = new crc8((byte) 0x07, false);
            assert obj.eval(text.getBytes()) == (byte) 0x45;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
        {
            crc8 obj = new crc8((byte) 0x31, true);
            assert obj.eval(text.getBytes()) == (byte) 0x75;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
        {
            crc16 obj = new crc16((short) 0x1021, false);
            assert obj.eval(text.getBytes()) == (short) 0x9C58;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
        {
            crc16 obj = new crc16((short) 0x8005, true);
            assert obj.eval(text.getBytes()) == (short) 0x443D;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
        {
            crc32 obj = new crc32(0x1EDC6F41, false);
            assert obj.eval(text.getBytes()) == 0x512B456E;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
        {
            crc32 obj = new crc32(0x04C11DB7, true);
            assert obj.eval(text.getBytes()) == 0x450EAFB0;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
        {
            crc64 obj = new crc64(0x000000000000001BL, false);
            assert obj.eval(text.getBytes()) == 0xE4FFBEA588AFC790L;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
        {
            crc64 obj = new crc64(0x42F0E1EBA9EA3693L, true);
            assert obj.eval(text.getBytes()) == 0xDA60676A5CDE0008L;
            assert obj.eval(obj.pack(text.getBytes())) == 0;
            System.out.println(Arrays.toString(obj.table()));
        }
    }
}
