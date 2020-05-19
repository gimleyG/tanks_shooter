#include "game_objects/wall.h"

namespace Shooter::GameObjects {

Wall::Wall(const sf::Vector2f& size, const sf::Vector2f& position) {
  m_texture = std::make_unique<sf::Texture>();
  if (!m_texture->loadFromFile("resources/images/wall.png")) {
    throw std::exception("Unable to load wall texture.");
  }
  m_texture->setSmooth(true);
  m_texture->setRepeated(true);

  m_sprite = std::make_unique<sf::Sprite>(
      *m_texture,
      sf::IntRect({0, 0}, {std::lround(size.x), std::lround(size.y)}));
  m_sprite->setPosition(position);
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*m_sprite, states);
}

Object::Type Wall::getType() const { return Object::Type::WALL; }

}  // namespace Shooter::GameObjects
