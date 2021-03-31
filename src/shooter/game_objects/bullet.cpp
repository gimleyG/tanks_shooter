#include "game_objects/bullet.h"

namespace Shooter::GameObjects {

namespace {
const uint16_t VELOCITY = 400;
}

Bullet::Bullet(const sf::Vector2f &position, float angle, Actions::Registrator &registrator)
    : m_actionRegistrator(registrator) {
  m_texture = std::make_unique<sf::Texture>();
  if (!m_texture->loadFromFile("resources/images/bullet.png")) {
    throw std::exception("Unable to load a bullet texture.");
  }
  m_texture->setSmooth(true);
  m_sprite = std::make_unique<sf::Sprite>(*m_texture);
  m_sprite->setPosition(position);
  auto bounds = m_sprite->getLocalBounds();
  m_sprite->setOrigin(bounds.width / 2.f, bounds.height / 2.f);

  m_state = {position, {bounds.width, bounds.height}, angle};
}

Bullet::~Bullet() = default;

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(*m_sprite, states);
}

Object::Type Bullet::getType() const { return Object::Type::BULLET; }

void Bullet::update(float elapsedTime) {
  using Actions::Action;

  Action action;
  action.type = Action::Type::MOVE;
  action.senderId = this->getId().value();

  float moveAmount = VELOCITY * elapsedTime;
  const auto sin = std::sin(m_state.angle * DEG_TO_RAD_COEF);
  const auto cos = std::cos(m_state.angle * DEG_TO_RAD_COEF);
  action.data = {m_state.position + sf::Vector2f{sin * moveAmount, -cos * moveAmount},
                 m_state.angle};

  m_actionRegistrator.registerAction(std::move(action));
}

void Bullet::updatePosition(const sf::Vector2f &position) {
  m_state.position = position;
  m_sprite->setPosition(position);
}

void Bullet::updateAngle(float angle) {
  m_state.angle = angle;
  m_sprite->setRotation(angle);
}

}  // namespace Shooter::GameObjects
