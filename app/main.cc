#include "dominion/gameState.hpp"
#include "typeplay/print.hpp"
#include <iostream>

using typeplay::print;

int main() {
  // RAII: Game acquires all resources on construction
  auto gameState = dominion::GameState::createGame({"Shayna", "Jake"});

  // Resources are automatically managed
  gameState.startGame();
  std::cout << "playing all treasures for current player: "
            << gameState.getCurrentPlayer().getName() << std::endl;
  gameState.playAllTreasures();
  std::cout << "played all treasures" << std::endl;
  gameState.getCurrentPlayer().printSituation();

  // When game goes out of scope, all resources are cleaned up
  return 0;
}
// Game destructor called here - automatic cleanup!