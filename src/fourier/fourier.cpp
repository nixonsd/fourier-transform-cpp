#include "fourier.h"

// Cooley–Tukey FFT (in-place)
void Fourier::fft(CArray& x)
{
	const size_t N = x.size();
	if (N <= 1) return;

	// divide (half a current array by 2)
	
	// std::slice(0, N/2, 2);
	

	CArray even = x[std::slice(0, N/2, 2)];
	CArray  odd = x[std::slice(1, N/2, 2)];
	
	// CArray even[N/2];
	// CArray odd[N/2];
	// for (int i = 0; i < N / 2; ++i) {
	// 	even[i] = x[i*2];
	// 	odd[i] = x[i*2+1];
	// }

	// conquer
	fft(even);
	fft(odd);

	// combine
	for (size_t k = 0; k < N/2; ++k)
	{
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k]; // magnitude = 1 theta=-2*PI*f
		// Complex t = exp(Complex(0, -2 * M_PI * k / N)) * odd[k];
		x[k    ] = even[k] + t;
		x[k+N/2] = even[k] - t;
	}
}

// inverse fft (in-place)
void Fourier::ifft(CArray& x)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	fft(x);

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= x.size();
}


// void interpolate(std::vector<Point> points, int step) {
//   return;
// }