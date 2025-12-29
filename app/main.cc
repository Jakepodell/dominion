#include "dominion/card.hpp"
#include "dominion/player.hpp"
#include "typeplay/print.hpp"
#include <iostream>

using typeplay::print;

int main() {
  std::cout << std::boolalpha;

  // auto a = dominion::is_card<float>::value;
  // auto numvar = 3;
  // auto numvartype = decltype(numvar);
  std::unique_ptr<dominion::Card> myFirstCard =
      std::make_unique<dominion::Village>();
  myFirstCard->play();
  dominion::Player p1("Podr");
  p1.initDeck();
  p1.printSituation();
  p1.shuffleDeck();
  std::cout << p1.getName() << " shuffles their deck." << std::endl;
  p1.printSituation();
  std::cout << p1.getName() << " draws 5 cards." << std::endl;
  p1.draw(11);
  p1.printSituation();
  return 0;
}