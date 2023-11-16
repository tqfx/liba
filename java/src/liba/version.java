package liba;

/** version */
public class version {
    byte[] ctx;
    static {
        System.loadLibrary("a");
        INIT();
    }

    static final native void INIT();

    final native void init(int major, int minor, int patch);

    public String toString() {
        return major() + "." + minor() + "." + patch();
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
     * @param maj major number
     */
    public version(int maj) {
        init(maj, 0, 0);
    }

    /**
     * construct a new {@link version} object
     *
     * @param maj major number
     * @param min minor number
     */
    public version(int maj, int min) {
        init(maj, min, 0);
    }

    /**
     * construct a new {@link version} object
     *
     * @param maj major number
     * @param min minor number
     * @param pat patch number
     */
    public version(int maj, int min, int pat) {
        init(maj, min, pat);
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
     * @param maj major number
     * @return {@link version}
     */
    public final native version major(int maj);

    /***
     * get minor number for version
     *
     * @return minor number
     */
    public final native int minor();

    /***
     * set minor number for version
     *
     * @param min minor number
     * @return {@link version}
     */
    public final native version minor(int min);

    /***
     * get patch number for version
     *
     * @return patch number
     */
    public final native int patch();

    /***
     * set patch number for version
     *
     * @param pat patch number
     * @return {@link version}
     */
    public final native version patch(int pat);

    /**
     * parse function for {@link version} object
     *
     * @param ver version string to be parsed
     * @return {@link version}
     */
    public final native version parse(String ver);

    /**
     * this version not equal other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean lt(version ver);

    /**
     * this version not equal other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean gt(version ver);

    /**
     * this version not equal other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean le(version ver);

    /**
     * this version not equal other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean ge(version ver);

    /**
     * this version not equal other version
     *
     * @param ver other version to be compared
     * @return result of comparison
     */
    public final native boolean eq(version ver);

    /**
     * this version not equal other version
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
}
