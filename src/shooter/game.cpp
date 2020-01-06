#include "game.h"

#include <SFML/Window/Event.hpp>

#include "menu/main.h"
#include "menu/splash_screen.h"

namespace Shooter {

namespace {
constexpr int SCREEN_WIDTH = 512;
constexpr int SCREEN_HEIGHT = 650;

constexpr int DEFAULT_BITS_PER_PIXEL = 32;

const sf::Color CLEAR_COLOR = sf::Color(0, 0, 0);
}  // namespace

Game::Game() : m_state{State::Uninitialized} {}

void Game::start() {
  if (m_state != State::Uninitialized) {
    return;
  }

  m_mainWindow.create(
      sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, DEFAULT_BITS_PER_PIXEL),
      "The Shooter");

  m_state = State::ShowingSplash;

  try {
    while (m_state != State::Exiting) {
      playLoop();
    }
  } catch (std::exception) {
  }

  m_mainWindow.close();
}

void Game::playLoop() {
  switch (m_state) {
    case State::ShowingMenu:
      showMenu();
      break;
    case State::ShowingSplash:
      showSplashScreen();
      break;
  }
}

void Game::showSplashScreen() {
  Menu::SplashScreen splashScreen;
  m_mainWindow.draw(splashScreen);
  m_mainWindow.display();

  sf::Event event;
  while (true) {
    while (m_mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::EventType::KeyPressed ||
          event.type == sf::Event::EventType::MouseButtonPressed ||
          event.type == sf::Event::EventType::Closed) {
        m_state = State::ShowingMenu;
        return;
      }
    }
  }
}

void Game::showMenu() {
  Menu::Main mainMenu;
  m_mainWindow.draw(mainMenu);
  m_mainWindow.display();

  sf::Event menuEvent;
  while (true) {
    while (m_mainWindow.pollEvent(menuEvent)) {
      if (menuEvent.type == sf::Event::KeyPressed) {
        if (menuEvent.key.code == sf::Keyboard::Return) {
          m_state = State::ShowingSplash;
          return;
        }
      }

      if (menuEvent.type == sf::Event::Closed) {
        m_state = State::Exiting;
        return;
      }
    }
  }
}

}  // namespace Shooter
