
# A demo project of how to use Eigen in STM32

## Version
- Eigen: 3.3.7
- CMake >= 3.5
- GCC: 8.3.1
- MDK: 5.28

## Build
- GCC & CMake
```
mkdir build & cd build
cmake ..
make -j
```

- Keil MDK (AC6)

## Tips
- Use -O3 to make Eigen run fast, if you don't need to debug online.There will be a huge difference in running time between -O0 and -O3.

- Lower version of gcc may got some error when compile Eigen.