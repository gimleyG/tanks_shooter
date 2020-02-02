#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Shooter::GameMap {

struct Wall {
  sf::Vector2f size;
  sf::Vector2f position;
};

struct Map {
  sf::Vector2f size;
  std::vector<Wall> walls;
};

}  // namespace Shooter::GameMap
