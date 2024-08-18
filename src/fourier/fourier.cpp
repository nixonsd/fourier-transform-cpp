#include "fourier.h"

void Fourier::applyHannWindow(std::vector<double>& x) {
    int N = x.size();
    for (int i = 0; i < N; i++) {
        // Apply Hann window function to each element
        double multiplier = 0.5 * (1 - cos(2 * PI * i / (N - 1)));
        x[i] *= multiplier;
    }
}

void Fourier::performFFT(CArray& x) {
    int N = x.size();
    if (N <= 1) return; // Base case: if the array contains only one element, do nothing

    // Divide the array into even and odd parts
    CArray even = x[std::slice(0, N / 2, 2)];
    CArray odd = x[std::slice(1, N / 2, 2)];

    // Recursively perform FFT on both halves
    performFFT(even);
    performFFT(odd);

    // Combine the results of the even and odd parts
    for (size_t k = 0; k < N / 2; ++k) {
        // Calculate the complex exponential factor
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;          // First half of the output
        x[k + N / 2] = even[k] - t;  // Second half of the output
    }
}

CArray Fourier::computeFFT(std::vector<double> x, bool offsetRemoval, bool applyWindow) {
    size_t N = x.size();

    // Optionally remove the DC offset (mean of the signal)
    if (offsetRemoval) {
        double avg = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
        std::transform(x.begin(), x.end(), x.begin(), [avg](double sample) {
            return sample - avg;
        });
    }

    // Optionally apply the Hann window function
    if (applyWindow) {
        applyHannWindow(x);
    }

    // Ensure the input length is a power of 2 by padding with zeros if necessary
    if ((N & (N - 1)) != 0) {
        N = static_cast<size_t>(pow(2, ceil(log2(N))));
        x.resize(N, 0);
    }

    // Transform the input vector to a complex vector before converting to CArray
    std::vector<Complex> complexInput(N);
    std::transform(x.begin(), x.end(), complexInput.begin(), [](double realValue) {
        return Complex(realValue, 0.0); // Convert real number to complex with zero imaginary part
    });

    // Convert the complex vector to a CArray for FFT processing
    CArray data(complexInput.data(), N);

    // Perform the FFT on the complex array
    performFFT(data);

    return data; // Return the transformed data
}

// Inverse Fast Fourier Transform (Not Implemented)
void Fourier::computeInverseFFT(CArray& x) {
    // Take the complex conjugate of the input array
    x = x.apply(std::conj);

    // Perform the FFT on the conjugated array
    performFFT(x);

    // Take the complex conjugate again to restore original values
    x = x.apply(std::conj);

    // Scale the output by the size of the array
    x /= x.size();
}
