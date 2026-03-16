#include <kfr/base.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>

using namespace kfr;

int main()
{
    println("KFR version: ", library_version());

    constexpr size_t taps_count = 63;
    univector<fbase, taps_count> taps;
    expression_handle<fbase> window = to_handle(window_hann(taps.size()));
    fir_lowpass(taps, 0.2, window, true);

    filter_fir<fbase, float> fir_filter(taps);

    constexpr size_t block_size = 64;
    constexpr size_t total_samples = 256;

    std::array<float, total_samples> input_storage{};
    for (size_t i = 0; i < input_storage.size(); ++i)
        input_storage[i] = static_cast<float>(i) / static_cast<float>(input_storage.size());

    std::array<float, block_size> output_storage{};

    for (size_t offset = 0; offset < total_samples; offset += block_size)
    {
        univector<float, 0> block_in = make_univector(input_storage.data() + offset, block_size);
        univector<float, 0> block_out = make_univector(output_storage.data(), block_size);

        fir_filter.apply(block_out, block_in);
        println("block ", offset / block_size, " out[0..3]: ", block_out.truncate(4));
    }

    return 0;
}
