#pragma once

#include "menu/item.h"

namespace sf {

class Sprite;
class Texture;

}  // namespace sf

namespace Shooter::Menu {

class Main final : public sf::Drawable {
 public:
  Main();
  ~Main() override;

  const std::list<Item>& getItems() const;

  // Drawable
 public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  std::list<Item> m_menuItems;
  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;
};

}  // namespace Shooter::Menu
