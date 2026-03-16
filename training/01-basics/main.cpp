#include <kfr/base.hpp>
#include <kfr/simd.hpp>

using namespace kfr;

int main()
{
    println("KFR version: ", library_version());

    constexpr size_t size = 16;

    // Lazy expression: this is not evaluated yet.
    // DSP view: generate a single-tone sine wave over `size` samples.
    // `linspace` builds a phase ramp from 0 to 4π (2 full cycles); `sin` maps phase -> samples.
    // This stays as an expression until it is assigned to a buffer.
    auto expr = sin(linspace(0.0f, c_pi<float, 2> * 2.0f, size));

    // Evaluation happens on assignment
    univector<float> signal = truncate(expr, size);

    // Owning buffer
    univector<float> owned = signal * 0.5f;

    // Non-owning view over external memory. 
    // Any container that has .data() and .size() can be used.
    std::array<float, size> external{};
    auto external_view = make_univector(external);
    external_view = owned;

    println("owned: ", owned);
    println("external_view: ", external_view);

    // SIMD basics: Single Instruction, Multiple Data.
    // `vec<float, 4>` represents 4 lanes processed in parallel with one instruction,
    // similar to how KFR speeds up DSP kernels on CPU vector units.
    vec<float, 4> a{ 1.f, 2.f, 3.f, 4.f };
    vec<float, 4> b = a + 1.f;
    println("simd a: ", a);
    println("simd b: ", b);

    return 0;
}
