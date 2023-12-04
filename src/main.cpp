#include <iostream>
#include "fourier.h"

int main() {
  // input values P (timestamp, value of the measurment)
  std::vector<Point> P = {{1, 8}, {2, 4}, {3, 5}, {4, 9}};
  Fourier::fft(P);
  return 0;
}
