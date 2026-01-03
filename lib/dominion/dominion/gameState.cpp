#include "dominion/gameState.hpp"
#include "dominion/card.hpp"
#include "gameState.hpp"
#include <stdexcept>

namespace dominion {

GameState GameState::createGame(std::vector<std::string> playerNames) {
  std::vector<Player> players;
  players.reserve(playerNames.size());

  for (const auto &name : playerNames) {
    Player p(name);
    players.push_back(std::move(p));
  }

  return GameState(std::move(players));
}

GameState::GameState(std::vector<Player> players)
    : players_(std::move(players)), currentPlayerIndex_(0),
      turnPhase_(TurnPhase::Action) {
  if (players_.empty()) {
    throw std::runtime_error("Game requires at least one player");
  }
}

void GameState::nextPlayer() {
  currentPlayerIndex_ = (currentPlayerIndex_ + 1) % players_.size();
}

void GameState::forEachPlayer(const std::function<void(Player &)> &func) {
  for (auto &player : players_) {
    func(player);
  }
}

void GameState::startGame() {
  std::cout << "starting game" << std::endl;
  forEachPlayer([](Player &p) { p.printSituation(); });
  forEachPlayer([](Player &p) {
    p.initDeck();
    p.draw(5);
    p.printSituation();
  });
}

void GameState::playAllTreasures() {
  const Player &currentPlayer = getCurrentPlayer();
  int indexOffset = 0;
  while (currentPlayer.getHandSize() - indexOffset > 0) {
    std::cout << "index offset: " << indexOffset << std::endl;
    if (currentPlayer.getCardAt(indexOffset)->isType(CardType::Treasure)) {
      playCard(indexOffset);
    } else {
      indexOffset++;
    }
  }
}

void GameState::playCard(size_t handIndex) {
  std::cout << "Playing card at hand index: " << handIndex << std::endl;
  std::unique_ptr<Card> cardAtIndex =
      getCurrentPlayer().removeCardFromHand(handIndex);
  if (cardAtIndex == nullptr) {
    throw std::runtime_error("Invalid hand index");
  }
  auto effect = cardAtIndex->createEffect();
  effect->apply(*this);
  board_.push_back(std::move(cardAtIndex));
}

} // namespace dominion