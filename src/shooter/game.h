#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace Shooter {

class Game final {
 public:
  enum class State {
    Uninitialized = 0,
    ShowingSplash,
    ShowingMenu,
    Playing,
    Exiting
  };

 public:
  Game();

  void start();

 private:
  void playLoop();
  void showSplashScreen();
  void showMenu();
  void renderGame();

 private:
  sf::RenderWindow m_mainWindow;
  State m_state;
};

}  // namespace Shooter
