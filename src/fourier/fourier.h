#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <complex>
#include <valarray>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

const double PI = 3.141592653589793238460;

class Fourier {

  public:
  static void fft(CArray& x);
  static void ifft(CArray& x);
};