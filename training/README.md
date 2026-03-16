# KFR Training

This training track is for junior C++ developers onboarding to KFR.
It pairs short explanations with runnable examples and exercises that point back to KFR source and docs.

## Learning Path
1. `01-basics`: `univector`, `univector<T,0>` refs, lazy evaluation, SIMD basics.
2. `02-expressions`: expression templates, `expression_handle`, windowed FIR design.
3. `03-fir`: FIR design + runtime filtering with `filter_fir`.
4. `04-dft`: `dft_plan`, temp buffers, magnitude in dB.
5. `05-realtime`: block processing, wrapping external buffers.

## Build (from repo root)
Enable training in the root build:

```bash
cmake -B build -DENABLE_TRAINING=ON
cmake --build build
```

Executables are placed in your build output bin directory.

## Python venv for plots (recommended)
Some examples use `plot_save(...)` and require Python packages from `requirements.txt`.
Use the helper script to create a local venv under `training/.venv`:

```bash
./training/setup-venv.sh
```

## References
- KFR docs: https://www.kfrlib.com/docs/latest/
- KFR examples: `examples/`
- Expression system: `include/kfr/base/expression.hpp`
- `univector`: `include/kfr/base/univector.hpp`
