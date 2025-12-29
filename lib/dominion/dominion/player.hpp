#pragma once

#include "card.hpp"
#include <algorithm>
#include <cctype> // for ::toupper
#include <deque>
#include <memory>
#include <random>
#include <string>

namespace dominion {
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
  }

  void printSituation() const {
    print("Player: ", name_);

    print("Deck [", deck_.size(), "]: ");
    for (const auto &card : deck_) {
      print("[", card->getShortName(), "] ");
    }

    print("Hand [", hand_.size(), "]: ");
    for (const auto &card : hand_) {
      print("[", card->getShortName(), "] ");
    }

    print("Discard pile [", discardPile_.size(), "]: ");
    for (const auto &card : discardPile_) {
      print("[", card->getShortName(), "] ");
    }
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

private:
  std::string name_;
  std::deque<std::unique_ptr<Card>> deck_;
  std::deque<std::unique_ptr<Card>> hand_;
  std::deque<std::unique_ptr<Card>> discardPile_;
};
} // namespace dominion