#include "satellite_reader.h"
#include <iostream>

// Function to read the file header
Header readHeader(std::ifstream &file) {
    Header header;
    file.read(reinterpret_cast<char*>(&header.numSatellites), sizeof(uint32_t));
    file.read(reinterpret_cast<char*>(&header.startTime), sizeof(uint32_t));
    file.read(reinterpret_cast<char*>(&header.endTime), sizeof(uint32_t));
    file.read(reinterpret_cast<char*>(&header.numSamples), sizeof(uint32_t));
    return header;
}

// Function to read the data for one satellite
std::vector<Sample> readSatelliteData(std::ifstream &file, uint32_t numSamples) {
    std::vector<Sample> samples(numSamples);

    for (uint32_t i = 0; i < numSamples; ++i) {
        Sample sample;
        sample.micValues.resize(8);

        // Read 8 microphone values for each sample
        for (int j = 0; j < 8; ++j) {
            int16_t micValue;
            file.read(reinterpret_cast<char*>(&micValue), sizeof(int16_t));
            sample.micValues[j] = micValue;
        }

        samples[i] = sample;
    }
    
    return samples;
}
