#include "menu/main.h"

namespace Shooter::Menu {

Main::Main() {
  m_texture = std::make_unique<sf::Texture>();
  if (!m_texture->loadFromFile("resources/images/main_menu.png")) {
    throw std::exception("Unable to load main menu texture.");
  }

  m_sprite = std::make_unique<sf::Sprite>(*m_texture);

  Item playButton;
  playButton.rect = sf::Rect<int>(183, 243, 131, 56);
  playButton.action = Action::Play;
  m_menuItems.push_back(playButton);

  Item exitButton;
  exitButton.rect = sf::Rect<int>(189, 331, 109, 57);
  exitButton.action = Action::Exit;
  m_menuItems.push_back(exitButton);
}

Main::~Main() = default;

const std::list<Item>& Main::getItems() const { return m_menuItems; }

void Main::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*m_sprite, states);
}

}  // namespace Shooter::Menu
