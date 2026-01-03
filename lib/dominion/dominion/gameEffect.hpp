#pragma once

namespace dominion {

class GameState;

struct GameEffect {
  virtual ~GameEffect() = default;
  // Effects operate on GameState, use state.getCurrentPlayer() for current
  // player
  virtual void apply(GameState &state) const = 0;
};

class GainMoneyEffect : public GameEffect {
public:
  explicit GainMoneyEffect(int money);
  void apply(GameState &state) const override;

private:
  int money_;
};

class NothingEffect : public GameEffect {
public:
  void apply(GameState &state) const override;
};

} // namespace dominion