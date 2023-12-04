#pragma once

#include <vector>
#include <iterator>
#include <iostream>

struct Point {
  int timestamp;
  double value;
};

class Fourier {
  public:
  static void fft(std::vector<Point> P);
};