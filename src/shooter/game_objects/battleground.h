#pragma once

#include "actions/registrator.h"
#include "game_map/map.h"
#include "game_objects/updatable.h"

namespace Shooter::GameObjects {

class BattleGround : public sf::Drawable, public Actions::Registrator {
 public:
  BattleGround(uint32_t width, uint32_t height);
  ~BattleGround() override;

  // Drawable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  // Actions::Registrator
 public:
  void registerAction(Actions::Action&&) override;

 public:
  void loadMap(const GameMap::Map& map);
  void registerGameObject(GameObjects::Updatable::UPtr object);
  void updateAll();

 private:
  void unregisterGameObject(Object::Id id);
  void performAction(Actions::Action&&);

 private:
  std::map<Object::Id, GameObjects::Object::UPtr> m_mapObjects;
  std::map<Object::Id, GameObjects::Updatable::UPtr> m_gameObjects;
  sf::Vector2u m_size;

  std::deque<Actions::Action> m_actions;

  mutable sf::Clock m_clock;
};

}  // namespace Shooter::GameObjects
