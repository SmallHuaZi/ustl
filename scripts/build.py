# Automatically build with python

import os
import re
import sys
import shutil
import subprocess


CMAKE_CACHE_ARGS = ["cmake", ".."]
CMAKE_BUILD_ARGS = ["cmake", "--build", "."]
CMAKE_INSTALL_ARGS = ["cmake", "--install", ".", "--prefix"]



# When starting tests, update the version number of the ustl version
def update_version_at_tests():
    pattern = "[0-9][.][0-9][.][0-9][ ][LANGUAGES]{9}[ ][C][ ][CXX]{3}"
    new_ver = "ustl-"
    with open("ustl/CMakeLists.txt", "r") as f:
        tmp = f.read()
        new_ver += re.search(pattern, tmp).group()[0:5]

    if new_ver.__eq__(""):
        print("read ustl version from ustl/CMakeLists.txt failure")
        os.abort()

    pattern = "[ustl]{4}[-][0-9][.][0-9][.][0-9]"
    content = ""
    old_ver = 0
    with open("tests/CMakeLists.txt", "r") as f:
        content = f.read()
        old_ver = re.search(pattern, content).group()

    new_ver = new_ver.replace(" ", "")
    old_ver = old_ver.replace(" ", "")
    print("new ustl version: ", new_ver)
    print("old ustl version: ", old_ver)
    content = content.replace(old_ver, new_ver)

    with open("tests/CMakeLists.txt", "w") as f:
        f.write(content)
 


def build_by_cmake(wd: str, ins: bool):
    root_wd = os.getcwd()
    os.chdir(wd)

    work_dir = "target"
    if os.path.exists("build"):
        work_dir = "build"
        shutil.rmtree(work_dir)
    elif os.path.exists("target"):
        work_dir = "target" 
        shutil.rmtree(work_dir)

    os.mkdir(work_dir)

    cmake = subprocess.Popen(CMAKE_CACHE_ARGS, cwd=work_dir)
    cmake.wait() 
    cmake = subprocess.Popen(CMAKE_BUILD_ARGS, cwd=work_dir)
    cmake.wait()

    if ins:
        cmake = subprocess.Popen(CMAKE_INSTALL_ARGS, cwd=work_dir)
        cmake.wait()

    os.chdir(root_wd)



def main():
    build_ustl: bool = False
    build_test: bool = False
    install_dir = "./ustl"
    envs = sys.argv

    for idx, arg in enumerate(envs):
        if arg.__eq__("-ustl"):
            build_ustl = True

        if arg.__eq__("-test"):
            update_version_at_tests()
            build_test = True

        if arg.__eq__("-d"):
            if not os.path.isabs(envs[idx + 1]):
                print("", envs[idx + 1])
                install_dir = os.path.abspath(envs[idx + 1])
                print(install_dir)
            elif os.path.isabs(envs[idx + 1]):
                install_dir = envs[idx + 1]
    
    if not os.path.exists(install_dir):
        print("No such directory or file: ", install_dir)
        os.abort()

    if not build_test and not build_ustl:
        print("you must specify the target \n\t1.ustl \n\t2.test]")
        os.abort()

    CMAKE_INSTALL_ARGS.append(install_dir)
    if  build_ustl:
        build_by_cmake("ustl", True)
    if build_test:
        build_by_cmake("tests", False)



if __name__ == "__main__":
    main()