#include "game_objects/wall.h"

namespace Shooter::GameObjects {

Wall::Wall(sf::Vector2f& size, sf::Vector2f& position) : m_shape(size) {
  static auto color = sf::Color(250, 150, 0);

  m_shape.setPosition(position);
  m_shape.setFillColor(color);
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_shape, states);
}

Object::Type Wall::getType() const { return Object::Type::WALL; }

}  // namespace Shooter::GameObjects
