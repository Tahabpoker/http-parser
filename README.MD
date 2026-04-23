# HFT-Oriented Zero-Copy HTTP Parser (C++)

## Overview

This project implements a **zero-copy, low-latency HTTP request parser** in modern C++, designed as a learning vehicle for **high-frequency trading (HFT)** and **performance-critical systems programming**.

The parser is built with a focus on:

* eliminating memory allocations in the parsing path
* minimizing branch mispredictions
* maximizing cache efficiency
* enabling future SIMD and kernel-bypass integration

Unlike conventional HTTP parsers, this project prioritizes **mechanical sympathy** and **predictable latency** over feature completeness.

---

## Key Features

### Zero-Copy Parsing

* Uses `std::string_view` for all parsed fields
* No heap allocations during parsing
* All fields reference the original input buffer

### Flat Finite State Machine (FSM)

* Single-pass, character-by-character parsing
* Avoids repeated scans (`find`, regex, etc.)
* Deterministic control flow

### Cache-Aware Design

* Compact parser state
* Designed to fit within CPU cache lines
* Avoids unnecessary data movement

### Branch Reduction (Foundation)

* Structured for future branchless parsing
* Predictable state transitions

### Testable and Modular

* Clean separation between parser, core utilities, and tests
* Easy to benchmark and extend

---

## Project Structure

```
hft-http-parser/
│
├── include/
│   ├── parser/
│   │   ├── http_parser.hpp
│   │   ├── http_types.hpp
│   │   └── state_machine.hpp
│   │
│   ├── core/
│
├── src/
│   ├── parser/
│   │   └── http_parser.cpp
│   │
│   └── main.cpp
│
├── tests/
│   └── test_parser.cpp
│
├── benchmarks/
│
├── build/
│
├── Makefile
├── README.md
└── .gitignore
```

---

## Build Instructions (Windows 11)

### Requirements

* MinGW-w64 (GCC)
* `mingw32-make`
* Git
* VS Code (recommended)

Verify installation:

```
g++ --version
mingw32-make --version
```

---

### Build the Project

```
mingw32-make
build\app.exe
```

---

### Run Tests

```
mingw32-make test
```

Expected output:

```
All parser tests passed
```

---

## Example Usage

```cpp
#include "parser/http_parser.hpp"
#include <string>

int main() {
    std::string raw =
        "GET /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "\r\n";

    parser::HttpParser parser;
    parser::HttpRequest request;

    if (parser.parse(raw, request)) {
        // Access parsed data (zero-copy views)
        auto method = request.method;
        auto uri = request.uri;
    }
}
```

---

## Zero-Copy Design

The parser does not own memory.

All parsed fields are `std::string_view`:

* They point directly into the input buffer
* No copying or allocation occurs

### Important Constraint

The input buffer **must remain valid** while the parsed result is used.

Valid:

```
std::string raw = "...";
parser.parse(raw, request);
```

Invalid:

```
parser.parse(std::string("GET ..."), request); // dangling views
```

---

## Parsing Model

The parser uses a **flat finite state machine** with states such as:

* METHOD
* URI
* VERSION
* HEADER_KEY
* HEADER_VALUE

It processes the input in a **single linear pass (O(n))**.

---

## Performance Philosophy

This project follows principles used in low-latency systems:

* Avoid allocations in hot paths
* Prefer data locality over abstraction
* Minimize branches and unpredictable control flow
* Design for cache efficiency
* Treat parsing as a streaming problem

---

## Future Improvements

The current implementation is a foundation. Planned enhancements include:

### SIMD Acceleration

* AVX2/SSE-based delimiter scanning (`\r\n`, `:`)
* Vectorized whitespace trimming

### Branchless Parsing

* Lookup tables (LUTs) for character validation
* Reduced conditional branching

### Memory Optimization

* Custom allocators for header storage
* Pre-allocated buffers

### Networking Integration

* Winsock-based ingestion (Windows)
* Transition to:

  * DPDK
  * kernel bypass
  * zero-copy networking

### Lock-Free Structures

* SPSC ring buffers for streaming input
* Disruptor-style pipelines

---

## Benchmarking (Planned)

Future benchmarks will measure:

* latency per request (ns)
* branch miss rate
* cache miss rate
* throughput under load

Tools:

* `perf` (Linux, later stage)
* Windows performance counters

---

## Learning Objectives

This project is designed to build intuition in:

* low-level C++ performance engineering
* memory layout and cache behavior
* parsing under strict latency constraints
* systems-level thinking (HFT-style design)

---

## Limitations

* Only supports basic HTTP request parsing
* No chunked encoding or full HTTP compliance
* No TLS/HTTPS handling
* Not production-ready

---

## Resume Description

Built a zero-copy HTTP parser in C++ using a flat finite-state machine, designed for low-latency systems. Eliminated heap allocations in the parsing path using `std::string_view`, and structured the parser for cache efficiency and SIMD acceleration.

---

## License

MIT License

---

## Author

Tahab Poker
