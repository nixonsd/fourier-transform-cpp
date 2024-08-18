#include <iostream>
#include <vector>
#include <filesystem>
#include <cmath>
#include <fstream>
#include <stdexcept>

#include "matplotlibcpp.h"
#include "fourier.h"

namespace plt = matplotlibcpp;

int main() {
    // Define the path to the sample signal file
    std::filesystem::path path = "./example/Sample_Signal.txt";
    
    // Container to store the input values
    std::vector<double> values;
    double samplingFrequency = 40000; // Hz

    // Output current and absolute path
    std::cout << "Current path: " << std::filesystem::current_path() << '\n';
    std::cout << "Absolute path: " << std::filesystem::absolute(path) << std::endl;

    // Open the sample signal file and read values
    std::ifstream myfile(std::filesystem::absolute(path));
    if (!myfile.is_open()) {
        std::cerr << "Error: Could not open the file " << path << std::endl;
        return 1;
    }

    double value;
    while (myfile >> value) {
        values.push_back(value);
    }

    if (values.empty()) {
        throw std::length_error("Invalid input size: No data read from file.");
    }

    // Perform FFT on the input values
    CArray result = Fourier::computeFFT(values, true, false);
    CArray resultWindowed = Fourier::computeFFT(values, true, true);

    const int N = result.size();
    std::vector<double> frequencies(N / 2);
    std::vector<double> amplitude(N / 2);
    std::vector<double> hannAmplitude(N / 2);

    for (int i = 0; i < N / 2; ++i) {
        frequencies[i] = samplingFrequency * i / N;
        amplitude[i] = 2 * std::abs(result[i]) / N;
        hannAmplitude[i] = 2 * std::abs(resultWindowed[i]) / N;
    }

    // Define the frequency boundaries for plotting
    const int lowerBoundary = 0;
    const int upperBoundary = 400 * N / samplingFrequency;

    // Plot the amplitude spectra
    plt::figure_size(1200, 600);
    plt::plot(
        std::vector<double>(frequencies.begin() + lowerBoundary, frequencies.begin() + upperBoundary),
        std::vector<double>(amplitude.begin() + lowerBoundary, amplitude.begin() + upperBoundary),
        "r-", {{"label", "FFT"}}
    );
    plt::plot(
        std::vector<double>(frequencies.begin() + lowerBoundary, frequencies.begin() + upperBoundary),
        std::vector<double>(hannAmplitude.begin() + lowerBoundary, hannAmplitude.begin() + upperBoundary),
        "b-", {{"label", "Hann Windowed FFT"}}
    );
    plt::xlabel("Frequency (Hz)");
    plt::ylabel("Amplitude");
    plt::legend();
    plt::title("Frequency Spectrum");
    plt::show();

    return 0;
}
