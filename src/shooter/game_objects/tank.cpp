#include "game_objects/tank.h"

namespace Shooter::GameObjects {

Tank::Tank() : m_state{} {
  m_texture = std::make_unique<sf::Texture>();
  if (!m_texture->loadFromFile("resources/images/player_tank.png")) {
    throw std::exception("Unable to load main menu texture.");
  }

  m_sprite = std::make_unique<sf::Sprite>(*m_texture);
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*m_sprite, states);
}

const Tank::State& Tank::getState() const { return m_state; }

void Tank::setState(const State& newState) {
  m_state = newState;
  m_sprite->setPosition(m_state.position);
  m_sprite->setRotation(m_state.angle);
}

}  // namespace Shooter::GameObjects
