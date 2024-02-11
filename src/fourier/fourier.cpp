#include "fourier.h"

void Fourier::_window(std::vector<double>& x) {
	int N = x.size();
	for (int i = 0; i < N; i++) {
		double multiplier = 0.5 * (1 - cos(2*PI*i/N));
		x[i] = multiplier * x[i];
	}
}

void Fourier::_fft(CArray& x) {
	int N = x.size();
	if (N <= 1) return;

	// divide (half a current array by 2)
	CArray even = x[std::slice(0, N/2, 2)];
	CArray  odd = x[std::slice(1, N/2, 2)];
	
	// conquer
	Fourier::_fft(even);
	Fourier::_fft(odd);

	// combine
	for (size_t k = 0; k < N/2; ++k)
	{
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
		x[k    ] = even[k] + t;
		x[k+N/2] = even[k] - t;
	}
}

std::valarray<Complex> Fourier::fft(std::vector<double> x, bool offsetRemoval, bool window)
{
	size_t N = x.size();

	// calculate average
	double avg = 0;
  for (int i = 0; i < N; i++) {
    avg += x[i];
  }
  avg /= N;

	// apply offset removal
  if (offsetRemoval) std::transform(x.begin(), x.end(), x.begin(), [=](double sample) { return sample - avg; });

	// Check if the array length is a power of 2
  for (;abs(log2(N) - int(log2(N))) > 1e-8; ++N) {
    x.push_back(0);
  }

	// Hann Window
	if (window) Fourier::_window(x);

	std::vector<Complex> _x(N);
	std::copy(x.begin(), x.end(), _x.begin());

	CArray data(&_x[0], N);

	// call Cooley-Tukey FFT function
	Fourier::_fft(data);

	return data;
}


// inverse fft (in-place) - is not implemented
void Fourier::ifft(CArray& x)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	Fourier::_fft(x);

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= x.size();
}
