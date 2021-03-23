#include "game_objects/tank.h"

namespace Shooter::GameObjects {

Tank::Tank() : m_state{} {
  m_texture = std::make_unique<sf::Texture>();
  if (!m_texture->loadFromFile("resources/images/tank.png")) {
    throw std::exception("Unable to load a tank texture.");
  }
  m_texture->setSmooth(true);

  m_sprite = std::make_unique<sf::Sprite>(*m_texture);

  m_sprite->setOrigin(m_sprite->getLocalBounds().width / 2.f,
                      m_sprite->getLocalBounds().height / 2.f);
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*m_sprite, states);
}

const Tank::State& Tank::getState() const { return m_state; }

void Tank::setPosition(const sf::Vector2f& position) {
  m_state.position = position;
  m_sprite->setPosition(position);
}

void Tank::setAngle(float angle) {
  m_state.angle = angle;
  m_sprite->setRotation(angle);
}

}  // namespace Shooter::GameObjects
