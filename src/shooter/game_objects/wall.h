#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "game_objects/object.h"

namespace Shooter::GameObjects {

class Wall : public Object {
 public:
  Wall(const sf::Vector2f& size, const sf::Vector2f& position);
  ~Wall() override = default;

  // Object
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Object::Type getType() const override;

 private:
  sf::RectangleShape m_shape;
};

}  // namespace Shooter::GameObjects
