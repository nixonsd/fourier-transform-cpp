#include <iostream>
#include <vector>
#include <iomanip>
#include "fourier.h"

int main() {
  // input values P (timestamp, value of the measurment)
  std::vector<Complex> values;
  
  // sin(2*T*pi*t);
  double fmax = 4.0;
  double T = 1/(fmax);
  for (double t = 0; t < 10; t+=T) {
    values.push_back(t);
    values.push_back(sin(2*fmax*PI*t));
  }

  int n = values.size();

  Complex test[n];
  copy(values.begin(),values.end(), test);

	CArray data(test, n);
	// forward fft
	Fourier::fft(data);

	std::cout << "fft" << std::endl;
  // x[std::slice(0, N/2, 2)]
  //   x[std::slice(1, N/2, 2)]

  std::cout << std::fixed << std::setprecision(4);
  double t = 0;
	for (int i = 0; i < n; ++i, t+=T)
	{
		std::cout << data[i] << std::endl;
	}

  return 0;
}
