#!/usr/bin/env python
# -*- coding: utf-8 -*-
from subprocess import Popen
import urllib.request
import urllib.parse
import urllib.error
import sys, os, re
import ssl, json


class godbolt(object):
    ssl._create_default_https_context = ssl._create_unverified_context
    compiler = {"CC": "", "CXX": "", "CFLAGS": "", "CXXFLAGS": ""}
    home_url = "https://godbolt.org"
    headers = {
        "Content-Type": "application/json;charset=utf-8",
        "Accept": "application/json;charset=utf-8",
        "User-Agent": "godbolt",
    }

    def languages(self):
        url = self.home_url + "/api/languages"
        request = urllib.request.Request(url, headers=self.headers)
        reponse = urllib.request.urlopen(request)
        text = reponse.read().decode("UTF-8")
        sys.stdout.write(text)
        return 0

    def compilers(self, lang):
        url = self.home_url + "/api/compilers/" + lang
        request = urllib.request.Request(url, headers=self.headers)
        reponse = urllib.request.urlopen(request)
        text = reponse.read().decode("UTF-8")
        sys.stdout.write(text)
        return 0

    def compile(self, source, output=""):
        if os.path.splitext(source)[-1] != ".c":
            option = self.compiler["CXXFLAGS"]
            compiler = self.compiler["CXX"]
        else:
            option = self.compiler["CFLAGS"]
            compiler = self.compiler["CC"]
        if not compiler:
            return False
        if not output:
            output = source + ".s"
        with open(source, "r") as f:
            source = f.read()
        data = json.dumps(
            {
                "source": source,
                "options": {
                    "userArguments": option,
                },
            }
        ).encode("UTF-8")
        url = self.home_url + "/api/compiler/" + compiler + "/compile"
        request = urllib.request.Request(url, data=data, headers=self.headers)
        reponse = urllib.request.urlopen(request)
        text = reponse.read()
        with open(output, "wb") as f:
            f.write(text)
        text = text.decode("UTF-8")
        if "<Compilation failed>" not in text:
            return True
        return text.split("Standard error:")[-1]


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("-S")
    parser.add_argument("-O")
    parser.add_argument("--cc", default="")
    parser.add_argument("--cxx", default="")
    parser.add_argument("--cflags", default="")
    parser.add_argument("--cxxflags", default="")
    parser.add_argument("-l", "--lang", default="")
    args = parser.parse_known_args()
    if not args[0].O:
        args[0].O = "build"
    if not args[0].S:
        args[0].S = "src"
    o = godbolt()
    if args[0].lang:
        exit(o.compilers(args[0].lang))
    args[0].S = os.path.relpath(args[0].S)
    args[0].O = os.path.relpath(args[0].O)
    single = os.path.join(os.path.dirname(__file__), "single.py")
    single = [sys.executable, single, "-Iinclude", "-C", args[0].S]
    single += ["-O", os.path.join(args[0].O, args[0].S)]
    Popen(single).wait()
    os.chdir(args[0].O)
    o.compiler["CC"] = args[0].cc
    o.compiler["CFLAGS"] = args[0].cflags
    o.compiler["CXX"] = args[0].cxx
    o.compiler["CXXFLAGS"] = args[0].cxxflags
    for dirpath, dirnames, filenames in os.walk(args[0].S):
        for filename in filenames:
            source = os.path.join(dirpath, filename)
            prefix, suffix = os.path.splitext(source)
            if suffix in (".c", ".cc", ".cpp", ".cxx"):
                err = o.compile(source)
                if err != False:
                    sys.stdout.write(source)
                if type(err) == type(""):
                    sys.stdout.write(err)  # type: ignore
                if err != False:
                    sys.stdout.write('\n')
