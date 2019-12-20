# VL1-emulator
An emulator of Casio VL-Tone VL1, based on source code by PolyValens

[![Build Status](https://travis-ci.com/linuxmao-org/VL1-emulator.svg?branch=master)](https://travis-ci.com/linuxmao-org/VL1-emulator)

Home page: http://www.polyvalens.com/blog/vl-1/

The information from the official page may not represent exactly the current state of this fork.

## Downloads

**Development**

- All: download from [Automatic builds](https://github.com/linuxmao-org/VL1-emulator/releases/tag/automatic).

## Build instructions

1. Obtain prerequisites

Install needed packages:

- `git`
- `build-essential`
- `pkg-config`
- `libx11-dev`
- `libcairo2-dev`
- `libjack-jackd2-dev` or `libjack-dev`
- `mesa-common-dev`

2. Check out the repository and submodules

```
git clone https://github.com/linuxmao-org/VL1-emulator.git
cd VL1-emulator
git submodule update --init
```

3. Compile

```
make
```

4. Install

```
sudo make install  # to install in system directories, or
make install-user  # to install in the home directory
```
