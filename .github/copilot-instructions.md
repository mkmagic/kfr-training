# Copilot Instructions for KFR

## Project shape (C++20 + CMake)
- `kfr` is a header-only core; feature modules are static libs: `kfr_dsp`, `kfr_dft`, `kfr_io`, `kfr_audio` (see `docs/docs/installation.md`).
- Optional C API is built with `KFR_ENABLE_CAPI_BUILD` (requires `KFR_ENABLE_DFT`), target `kfr_capi`.
- Sources lists are auto-generated in `sources.cmake`; update via `update-sources.py` (do not edit by hand).

## Architecture + performance model
- Expression templates drive **lazy evaluation**; assignment to `univector` (or `assign_expr`) triggers execution (see `include/kfr/base/expression.hpp`, `include/kfr/base/univector.hpp`).
- Use `expression_handle` / `to_handle(...)` when you need to freeze expressions (example: window design in `examples/fir.cpp`).
- Runtime multiarch dispatch is implemented in `cmake/add_kfr_library.cmake` and `cmake/target_set_arch.cmake` and is enabled via `KFR_ENABLE_MULTIARCH` on x86.

## Build + test workflow
- CMake options to know: `ENABLE_TESTS`, `ENABLE_EXAMPLES`, `KFR_ENABLE_DFT`, `KFR_ENABLE_DSP/IO/AUDIO`, `KFR_ENABLE_MULTIARCH`, `KFR_ENABLE_CAPI_BUILD` (see `CMakeLists.txt`).
- Tests use Catch2 and are defined in `tests/CMakeLists.txt` (`all_tests`, `dft_test`, `audio_test`, `capi_test`).
- Examples live in `examples/`; some plots require Python deps from `requirements.txt` (see `examples/fir.cpp`).

## Common coding patterns
- Use `univector<T>` for owning buffers and `univector<T, 0>` / `make_univector(...)` for wrapping external buffers (see `include/kfr/base/univector.hpp`).
- For FFTs: `dft_plan` + `execute(...)` + temp buffer (see `examples/dft.cpp`).
- For FIR/IIR: use design helpers (`fir_lowpass`, `fir_bandpass`) and runtime filters (`filter_fir`, `convolve_filter`) as in `examples/fir.cpp`.

## Formatting + regen tools
- Formatting is centralized via `format-all.py` (clang-format; skips thirdparty).
- Update `sources.cmake` after adding/removing files via `update-sources.py`.
