# `J++ | jpp`

A collection of useful C++ code snippets.

## Installation/Requirements

- A decent C++17 compiler

## File structure

```
├── build.sh                              // Build script
├── CMakeLists.txt
├── src                                   // Few examples
│   └── main.cpp
├── include
│   └── jpp
│       ├── branch_over.hpp               // Switch-over-enum generator
│       ├── function_helpers.hpp          // Helpers for manipulating functions
│       ├── match_overload.hpp            // ML-style match implementation
│       ├── parameter_pack_reduction.hpp  // Arbitrary parameter pack reductor
│       └── unroll.hpp                    // Arbitrary lambda unroller
└── README.md                             // This
```

```
├── LICENSE.txt
├── Makefile
├── config.mk                             //  Makefile config file
├── README.md                             //  This
├── include
│   └── jpp
│       ├── branch_over.hpp               //  Switch-over-enum generator
│       ├── function_helpers.hpp          //  Helpers for manipulating functions
│       ├── match_overload.hpp            //  ML-style match implementation
│       ├── parameter_pack_reduction.hpp  //  Arbitrary parameter pack reductor
│       └── unroll.hpp                    //  Arbitrary lambda unroller
├── src                                   //
│   └── main.cpp
└── tests                                 //  Tests
    │
   ...
```
