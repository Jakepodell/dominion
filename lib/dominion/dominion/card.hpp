#pragma once

#include "dominion/gameEffect.hpp"
#include "typeplay/print.hpp"
#include <string>
#include <type_traits>
#include <vector>

namespace dominion {

enum class CardType { Action, Treasure, Victory };

class Card {
public:
  virtual ~Card() = default;
  virtual std::unique_ptr<GameEffect> createEffect() const = 0;
  virtual std::vector<CardType> types() const = 0;
  virtual std::string const getName() const = 0;
  virtual bool isType(CardType type) const {
    auto cardTypes = types();
    return std::find(cardTypes.begin(), cardTypes.end(), type) !=
           cardTypes.end();
  }
  std::string const getShortName() const {
    auto abbrev = getName().substr(0, 2);
    std::transform(abbrev.begin(), abbrev.end(), abbrev.begin(), ::toupper);
    return abbrev;
  }

  // log the card name that's being played and then call the derived class
  // implementaitno
};

// ------------ BASE CARD TYPES ------------

class PureActionCard : public Card {
public:
  std::unique_ptr<GameEffect> createEffect() const override {
    typeplay::print("Playing action card: ", getName());
    return std::make_unique<NothingEffect>();
  }
  std::vector<CardType> types() const override { return {CardType::Action}; }
};

class PureTreasureCard : public Card {
public:
  std::unique_ptr<GameEffect> createEffect() const override {
    return std::make_unique<GainMoneyEffect>(moneyValue());
  }
  std::vector<CardType> types() const override { return {CardType::Treasure}; }
  virtual const int moneyValue() const = 0;
};

class PureVictoryCard : public Card {
public:
  std::unique_ptr<GameEffect> createEffect() const override {
    return std::make_unique<NothingEffect>();
  }
  std::vector<CardType> types() const override { return {CardType::Victory}; }
  virtual const int victoryValue() const = 0;
};

// ------------ CARDS ------------

// Treasures

class Copper : public PureTreasureCard {
public:
  const int moneyValue() const final { return 1; }
  std::string const getName() const final { return "Copper"; }
};

class Silver : public PureTreasureCard {
public:
  const int moneyValue() const final { return 2; }
  std::string const getName() const final { return "Silver"; }
};

class Gold : public PureTreasureCard {
public:
  const int moneyValue() const final { return 3; }
  std::string const getName() const final { return "Gold"; }
};

// Victory Cards

class Estate : public PureVictoryCard {
public:
  const int victoryValue() const final { return 1; }
  std::string const getName() const final { return "Estate"; }
};

class Duchy : public PureVictoryCard {
public:
  const int victoryValue() const final { return 3; }
  std::string const getName() const final { return "Duchy"; }
};

class Provence : public PureVictoryCard {
public:
  const int victoryValue() const final { return 6; }
  std::string const getName() const final { return "Provence"; }
};

// Action Cards

class Village : public PureActionCard {
public:
  std::vector<CardType> types() const final { return {CardType::Action}; }
  std::string const getName() const final { return "Village"; }
};

class Smithy : public PureActionCard {
public:
  std::vector<CardType> types() const final { return {CardType::Action}; }
  std::string const getName() const final { return "Smithy"; }
};

template <typename T> struct is_card : std::false_type {};

template <> struct is_card<Card> : std::true_type {};
} // namespace dominion