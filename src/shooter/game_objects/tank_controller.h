#pragma once

#include "game_objects/object.h"

namespace Shooter::GameObjects {

class Tank;

class TankController : public Object {
 public:
  explicit TankController(std::unique_ptr<Tank> tank);
  ~TankController() override;

  // Object
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Object::Type getType() const override;

 private:
  std::unique_ptr<Tank> m_controlledTank;
};

}  // namespace Shooter::GameObjects
