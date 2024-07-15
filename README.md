# design_patterns

![Build status](https://github.com/mapi-ng/design_patterns/actions/workflows/cmake-multi-platform.yml/badge.svg) [![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=mapi-ng_design_patterns&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=mapi-ng_design_patterns)

## About

Implementations of various design patterns

## Prerequisites
- Internet connection (for CMake FetchContent module)
- CMake version at least 3.28.3
- Compiler with support for C++23

## Build instructions
From command line, execute the commands below (replace Debug by Release if relevant):

```
mkdir build
cmake -S. -B./build
cmake --build ./build --config Debug
```

## Running tests

From the build directory, run:
```
ctest -C Debug --output-on-failure
```