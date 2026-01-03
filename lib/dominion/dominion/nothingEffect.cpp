#include "dominion/gameEffect.hpp"
#include <iostream>

namespace dominion {

void NothingEffect::apply(GameState & /*state*/) const {
  std::cout << "NothingEffect applied." << std::endl;
}

} // namespace dominion