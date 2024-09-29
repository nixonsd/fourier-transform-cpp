#include <iostream>
#include <vector>
#include <filesystem>
#include <cmath>
#include <fstream>
#include <stdexcept>

#include "matplotlibcpp.h"
#include "fourier.h"
#include "satellite_reader.h"

namespace plt = matplotlibcpp;

int main() {
    // Define the path to the satellite data file
    std::filesystem::path path = "./example/meas25.bin"; // Change to your binary file
    double samplingFrequency = 40000; // Hz (Adjust as needed)

    // Output current and absolute path
    std::cout << "Current path: " << std::filesystem::current_path() << '\n';
    std::cout << "Absolute path: " << std::filesystem::absolute(path) << std::endl;

    // Open the satellite data file
    std::ifstream file(std::filesystem::absolute(path), std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << path << std::endl;
        return 1;
    }

    // Read the header
    Header header = readHeader(file);
    std::cout << "Number of satellites: " << header.numSatellites << std::endl;
    std::cout << "Start time: " << header.startTime << ", End time: " << header.endTime << std::endl;
    std::cout << "Number of samples: " << header.numSamples << std::endl;

    // Prepare to store the frequencies and amplitudes for each satellite
    std::vector<double> frequencies;
    // std::vector<std::vector<double>> amplitudes;  // 2D vector to store amplitude for each satellite
    std::vector<std::vector<double>> hannAmplitudes;  // 2D vector to store windowed amplitude for each satellite

    const int lowerBoundary = 0;
    const int upperBoundary = 400; // Upper frequency boundary in Hz (adjust as needed)

    // Iterate over each satellite and process the data
    for (uint32_t sat = 0; sat < header.numSatellites; ++sat) {
        std::cout << "Processing satellite " << sat + 1 << std::endl;

        // Read data for the current satellite
        std::vector<Sample> satelliteSamples = readSatelliteData(file, header.numSamples);

        // Prepare the data for FFT (for example, from the first microphone)
        std::vector<double> values(satelliteSamples.size());
        for (size_t i = 0; i < satelliteSamples.size(); ++i) {
            values[i] = static_cast<double>(satelliteSamples[i].micValues[0]); // Using 1st microphone data
        }

        // Perform FFT on the satellite data
        CArray result = Fourier::computeFFT(values, true, false);
        CArray resultWindowed = Fourier::computeFFT(values, true, true);

        const int N = result.size();
        if (frequencies.empty()) {
            frequencies.resize(N / 2);
            for (int i = 0; i < N / 2; ++i) {
                frequencies[i] = samplingFrequency * i / N;
            }
        }

        // std::vector<double> amplitude(N / 2);
        std::vector<double> hannAmplitude(N / 2);

        for (int i = 0; i < N / 2; ++i) {
            // amplitude[i] = 2 * std::abs(result[i]) / N;
            hannAmplitude[i] = 2 * std::abs(resultWindowed[i]) / N;
        }

        // Store the amplitudes for plotting later
        // amplitudes.push_back(std::move(amplitude));
        hannAmplitudes.push_back(std::move(hannAmplitude));
    }

    // Plot all the satellites' spectra on one plot
    plt::figure_size(1200, 600);

    // Plot the FFT and Hann Windowed FFT for each satellite
    for (uint32_t sat = 0; sat < header.numSatellites; ++sat) {
        // plt::plot(
        //     std::vector<double>(frequencies.begin() + lowerBoundary, frequencies.end()),
        //     std::vector<double>(amplitudes[sat].begin() + lowerBoundary, amplitudes[sat].end()),
        //     {{"label", "Satellite " + std::to_string(sat + 1) + " FFT"}}
        // );
        plt::plot(
            std::vector<double>(frequencies.begin() + lowerBoundary, frequencies.end()),
            std::vector<double>(hannAmplitudes[sat].begin() + lowerBoundary, hannAmplitudes[sat].end()),
            {{"label", "Satellite " + std::to_string(sat + 1) + " Hann Windowed FFT"}}
        );
    }

    // Add labels and title
    plt::xlabel("Frequency (Hz)");
    plt::ylabel("Amplitude");
    plt::legend();
    plt::title("Frequency Spectrum for All Satellites");
    plt::show();

    file.close();
    return 0;
}
