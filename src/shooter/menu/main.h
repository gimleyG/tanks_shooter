#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <list>
#include <memory>

namespace sf {

class Sprite;
class Texture;

}  // namespace sf

namespace Shooter::Menu {

enum class MenuResult { Nothing = 0, Exit, Play };

class Main final : public sf::Drawable {
 public:
  struct MenuItem {
    sf::Rect<int> rect;
    MenuResult action;
  };

 public:
  Main();
  ~Main() override;

  // Drawable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  std::list<MenuItem> m_menuItems;
  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;
};

}  // namespace Shooter::Menu
