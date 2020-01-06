#include "game.h"

#include <SFML/Window/Event.hpp>

#include "menu/item_pointer.h"
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
      switch (event.type) {
        case sf::Event::EventType::KeyPressed:
        case sf::Event::EventType::MouseButtonPressed:
          m_state = State::ShowingMenu;
          return;
        case sf::Event::Closed:
          m_state = State::Exiting;
          return;
      }
    }
  }
}

void Game::showMenu() {
  Menu::Main mainMenu;
  Menu::ItemPointer menuItemPointer;
  menuItemPointer.setUp(mainMenu.getItems().begin(), mainMenu.getItems().end());

  m_mainWindow.draw(mainMenu);
  m_mainWindow.draw(menuItemPointer);
  m_mainWindow.display();

  sf::Event menuEvent;
  while (true) {
    while (m_mainWindow.pollEvent(menuEvent)) {
      switch (menuEvent.type) {
        case sf::Event::KeyPressed:
          switch (menuEvent.key.code) {
            case sf::Keyboard::Return:
              switch (menuItemPointer.getCurrent()->action) {
                case Menu::Action::Play:
                case Menu::Action::Exit:
                  m_state = State::ShowingSplash;
              }
              return;
            case sf::Keyboard::Up:
              menuItemPointer.prev();
              m_mainWindow.draw(mainMenu);
              m_mainWindow.draw(menuItemPointer);
              m_mainWindow.display();
              break;
            case sf::Keyboard::Down:
              menuItemPointer.next();
              m_mainWindow.draw(mainMenu);
              m_mainWindow.draw(menuItemPointer);
              m_mainWindow.display();
              break;
          }
          break;
        case sf::Event::Closed:
          m_state = State::Exiting;
          return;
      }
    }
  }
}

}  // namespace Shooter
