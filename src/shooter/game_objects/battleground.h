#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include <map>

#include "game_objects/object.h"

namespace Shooter::GameObjects {

class BattleGround : public sf::Drawable {
 public:
  BattleGround(uint32_t width, uint32_t height);
  ~BattleGround() override;

  // Drawable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 public:
  void registerObject(GameObjects::Object::UPtr object);

 private:
  void unregisterObject(Object::Id id);

 private:
  std::map<Object::Id, GameObjects::Object::UPtr> m_gameObjects;
  sf::Vector2u m_size;

  mutable sf::Clock m_clock;
};

}  // namespace Shooter::GameObjects