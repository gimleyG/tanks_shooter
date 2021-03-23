#pragma once

#include "actions/registrator.h"
#include "game_objects/updatable.h"

namespace Shooter::GameObjects {

class Bullet final : public Updatable {
 public:
  struct State {
    sf::Vector2f position;
    float angle;
  };

 public:
  Bullet(const sf::Vector2f& position, float angle,
         Actions::Registrator& registrator);
  ~Bullet() override;

  // Updatable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  Object::Type getType() const override;

  void update(float elapsedTime) override;

  void updatePosition(const sf::Vector2f& position) override;

  void updateAngle(float angle) override;

 private:
  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;

  Actions::Registrator& m_actionRegistrator;
  State m_state;
};

}  // namespace Shooter::GameObjects
