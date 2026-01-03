#include "dominion/gameEffect.hpp"
#include "dominion/gameState.hpp"

namespace dominion {

GainMoneyEffect::GainMoneyEffect(int money) : money_(money) {}

void GainMoneyEffect::apply(GameState &state) const {
  state.getCurrentPlayer().addMoney(money_);
}

} // namespace dominion