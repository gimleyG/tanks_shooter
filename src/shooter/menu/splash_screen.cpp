#include "menu/splash_screen.h"

namespace Shooter::Menu {

SplashScreen::SplashScreen() {
  m_texture = std::make_unique<sf::Texture>();

  if (!m_texture->loadFromFile("resources/images/splash_screen.png")) {
    throw std::exception("Unable to load splash screen texture.");
  }

  m_sprite = std::make_unique<sf::Sprite>(*m_texture);
}

SplashScreen::~SplashScreen() = default;

void SplashScreen::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  target.draw(*m_sprite, states);
}

}  // namespace Shooter::Menu
