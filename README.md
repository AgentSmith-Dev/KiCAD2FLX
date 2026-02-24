# KiCAD2FLX

Command line tool to convert KiCad `.pos` files for Essemtec FLX by mapping/shortening the `Package` column.

## Build

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Run

```bash
./build/KiCAD2FLX KiCAD.pos FLX.pos [KiCADPackage2FLX.txt]
```

If the mapping file argument is omitted, `KiCADPackage2FLX.txt` is used.
