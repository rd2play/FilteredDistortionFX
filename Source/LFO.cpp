#include "LFO.h"
#include <cmath>
#include <numbers>

namespace CF {
namespace {
const auto TWO_PI = 2 * std::numbers::pi_v<float>;
}

float LFO::getNextSample() {
  const auto returnedValue = std::sin(_phase);
  _phase += _phaseIncrement;
  _phase = std::fmod(_phase, TWO_PI);
  return returnedValue;
}
void LFO::setSampleRate(float sampleRate) {
  _sampleRate = sampleRate;
}

void LFO::setFrequency(float frequency) {
  const auto period = 1 / frequency;
  const auto periodInSamples = period * _sampleRate;
  _phaseIncrement = TWO_PI / periodInSamples;
}
}  // namespace CF
