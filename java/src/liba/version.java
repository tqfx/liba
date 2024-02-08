package liba;

import java.nio.ByteBuffer;

/** version */
public class version {
    /** algorithm library version major */
    public static final int MAJOR;
    /** algorithm library version minor */
    public static final int MINOR;
    /** algorithm library version patch */
    public static final int PATCH;
    /** algorithm library version tweak */
    public static final int TWEAK;
    ByteBuffer ctx;
    static {
        System.loadLibrary("a");
        MAJOR = 0;
        MINOR = 0;
        PATCH = 0;
        TWEAK = 0;
        INIT();
    }

    static final native void INIT();

    final native void init(int major, int minor, int third);

    /**
     * return string representation of version
     */
    public String toString() {
        String s = major() + "." + minor() + "." + third();
        int extra = extra();
        if (extra > 0) {
            s += "." + extra;
        }
        return s;
    }

    /**
     * construct a new {@link version} object
     */
    public version() {
        init(0, 0, 0);
    }

    /**
     * construct a new {@link version} object
     *
     * @param major major number
     */
    public version(int major) {
        init(major, 0, 0);
    }

    /**
     * construct a new {@link version} object
     *
     * @param major major number
     * @param minor minor number
     */
    public version(int major, int minor) {
        init(major, minor, 0);
    }

    /**
     * construct a new {@link version} object
     *
     * @param major major number
     * @param minor minor number
     * @param third third number
     */
    public version(int major, int minor, int third) {
        init(major, minor, third);
    }

    /***
     * get major number for version
     *
     * @return major number
     */
    public final native int major();

    /***
     * set major number for version
     *
     * @param major major number
     * @return {@link version}
     */
    public final native version major(int major);

    /***
     * get minor number for version
     *
     * @return minor number
     */
    public final native int minor();

    /***
     * set minor number for version
     *
     * @param minor minor number
     * @return {@link version}
     */
    public final native version minor(int minor);

    /***
     * get third number for version
     *
     * @return third number
     */
    public final native int third();

    /***
     * set third number for version
     *
     * @param third third number
     * @return {@link version}
     */
    public final native version third(int third);

    /***
     * get extra number for version
     *
     * @return extra number
     */
    public final native int extra();

    /***
     * set extra number for version
     *
     * @param extra extra number
     * @return {@link version}
     */
    public final native version extra(int extra);

    /**
     * parse for {@link version} object
     *
     * @param ver version string to be parsed
     * @return {@link version}
     */
    public final native version parse(String ver);

    /**
     * this version is less than other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean lt(version ver);

    /**
     * this version is greater than other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean gt(version ver);

    /**
     * this version is less than or equal to other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean le(version ver);

    /**
     * this version is greater than or equal to other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean ge(version ver);

    /**
     * this version is equal to other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean eq(version ver);

    /**
     * this version is not equal to other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean ne(version ver);

    /**
     * compare this version with other versions
     *
     * @param ver other version to be compared
     * @return relationship between the versions
     */
    public final native int cmp(version ver);

    /**
     * algorithm library version check
     *
     * @param major major number
     * @param minor minor number
     * @param patch patch number
     * @return -3(&lt;major),-2(&lt;minor),-1(&lt;patch),0,+1(&gt;patch),+2(&gt;minor),+3(&gt;major)
     */
    public static final native int check(int major, int minor, int patch);
}
