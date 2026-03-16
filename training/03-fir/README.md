# 03 — FIR Filters (Finite Impulse Response)

FIR filters are a way to **shape a signal** by mixing each sample with its neighbors.
Think of it like a weighted moving average: you choose a set of weights (“taps”), and
each output sample is the sum of nearby input samples multiplied by those taps.

**Linear phase** simply means “all frequencies are delayed by the same amount.”
In plain terms, the waveform shape stays intact — it doesn’t get skewed or smeared
in time. This is often important for audio and SDR because transients and timing
remain faithful after filtering.

KFR gives you both **design helpers** (to compute taps) and **runtime filters** (to process
samples) with SIMD acceleration under the hood.

## DSP background (short version)
- **Taps**: the FIR coefficients; more taps = sharper cutoff but more CPU cost.
- **Windowed design**: start with an ideal filter, then apply a window to control ripple.
- **Linear phase**: FIR filters can preserve waveform shape (important for audio).

## Key KFR features used here
- `fir_lowpass`, `fir_highpass`, `fir_bandpass`, `fir_bandstop`
- Window functions via `window_hann`, `window_kaiser`, etc.
- Runtime filtering with `filter_fir` or the expression-style `fir(...)`

## Mini examples

### 1) Design taps with a window
```cpp
univector<fbase, 63> taps;
auto win = to_handle(window_hann(taps.size()));
fir_lowpass(taps, 0.2, win, true);
```

### 2) Apply a filter to a signal
```cpp
filter_fir<fbase, float> fir_filter(taps);
univector<float> out;
fir_filter.apply(out, in);
```

## Build and run this chapter
```bash
cmake --build build-training --target kfr_training_fir
```

## Plotting the signal (optional)
This example uses `plot_save(...)` to write SVG plots before and after filtering.
It requires Python dependencies from `requirements.txt`:

```bash
./training/setup-venv.sh
```

`plot_save(...)` depends on the local `dspplot` package, which the setup script installs.

You can also run the full plot flow with the helper script:

```bash
./training/03-fir/run-plots.sh
```

Plots are written to `svg/` at the repo root.

## Exercises
1. Change to a highpass filter and compare the output energy.
2. Increase taps to 127 and observe the sharper transition.
3. Replace `filter_fir` with the expression-style `fir(...)`.
4. Switch to `window_kaiser` and compare tap values.

## Where to explore next
- FIR design: `include/kfr/dsp/fir_design.hpp`
- FIR runtime filter: `include/kfr/dsp/fir.hpp`
