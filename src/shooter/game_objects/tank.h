#pragma once

namespace Shooter::GameObjects {

class Tank final : public sf::Drawable {
 public:
  using UPtr = std::unique_ptr<Tank>;

 public:
  Tank();
  ~Tank() override = default;

  // sf::Drawable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  sf::Vector2f getSize() const;

  void setPosition(const sf::Vector2f& position);

  void setAngle(float angle);

  void setTowerAngle(float angle);

  float getCanonLength() const;

 private:
  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;

  std::unique_ptr<sf::Texture> m_towerTexture;
  std::unique_ptr<sf::Sprite> m_towerSprite;
};

}  // namespace Shooter::GameObjects
