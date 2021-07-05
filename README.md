![Linux Tests](https://github.com/gloomyzen/cards-app/workflows/Linux%20Tests/badge.svg?branch=master)
# cards-app

#### Project submodules structure:

- [src/common - Common modules for all games](https://github.com/gloomyzen/cocos2d-common)
- [adxe/cocos2dx game engine](https://github.com/gloomyzen/engine-x)

#### First of all, be sure to clone all submodules:
```bash
git clone --recurse-submodules git@github.com:gloomyzen/cards-app.git cards-app 
cd cards-app
```

#### Install cocos2dx/adxe v4:
1. Install Boost, CMake and Python 2.7 on your system
2. Install VS for win32 or XCode for macOS
3. Clone `https://github.com/gloomyzen/engine-x`
4. Just run `python setyp.py` in engine folder

#### Build from sources :
```bash
mkdir build && cd build
cmake .. -DDEBUG=1
make -j$(nproc)
```

#### Generate project file (VS, Xcode, Android studio) :

For XCode - mac project
```bash
sudo xcode-select --reset
cmake -S . -B build-mac -GXcode -DDEBUG=1
```
Then just open solution file from `build-mac`.

For XCode - ios project
```bash
sudo xcode-select --reset
cmake -S . -B build-ios -GXcode -DCMAKE_TOOLCHAIN_FILE=${ADXE_ROOT}/cmake/ios.mini.cmake -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
```

For iOS destribution
```bash
cmake -S . -B build-ios -GXcode -DCMAKE_TOOLCHAIN_FILE=${ADXE_ROOT}/cmake/ios.mini.cmake 
cmake --build build-ios --config Release --target cards-app -- -quiet -jobs 16
```

For Visual Studio Community 2019
```bash
cmake -S . -B build-win32 -G "Visual Studio 16 2019" -A Win32 -DDEBUG=1
```
Then open $(PROJECT_NAME).sln file from `build-win32` folder and set $(PROJECT_NAME) target as "startup project" in "solution explorer"

For Android studio:
android gradle plugin version: 3.6.3
gradle version: 5.6.4
NDK 21.0.6011959


#Credits
- International Phonetic Alphabet (IPA) Free Font - https://www.wfonts.com/font/ipa-font
- International Phonetic Alphabet (IPA) Free Dictionary - https://sourceforge.net/projects/free-english-to-ipa-database/
- SF Pro Text Regular Font - https://fontsfree.net/sf-pro-text-regular-font-download.html