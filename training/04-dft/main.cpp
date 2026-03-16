#include <kfr/base.hpp>
#include <kfr/dft.hpp>
#include <kfr/io.hpp>

using namespace kfr;

int main()
{
    println("KFR version: ", library_version());

    constexpr size_t size = 64;

    univector<complex<fbase>, size> input = sin(linspace(0.0, c_pi<fbase, 2> * 4.0, size));
    univector<complex<fbase>, size> output = scalar(qnan);

    dft_plan<fbase> dft(size);
    univector<u8> temp(dft.temp_size);

    dft.execute(output, input, temp);
    output = output / size;

    univector<fbase, size> magnitude = amp_to_dB(cabs(output));
    println("dB[0..7]: ", magnitude.truncate(8));

    return 0;
}
