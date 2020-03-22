#pragma once

#include "game_objects/object.h"

namespace Shooter::GameObjects {

class Tank : public Object {
 public:
  using UPtr = std::unique_ptr<Tank>;

 public:
  ~Tank() override = default;

  // Object
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Object::Type getType() const override;
};

}  // namespace Shooter::GameObjects
