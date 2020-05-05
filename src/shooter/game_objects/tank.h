#pragma once

namespace Shooter::GameObjects {

class Tank : public sf::Drawable {
 public:
  using UPtr = std::unique_ptr<Tank>;

  struct State {
    sf::Vector2f position;
    float angle;
  };

 public:
  Tank();
  ~Tank() override = default;

  // sf::Drawable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  const State& getState() const;

  void setPosition(const sf::Vector2f& position);

  void setAngle(float angle);

 private:
  State m_state;
  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;
};

}  // namespace Shooter::GameObjects
