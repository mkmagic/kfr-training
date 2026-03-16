# 01 — What is KFR?

KFR is a modern C++ DSP framework focused on **high performance** and **portable SIMD**.
It lets you write signal-processing code in a math-like style while still generating fast,
vectorized machine code for x86 and ARM. The core ideas to keep in mind are:

- **Expressions are lazy**: building expressions is cheap; they evaluate only when you assign.
- **`univector` is the primary buffer**: owning (`univector<T>`) or a non-owning view (`univector_ref<T>`; also exposed as `univector<T, 0>` / `make_univector(...)`).
- **SIMD-first design**: many ops map to CPU vector lanes via `kfr::vec`.

KFR is used to build real-time DSP pipelines (filters, FFTs, resampling), and its APIs
are designed to be composable and fast without forcing you into low-level intrinsics.

## Key terms (plain English)
- **Expression**: a recipe for computation that hasn’t executed yet.
- **Lazy evaluation**: compute only when needed (assignment / `assign_expr`).
- **`univector`**: KFR’s buffer type; use it for storage and to trigger evaluation.
- **View / ref**: `univector_ref<T>` (aka `univector<T, 0>`) wraps existing memory without copying.
- **SIMD**: Single Instruction, Multiple Data — one instruction processes several samples.

## Mini examples

### 1) Lazy expressions become samples on assignment
```cpp
auto expr = sin(linspace(0.0f, c_pi<float, 2> * 2.0f, 16)); // 2-cycle tone, lazy
univector<float> signal = truncate(expr, 16);              // now it evaluates
```

### 2) Views avoid copies
```cpp
std::array<float, 32> storage{};
auto view = make_univector(storage); // view into existing data
view = scalar(0.5f);                  // fills storage without allocating
```

### 3) SIMD in one line
```cpp
vec<float, 4> a{1.f, 2.f, 3.f, 4.f};
vec<float, 4> b = a + 1.f; // add 1 to 4 values in parallel
```

## Build and run this chapter
```bash
cmake -S . -B build-training -DENABLE_TRAINING=ON -DENABLE_TESTS=OFF
cmake --build build-training --target kfr_training_basics
```

## Exercises
1. Change the signal length to 256 and print the first 8 samples.
2. Replace the sine wave with `square()` (hint: `kfr/dsp.hpp`).
3. Wrap a `std::array<float, 32>` with `univector_ref<float>` (or `univector<float, 0>`) and scale it by 0.5.
4. SIMD: replace `vec<float, 4>` with `vec<float, 8>` and adjust printing.

## Where to explore next
- Source: `include/kfr/base/univector.hpp`, `include/kfr/base/expression.hpp`
- SIMD: `include/kfr/simd/vec.hpp`
