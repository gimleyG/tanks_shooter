#pragma once

#include "game_objects/object.h"

namespace Shooter::GameObjects {

class Updatable : public Object {
 public:
  using UPtr = std::unique_ptr<Updatable>;

 public:
  ~Updatable() override = default;

  virtual void update(float elapsedTime) = 0;

  virtual void updatePosition(const sf::Vector2f &position) = 0;

  virtual void updateAngle(float angle) = 0;
};

}  // namespace Shooter::GameObjects
