# 02 — Expressions, handles, and reusable windows

In KFR, **expressions** are lazy recipes. This is great for performance,
but sometimes you need to **freeze** an expression so it can be reused
without re-evaluating or capturing dangling references.

That’s what `expression_handle` does: it **owns the expression and its data** so you can
reuse it safely. Many expressions capture references to temporary objects or input ranges.
If you pass a raw lazy expression directly into a function that stores it for later use,
those references can dangle after the call returns. The handle makes the expression
explicitly owned and stable for reuse.

## Key terms
- **Expression template**: a compile-time representation of a computation.
- **Handle**: an owning wrapper that keeps an expression alive.
- **Window**: a shaped curve applied to filter taps to control ripple.

## Mini examples

### 1) Lazy window expression
```cpp
auto win_expr = window_hann(64); // lazy
```

### 2) Freeze the window for reuse
```cpp
expression_handle<fbase> win = to_handle(window_hann(64));
fir_lowpass(taps, 0.2, win, true);
```

### Why not pass the lazy window directly?
`window_hann(64)` is a lazy expression object. It may refer to temporary state that
only exists for the duration of the call. If a function stores the window for later
or evaluates it in multiple steps, those references may be invalid.
`to_handle(...)` turns the expression into an owned, reusable object with a stable lifetime.

### Rule of thumb: when to freeze a lazy expression
Freeze with `to_handle(...)` when:
- You **store** the expression in a class/struct for later use.
- You **reuse** the same expression across multiple calls or frames.
- The expression is built from **temporaries** (e.g., `window_hann(taps.size())`).
- A function expects an expression whose lifetime must **outlive the call**.

You can usually keep it lazy when you build and assign it **immediately** in the same statement.

## Build and run this chapter
```bash
cmake --build build-training --target kfr_training_expressions
```

## Exercises
1. Replace `window_hann` with `window_kaiser` and re-run.
2. Change the cutoff from `0.2` to `0.1` and observe the tap values.
3. Store the window in a variable without `to_handle` and compare behavior.
4. Increase `taps` to 128 and print the first 16 taps.

## Where to explore next
- Expression system: `include/kfr/base/expression.hpp`
- Windows: `include/kfr/dsp/window.hpp`
