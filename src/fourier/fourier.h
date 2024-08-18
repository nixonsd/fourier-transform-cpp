#pragma once

#define IsNotImplemented private

#include <vector>
#include <iterator>
#include <iostream>
#include <complex>
#include <valarray>
#include <numeric>
#include <algorithm>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

const double PI = 3.141592653589793238460;

class Fourier {
public:
    /**
     * @brief Fast Fourier Transform
     * 
     * @param x Input samples
     * @param offsetRemoval Should be set if mean subtraction is required (for DC component removal)
     * @param applyWindow Should be set if the Hann Window function needs to be applied
     * @return CArray Array of complex number results
     */
    static CArray computeFFT(std::vector<double> x, bool offsetRemoval = false, bool applyWindow = false);

IsNotImplemented:
    /**
     * @brief Inverse Fast Fourier Transform (Not Implemented)
     * 
     * @param x Complex array for in-place transformation
     */
    static void computeInverseFFT(CArray& x);

private:
    /**
     * @brief The primary logic of Fast Fourier Transform. Cooley-Tukey FFT implementation (in-place)
     * 
     * @param x Complex array for in-place transformation
     */
    static void performFFT(CArray& x);

    /**
     * @brief Calculate the Hann window
     * 
     * @param x Input samples to apply the window function
     */
    static void applyHannWindow(std::vector<double>& x);

    /**
     * @brief DC offset removal
     * 
     * @param x Input samples for mean subtraction
     */
    static void removeDCOffset(std::vector<double>& x);
};
