#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace sf {

class Sprite;
class Texture;

}  // namespace sf

namespace Shooter::Menu {

class SplashScreen final : public sf::Drawable {
 public:
  SplashScreen();
  ~SplashScreen() override;

  // sf::Drawable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;
};

}  // namespace Shooter::Menu
