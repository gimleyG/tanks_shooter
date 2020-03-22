#include "game_objects/tank_controller.h"

#include "game_objects/tank.h"

namespace Shooter::GameObjects {

TankController::TankController(Tank::UPtr tank)
    : m_controlledTank(std::move(tank)) {}

TankController::~TankController() = default;

void TankController::draw(sf::RenderTarget& target,
                          sf::RenderStates states) const {
  m_controlledTank->draw(target, states);
}

Object::Type TankController::getType() const {
  return m_controlledTank->getType();
}

}  // namespace Shooter::GameObjects
