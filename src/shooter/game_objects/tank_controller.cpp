#include "game_objects/tank_controller.h"

#include "actions/registrator.h"
#include "game_objects/tank.h"

namespace Shooter::GameObjects {

TankController::TankController(Tank::UPtr tank, Actions::Registrator& registrator)
    : m_controlledTank(std::move(tank)), m_actionRegistrator(registrator) {}

TankController::~TankController() = default;

void TankController::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  m_controlledTank->draw(target, states);
}

Object::Type TankController::getType() const { return Type::TANK; }

void TankController::update(float elapsedTime) {
  using Shooter::Actions::Action;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    Action action;
    auto state = m_controlledTank->getState();

    const auto moveAmount = 100.f * elapsedTime;
    const auto sin = std::sin(state.angle * DEG_TO_RAD_COEF);
    const auto cos = std::cos(state.angle * DEG_TO_RAD_COEF);
    state.position += {sin * moveAmount, -cos * moveAmount};

    action.type = Action::Type::MOVE;
    action.senderId = this->getId().value();
    action.data = {state.position, state.angle};
    m_actionRegistrator.registerAction(std::move(action));
    return;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    Action action;
    auto state = m_controlledTank->getState();

    const auto moveAmount = -100.f * elapsedTime;
    const auto sin = std::sin(state.angle * DEG_TO_RAD_COEF);
    const auto cos = std::cos(state.angle * DEG_TO_RAD_COEF);
    state.position += {sin * moveAmount, -cos * moveAmount};

    action.type = Action::Type::MOVE;
    action.senderId = this->getId().value();
    action.data = {state.position, state.angle};
    m_actionRegistrator.registerAction(std::move(action));
    return;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    Action action;
    auto state = m_controlledTank->getState();

    state.angle -= 40.f * elapsedTime;
    if (state.angle < -180) {
      state.angle += 360;
    }

    action.type = Action::Type::MOVE;
    action.senderId = this->getId().value();
    action.data = {state.position, state.angle};
    m_actionRegistrator.registerAction(std::move(action));
    return;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    Action action;
    auto state = m_controlledTank->getState();

    state.angle += 40.0f * elapsedTime;
    if (state.angle > 180) {
      state.angle -= 360;
    }

    action.type = Action::Type::MOVE;
    action.senderId = this->getId().value();
    action.data = {state.position, state.angle};
    m_actionRegistrator.registerAction(std::move(action));
    return;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    Action action;
    action.type = Action::Type::SHOOT;
    action.senderId = this->getId().value();

    const auto& state = m_controlledTank->getState();
    action.data = {state.position, state.angle};

    m_actionRegistrator.registerAction(std::move(action));
  }
}

void TankController::updatePosition(const sf::Vector2f& position) {
  m_controlledTank->setPosition(position);
}

void TankController::updateAngle(float angle) { m_controlledTank->setAngle(angle); }

}  // namespace Shooter::GameObjects
