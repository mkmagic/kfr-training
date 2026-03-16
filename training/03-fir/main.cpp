#include <kfr/base.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>

using namespace kfr;

#ifndef PYTHON_IS_INSTALLED
#define PYTHON_IS_INSTALLED 1
#endif

int main()
{
    println("KFR version: ", library_version());

    constexpr size_t taps_count = 63;
    univector<fbase, taps_count> taps;
    expression_handle<fbase> window = to_handle(window_hann(taps.size()));

    fir_lowpass(taps, 0.2, window, true);

    univector<float> noise = truncate(gen_random_range(random_init(1, 2, 3, 4), -1.f, +1.f), 256);

    filter_fir<fbase, float> fir_filter(taps);
    univector<float> filtered;
    fir_filter.apply(filtered, noise);

    println("noise[0..7]: ", noise.truncate(8));
    println("filtered[0..7]: ", filtered.truncate(8));

#if PYTHON_IS_INSTALLED
    plot_save("fir_input_noise", noise, "title='Input noise', div_by_N=True");
    plot_save("fir_output_noise", filtered, "title='Filtered noise', div_by_N=True");
    println("SVG plots have been saved to svg directory");
#endif

    return 0;
}
