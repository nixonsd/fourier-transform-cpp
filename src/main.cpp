#include <iostream>
#include <vector>
#include <filesystem>
#include <cmath>

#include "fourier.h"

#include <matplot/matplot.h>

void smoothSpectrum(CArray& spectrum, int windowSize) {
    CArray smoothedSpectrum(spectrum.size());
    int halfWindow = windowSize / 2;
    
    for (size_t i = 0; i < spectrum.size(); ++i) {
        Complex sum = 0.0;
        int count = 0;
        
        for (int j = -halfWindow; j <= halfWindow; ++j) {
            int index = i + j;
            if (index >= 0 && index < spectrum.size()) {
                sum += spectrum[index];
                count++;
            }
        }
        
        smoothedSpectrum[i] = sum / static_cast<double>(count);
    }
    
    spectrum = smoothedSpectrum;
}

int main() {
    std::filesystem::path path = "Sample_Signal.txt";
    
    // input values P
    std::vector<double> values;
    double samplingFrequency = 40000; // Hz

    std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    std::cout << "Absolute path for " << path << " is " << std::filesystem::absolute(path) << std::endl;
    std::fstream myfile(std::filesystem::absolute(path), std::ios_base::in);

    double a;
    while (myfile >> a) { values.push_back(a); }

    const int L = values.size();
    if (!L) {
        throw new std::length_error("Invalid input size");
    }
    
        // forward fft
        CArray result = Fourier::computeFFT(values, true, false);
    CArray resultWindowed = Fourier::computeFFT(values, true, true);
    // smoothSpectrum(resultWindowed, 5);
    
    const int N = result.size();
    std::vector<double> frequencies(N / 2);
    std::vector<double> amplitude(N / 2);
    for (int i = 0; i < N / 2; ++i) {
        double frequency = samplingFrequency * i / N;
        frequencies[i] = frequency;
        amplitude[i] = 2 * abs(result[i]) / N;
    }

    // Hann Window calculation from complex numbers
    std::vector<double> hannAmplitude(N / 2);
    for (int i = 0; i < N / 2; ++i) {
        hannAmplitude[i] = 2 * abs(resultWindowed[i]) / (N - 1);
    }

    // Set boundaries
    const int lowerBoundary = 0 * N / samplingFrequency;
    const int upperBoundary = 400 * N / samplingFrequency;
    
    // Draw spectre
    matplot::hold(matplot::on);
    matplot::plot(std::vector<double>(frequencies.begin() + lowerBoundary, frequencies.begin() + upperBoundary), std::vector<double>(amplitude.begin() + lowerBoundary, amplitude.begin() + upperBoundary), "r");
    matplot::plot(std::vector<double>(frequencies.begin() + lowerBoundary, frequencies.begin() + upperBoundary), std::vector<double>(hannAmplitude.begin() + lowerBoundary, hannAmplitude.begin() + upperBoundary), "b");
    
    matplot::show();

    return 0;
}
