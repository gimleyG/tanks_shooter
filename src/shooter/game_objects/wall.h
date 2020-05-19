#pragma once

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
  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;
};

}  // namespace Shooter::GameObjects
