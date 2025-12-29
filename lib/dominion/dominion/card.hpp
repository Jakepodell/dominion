#pragma once

#include "typeplay/print.hpp"
#include <string>
#include <type_traits>
#include <vector>

using typeplay::print;

namespace dominion {

enum class CardType { Action, Treasure, Victory };

struct Card {
  virtual ~Card() = default;
  virtual void play() const = 0;
  virtual std::vector<CardType> types() const = 0;
  virtual std::string const getName() const = 0;
  std::string const getShortName() const {
    auto abbrev = getName().substr(0, 2);
    std::transform(abbrev.begin(), abbrev.end(), abbrev.begin(), ::toupper);
    return abbrev;
  }

  // log the card name that's being played and then call the derived class
  // implementaitno
};

// ------------ BASE CARD TYPES ------------

struct PureAction : Card {
  std::vector<CardType> types() const final { return {CardType::Action}; }
};

struct PureTreasure : Card {
  std::vector<CardType> types() const final { return {CardType::Treasure}; }
  virtual const int moneyValue() const = 0;
};

struct PureVictory : Card {
  std::vector<CardType> types() const final { return {CardType::Victory}; }
  virtual const int victoryValue() const = 0;
};

// ------------ CARDS ------------

// Treasures

struct Copper : PureTreasure {
  void play() const final { print("User has played the copper"); }
  const int moneyValue() const final { return 1; }
  std::string const getName() const final { return "Copper"; }
};

struct Silver : PureTreasure {
  void play() const final { print("User has played the silver"); }
  const int moneyValue() const final { return 2; }
  std::string const getName() const final { return "Silver"; }
};

struct Gold : PureTreasure {
  void play() const final { print("User has played the gold"); }
  const int moneyValue() const final { return 3; }
  std::string const getName() const final { return "Gold"; }
};

// Victory Cards

struct Estate : PureVictory {
  void play() const final { print("User has played the estate"); }
  const int victoryValue() const final { return 1; }
  std::string const getName() const final { return "Estate"; }
};

struct Duchy : PureVictory {
  void play() const final { print("User has played the duchy"); }
  const int victoryValue() const final { return 3; }
  std::string const getName() const final { return "Duchy"; }
};

struct Provence : PureVictory {
  void play() const final { print("User has played the provence"); }
  const int victoryValue() const final { return 6; }
  std::string const getName() const final { return "Provence"; }
};

// Action Cards

struct Village : Card {
  void play() const final { print("User has played the village"); }
  std::vector<CardType> types() const final { return {CardType::Action}; }
  std::string const getName() const final { return "Village"; }
};

template <typename T> struct is_card : std::false_type {};

template <> struct is_card<Card> : std::true_type {};
} // namespace dominion