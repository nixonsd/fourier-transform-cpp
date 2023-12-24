#include <iostream>
#include <vector>
#include <iomanip>

#include "fourier.h"

#include <matplot/matplot.h>

int main() {
  // input values P (timestamp, value of the measurment)
  std::vector<Complex> values;
  
  // sin(2*T*pi*t);
  double fmax = 50.0;
  double samplingFreq = 1000;

  double T = 1/samplingFreq;

  double tmax = 1.5;
  double L = samplingFreq * tmax;

  double t = 0;

  // std::valarray<double> test2 = {0, 1, 2, 3, 4, 5};
  // std::valarray<double> test3 = test2[std::slice(0, test2.size() / 2, 2)]; 
  // std::valarray<double> test4 = test2[std::slice(1, test2.size() / 2, 2)]; 

  // for (const double x: test4) {
  //   std::cout << x << std::endl;
  // }

  // for (; t < tmax; t+=T) {
  //   // values.push_back({t, 0});
  //   values.push_back({2 * sin(2*fmax*PI*t), 0});
  // }

  // const int n = pow(2, int(ceil(log2(values.size()))));
  // for (int i = values.size(); i < n; i++, t+=T) {
  //   values.push_back(0);
  // }

  // const int n = values.size();
  // const int n = pow(2, int(ceil(log2(L))));
  const int n = L;
  Complex* test = new Complex[n];

  // std::fill(test, test + n + 1, Complex(0, 0));

  for (int i = 0; t < tmax; t += T, i++) {
    // values.push_back({t, 0});
    // values.push_back({2 * sin(2*fmax*PI*t), 0});
    // test[i] = Complex(t, 0);
    test[i] = Complex(6 * sin(2*fmax*PI*t), 0);
  }
  // copy(values.begin(),values.end(), test);

	CArray data(test, n);

	// forward fft
	Fourier::fft(data);
  data = data[std::slice(1, L / 2 + 1, 1)];

	// std::cout << "fft" << std::endl;
  // x[std::slice(0, N/2, 2)]
  //   x[std::slice(1, N/2, 2)]

  std::cout << std::fixed << std::setprecision(3);

  std::vector<double> frequencies(L/2);
  std::vector<double> amplitude(L/2);
  for (int i = 0; i < L / 2 + 1; ++i) {
    frequencies[i] = samplingFreq*i/L;
    amplitude[i] = 2 * abs(data[i]) / L;

    // delete when testing is done
    double f = samplingFreq*i/L;
    std::cout << "f = " << f << "hz; fft(f) = " << 2 * abs(data[i]) / L << std::endl; 
  }

  // Fourier::ifft(data);
  // for (Complex piece : data) {
  //   std::cout << abs(piece) << std::endl; 
  // }

  matplot::plot(frequencies, amplitude, "k");

  matplot::show();

  return 0;
}
