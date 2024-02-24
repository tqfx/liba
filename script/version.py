#!/usr/bin/env python
import time, os, re


class version(object):
    def __init__(self, release="0.0.0") -> None:
        self.major, self.minor, self.patch = re.findall(r"(\d+)\.(\d+)\.(\d+)", release)[0]
        self.version = self.major + "." + self.minor + "." + self.patch
        self.tweak = time.strftime("%Y%m%d")
        self.release = release

    @staticmethod
    def load(file):
        if not os.path.exists(file):
            print("missing {}".format(file))
            return ""
        with open(file, "r", encoding="UTF-8") as f:
            return f.read()

    @staticmethod
    def save(file, text):
        with open(file, "wb") as f:
            f.write(text.encode("UTF-8"))

    def update_version(self, file, feild="version"):
        text = self.load(file)
        res = re.findall(
            r"{}([^0-9A-Za-z]+)([0-9]+)\.([0-9]+)\.([0-9]+)([.\w-]*)".format(feild), text
        )
        if res:
            release = "{}.{}.{}{}".format(res[0][1], res[0][2], res[0][3], res[0][4])
            if self.release != release:
                line0 = "{}{}{}".format(feild, res[0][0], release)
                line1 = "{}{}{}".format(feild, res[0][0], self.release)
                self.save(file, text.replace(line0, line1))

    def update_version_h(self, file):
        text = text_ = self.load(file)
        res = re.findall(r"#define A_VERSION_MAJOR (\d+)", text)
        if res and self.major != res[0]:
            line0 = "#define A_VERSION_MAJOR {}".format(res[0])
            line1 = "#define A_VERSION_MAJOR {}".format(self.major)
            text = text.replace(line0, line1)
        res = re.findall(r"#define A_VERSION_MINOR (\d+)", text)
        if res and self.minor != res[0]:
            line0 = "#define A_VERSION_MINOR {}".format(res[0])
            line1 = "#define A_VERSION_MINOR {}".format(self.minor)
            text = text.replace(line0, line1)
        res = re.findall(r"#define A_VERSION_PATCH (\d+)", text)
        if res and self.patch != res[0]:
            line0 = "#define A_VERSION_PATCH {}".format(res[0])
            line1 = "#define A_VERSION_PATCH {}".format(self.patch)
            text = text.replace(line0, line1)
        res = re.findall(r"#define A_VERSION_TWEAK (\d+)", text)
        if res and self.tweak != res[0]:
            line0 = "#define A_VERSION_TWEAK {}".format(res[0])
            line1 = "#define A_VERSION_TWEAK {}".format(self.tweak)
            text = text.replace(line0, line1)
        if text != text_:
            self.save(file, text)

    def update_version_ac(self, file):
        text = text_ = self.load(file)
        res = re.findall(r"\[version_major\], \[(\d+)\]", text)
        if res and self.major != res[0]:
            line0 = "[version_major], [{}]".format(res[0])
            line1 = "[version_major], [{}]".format(self.major)
            text = text.replace(line0, line1)
        res = re.findall(r"\[version_minor\], \[(\d+)\]", text)
        if res and self.minor != res[0]:
            line0 = "[version_minor], [{}]".format(res[0])
            line1 = "[version_minor], [{}]".format(self.minor)
            text = text.replace(line0, line1)
        res = re.findall(r"\[version_patch\], \[(\d+)\]", text)
        if res and self.patch != res[0]:
            line0 = "[version_patch], [{}]".format(res[0])
            line1 = "[version_patch], [{}]".format(self.patch)
            text = text.replace(line0, line1)
        if text != text_:
            self.save(file, text)

    def update_autogen(self, file):
        text = self.load(file)
        age = str(int(self.minor) - int(self.major))
        version = self.minor + ":" + self.patch + ":" + age
        res = re.findall(r"version-info ([0-9:]+)", text)
        if res and version != res[0]:
            line0 = "version-info {}".format(res[0])
            line1 = "version-info {}".format(version)
            self.save(file, text.replace(line0, line1))


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("version")
    args = parser.parse_known_args()
    v = version(args[0].version)
    v.update_version("doc/Doxyfile", "PROJECT_NUMBER")
    v.update_version("cmake/Project.cmake", "VERSION")
    v.update_version("java/src/liba.java", "VERSION")
    v.update_version("lua/liba.lua", "VERSION")
    v.update_version_h("include/a/version.h")
    v.update_version("javascript/package.json")
    v.update_version_ac("script/configure.ac")
    v.update_autogen("script/autogen")
    v.update_version("Cargo.toml")
    v.update_version("conanfile.py")
    v.update_version("meson.build")
    v.update_version("setup.cfg")
    v.update_version("xmake.lua")
