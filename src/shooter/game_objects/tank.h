#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "game_objects/object.h"

namespace Shooter::GameObjects {

class Tank : public Object {
 public:
  ~Tank() override = default;

  // Object
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Object::Type getType() const override;
};

}  // namespace Shooter::GameObjects
