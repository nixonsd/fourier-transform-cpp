#include "fourier.h"

void Fourier::fft(std::vector<Point> points) {
  // ! write code here
  std::vector<Point>::iterator ptr;

  for (ptr = points.begin(); ptr != points.end(); ptr++) {
    std::cout << ptr->timestamp << " " << ptr->value << std::endl;
  }

  return;
}