#ifndef SATELLITE_READER_H
#define SATELLITE_READER_H

#include <vector>
#include <fstream>
#include <cstdint>

struct Header {
    uint32_t numSatellites;
    uint32_t startTime;
    uint32_t endTime;
    uint32_t numSamples;
};

struct Sample {
    std::vector<int16_t> micValues; // 8 values for each microphone
};

// Functions for reading the file
Header readHeader(std::ifstream &file);
std::vector<Sample> readSatelliteData(std::ifstream &file, uint32_t numSamples);

#endif // SATELLITE_READER_H
