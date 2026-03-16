#include <kfr/base.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>

using namespace kfr;

int main()
{
    println("KFR version: ", library_version());

    univector<fbase, 64> taps;

    // Window expression is lazy; freeze it so it owns its data and can be reused safely
    expression_handle<fbase> win = to_handle(window_hann(taps.size()));

    // Design a lowpass FIR: window shapes the taps to control ripple and transition width
    fir_lowpass(taps, 0.2, win, true);

    println("First 8 taps: ", taps.truncate(8));

    return 0;
}
