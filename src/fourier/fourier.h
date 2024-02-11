#pragma once

#define IsNotImplemented private

#include <vector>
#include <iterator>
#include <iostream>
#include <complex>
#include <valarray>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

const double PI = 3.141592653589793238460;

class Fourier {
  /**
   * The primary logic of Fast Fourier Transform. Cooley-Tukey FFT implementation (in-place)
   */
  static void _fft(CArray& x);
  /**
   * Calculate the Hann window
   */
  static void _window(std::vector<double>& x);
  /**
   * DC offset removal
   */
  static void _offsetRemoval(std::vector<double>& x);

  public:
  /**
   * @brief Fast Fourier Transform
   * 
   * @param x input samples
   * @param offsetRemoval should be set if mean subtraction is required (for DC component removal)
   * @param window should be set if the Hann Window function needs to be applied
   * @return CArray array of complex number results
   */
  static std::valarray<Complex> fft(std::vector<double> x, bool offsetRemoval = false, bool window = false);

  IsNotImplemented:
  static void ifft(CArray& x);
};
