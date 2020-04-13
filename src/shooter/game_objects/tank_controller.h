#pragma once

#include "actions/registrator.h"
#include "game_objects/updatable.h"

namespace Shooter {

namespace Actions {
class Registrator;
}  // namespace Actions

namespace GameObjects {

class Tank;

class TankController : public Updatable {
 public:
  explicit TankController(std::unique_ptr<Tank> tank,
                          Actions::Registrator& registrator);
  ~TankController() override;

  // Updatable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Object::Type getType() const override;

  void update(float elapsedTime) override;

 private:
  std::unique_ptr<Tank> m_controlledTank;
  Actions::Registrator& m_actionRegistrator;
};

}  // namespace GameObjects
}  // namespace Shooter
