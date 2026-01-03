#pragma once

#include "dominion/card.hpp"
#include "typeplay/print.hpp"
#include <algorithm>
#include <cctype> // for ::toupper
#include <deque>
#include <memory>
#include <random>
#include <string>

namespace dominion {
class GameState; // Forward declaration

class Player {

public:
  Player(const std::string &name) : name_(name) {}

  const std::string &getName() const { return name_; }

  void initDeck() {
    for (int i = 0; i < 7; i++) {
      deck_.push_back(std::make_unique<Copper>());
    }
    for (int i = 0; i < 3; i++) {
      deck_.push_back(std::make_unique<Estate>());
    }
    shuffleDeck();
  }

  void printSituation() const {
    typeplay::print("Player: ", name_);

    typeplay::print("Deck [", deck_.size(), "]: ");
    for (const auto &card : deck_) {
      typeplay::print("[", card->getShortName(), "] ");
    }

    typeplay::print("Hand [", hand_.size(), "]: ");
    for (const auto &card : hand_) {
      typeplay::print("[", card->getShortName(), "] ");
    }

    typeplay::print("Discard pile [", discardPile_.size(), "]: ");
    for (const auto &card : discardPile_) {
      typeplay::print("[", card->getShortName(), "] ");
    }

    typeplay::print("Money: ", money_);
  }

  void moveDiscardIntoDeck() { deck_ = std::move(discardPile_); }

  void shuffleDeck() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck_.begin(), deck_.end(), gen);
  }

  void draw(const int numCards) {
    int numDrawn = 0;
    while (numDrawn < numCards) {
      if (deck_.empty()) {
        if (discardPile_.empty()) {
          return;
        }
        deck_ = std::move(discardPile_);
      }
      if (!deck_.empty()) {
        hand_.push_back(std::move(deck_.front()));
        deck_.pop_front();
        numDrawn++;
      }
    }
    return;
  }

  void addMoney(int amount) { money_ += amount; }
  int money() const { return money_; }

  // Add these getter methods
  const std::deque<std::unique_ptr<Card>> &getHand() const { return hand_; }
  const Card *getCardAt(size_t index) const {
    return index < hand_.size() ? hand_[index].get() : nullptr;
  }

  // todo should make sure that the index is valid
  std::unique_ptr<Card> removeCardFromHand(size_t index) {
    auto card = std::move(hand_[index]);
    hand_.erase(hand_.begin() + index);
    return card;
  }

  size_t getHandSize() const { return hand_.size(); }

private:
  std::string name_;
  std::deque<std::unique_ptr<Card>> deck_;
  std::deque<std::unique_ptr<Card>> hand_;
  std::deque<std::unique_ptr<Card>> discardPile_;
  int money_ = 0;
};
} // namespace dominion