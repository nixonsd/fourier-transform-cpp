#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <cmath>
#include <span>

#include "fourier.h"

#include <matplot/matplot.h>

int main() {
  using namespace matplot;

  // input values P
  std::vector<Complex> values;
  double samplingFreq = 40000; // test sampling 1000
  
  // Test
  // sin(2*T*pi*t);
  // double fmax = 402.0;
  // double T = 1/samplingFreq;
  // double tmax = 1.5;
  // double L = samplingFreq * tmax;
  // double t = 0;

  std::filesystem::path path = "Sample_Signal.txt";
  std::cout << "Current path is " << std::filesystem::current_path() << '\n';
  std::cout << "Absolute path for " << path << " is " << std::filesystem::absolute(path) << '\n';
  std::fstream myfile(std::filesystem::absolute(path), std::ios_base::in);

  double a;
  while (myfile >> a)
  {
    values.push_back(a);
  }

  const int L = values.size();
  if (!L) {
    throw new std::length_error("Invalid input size");
  }

  std::vector<double> time(L);
  std::vector<double> func_value(L);

  // Test
  // const int n = L;
  // Complex* test = new Complex[n];
  // std::fill(test, test + n, Complex(0, 0));
  // for (int i = 0; t < tmax; t += T, i++) {
  //   double value = 6 * sin(2*fmax*PI*t);
  //   time[i] = t;
  //   func_value[i] = value;
  //   test[i] = Complex(value, 0);
  // }

	CArray data(&values[0], L);

	// forward fft
	Fourier::fft(data);

  std::vector<double> frequencies(L / 2);
  std::vector<double> amplitude(L / 2);
  for (int i = 0; i <= L / 2; ++i) {
    frequencies[i] = samplingFreq * i / L;
    amplitude[i] = 2 * abs(data[i]) / L;
  }
  
  // Draw initial points
  // matplot::subplot(2, 1, 0);
  // matplot::plot(std::vector<double>(time.begin(), time.begin() + L/2), std::vector<double>(func_value.begin(), func_value.begin() + L/2), "r");
  // matplot::subplot(2, 1, 1);

  // Draw spectre
  matplot::plot(std::vector<double>(frequencies.begin(), frequencies.begin() + 500), std::vector<double>(amplitude.begin(), amplitude.begin() + 500), "k");
  matplot::show();

  return 0;
}
