#pragma once
#include "dominion/player.hpp"
#include <vector>

namespace dominion {

enum class TurnPhase { Action, Treasures, Buy, CleanUp };

class GameState {
public:
  static GameState createGame(std::vector<std::string> playerNames);
  explicit GameState(std::vector<Player> players);

  void startGame();

  Player &getCurrentPlayer() { return players_[currentPlayerIndex_]; }
  std::vector<Player> &getPlayers() { return players_; }
  TurnPhase getTurnPhase() const { return turnPhase_; }
  void setTurnPhase(TurnPhase phase) { turnPhase_ = phase; }
  void nextPlayer();

  void playCard(size_t handIndex);
  void playAllTreasures();

  void forEachPlayer(const std::function<void(Player &)> &func);

private:
  std::vector<Player> players_;
  size_t currentPlayerIndex_;
  TurnPhase turnPhase_;
  std::vector<std::unique_ptr<Card>> board_;
  std::vector<std::vector<std::unique_ptr<Card>>> supplyPiles_;
};

} // namespace dominion