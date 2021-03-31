#include "game_objects/tank.h"

namespace Shooter::GameObjects {

float canonLength{0};

Tank::Tank() {
  m_texture = std::make_unique<sf::Texture>();
  if (!m_texture->loadFromFile("resources/images/tank.png")) {
    throw std::exception("Unable to load a tank texture.");
  }
  m_towerTexture = std::make_unique<sf::Texture>();
  if (!m_towerTexture->loadFromFile("resources/images/tower.png")) {
    throw std::exception("Unable to load a tank's tower texture.");
  }
  m_texture->setSmooth(true);
  m_towerTexture->setSmooth(true);

  m_sprite = std::make_unique<sf::Sprite>(*m_texture);
  const auto bounds = m_sprite->getLocalBounds();
  m_sprite->setOrigin(bounds.width / 2.f, bounds.height / 2.f);

  m_towerSprite = std::make_unique<sf::Sprite>(*m_towerTexture);
  const auto towerBounds = m_towerSprite->getLocalBounds();
  m_towerSprite->setOrigin(towerBounds.width / 2, towerBounds.height - 9);
  canonLength = towerBounds.height - 9;
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*m_sprite, states);
  target.draw(*m_towerSprite, states);
}

sf::Vector2f Tank::getSize() const {
  const auto bounds = m_sprite->getLocalBounds();
  return {bounds.width, bounds.height};
}

void Tank::setPosition(const sf::Vector2f& position) {
  m_sprite->setPosition(position);
  m_towerSprite->setPosition(position);
}

void Tank::setAngle(float angle) { m_sprite->setRotation(angle); }

void Tank::setTowerAngle(float angle) { m_towerSprite->setRotation(angle); }

float Tank::getCanonLength() const { return canonLength; }

}  // namespace Shooter::GameObjects
