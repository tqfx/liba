package liba;

/** version */
public class version {
    static {
        System.loadLibrary("a");
    }
    /** major number */
    public int major = 0;
    /** minor number */
    public int minor = 0;
    /** patch number */
    public int patch = 0;

    /**
     * construct a new {@link version} object
     */
    public version() {
    }

    /**
     * construct a new {@link version} object
     *
     * @param maj major number
     */
    public version(int maj) {
        major = maj;
    }

    /**
     * construct a new {@link version} object
     *
     * @param maj major number
     * @param min minor number
     */
    public version(int maj, int min) {
        major = maj;
        minor = min;
    }

    /**
     * construct a new {@link version} object
     *
     * @param maj major number
     * @param min minor number
     * @param pat patch number
     */
    public version(int maj, int min, int pat) {
        major = maj;
        minor = min;
        patch = pat;
    }

    public String toString() {
        return major + "." + minor + "." + patch;
    }

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
