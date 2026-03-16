# 05 — Realtime-Style Block Processing

## Goals
- Wrap external buffers with `univector<T,0>`.
- Process audio in fixed-size blocks.
- Reuse stateful filters across blocks.

## Files
- `main.cpp`
- Reference: `include/kfr/base/univector.hpp`, `include/kfr/dsp/fir.hpp`.

## Exercises
1. Change `block_size` to 128 and verify output length.
2. Replace the lowpass with a bandpass filter.
3. Keep a running RMS meter across blocks.
