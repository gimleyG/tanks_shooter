#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <list>

namespace Shooter::Menu {

enum class Action { Nothing = 0, Exit, Play };

struct Item {
  sf::Rect<int> rect;
  Action action{Action::Nothing};
};

using ItemList = std::list<Item>;

}  // namespace Shooter::Menu
