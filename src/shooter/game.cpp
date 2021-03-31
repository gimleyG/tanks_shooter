#include "prec.h"

#include "game.h"

#include "game_map/parser.h"
#include "game_objects/battleground.h"
#include "game_objects/object.h"
#include "game_objects/tank.h"
#include "game_objects/tank_controller.h"
#include "menu/item_pointer.h"
#include "menu/main.h"
#include "menu/splash_screen.h"

namespace Shooter {
namespace {
constexpr int SCREEN_WIDTH = 512;
constexpr int SCREEN_HEIGHT = 650;

constexpr int DEFAULT_BITS_PER_PIXEL = 32;
constexpr int FPS = 60;

const sf::Color CLEAR_COLOR = sf::Color(0, 0, 0);

#define BEGIN_EVENT_LOOP_SECTION(window, event) \
  while (true) {                                \
    while (window.pollEvent(event)) {
#define END_EVENT_LOOP_SECTION \
  }                            \
  }

}  // namespace

class Game::Implementation final {
 public:
  Implementation() : m_state{State::Uninitialized} {}
  ~Implementation() = default;

  Implementation(const Implementation&) = delete;
  Implementation(Implementation&&) = delete;
  Implementation& operator=(const Implementation&) = delete;
  Implementation& operator=(Implementation&&) = delete;

  void init() {
    m_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, DEFAULT_BITS_PER_PIXEL),
                        "The Shooter");
    m_mainWindow.setFramerateLimit(FPS);

    m_state = State::ShowingSplash;
  }

  void finilize() { m_mainWindow.close(); }

  void playLoop() {
    switch (m_state) {
      case State::Playing:
        renderGame();
        break;
      case State::ShowingMenu:
        showMenu();
        break;
      case State::ShowingSplash:
        showSplashScreen();
        break;
    }
  }

  void showSplashScreen() {
    Menu::SplashScreen splashScreen;
    m_mainWindow.draw(splashScreen);
    m_mainWindow.display();

    sf::Event event;
    BEGIN_EVENT_LOOP_SECTION(m_mainWindow, event)

    switch (event.type) {
      case sf::Event::EventType::KeyPressed:
      case sf::Event::EventType::MouseButtonPressed:
        m_state = State::ShowingMenu;
        return;
      case sf::Event::Closed:
        m_state = State::Exiting;
        return;
    }

    END_EVENT_LOOP_SECTION
  }

  void showMenu() {
    Menu::Main mainMenu;
    Menu::ItemPointer menuItemPointer;
    menuItemPointer.setUp(mainMenu.getItems().begin(), mainMenu.getItems().end());

    auto updateMenu = [this, &mainMenu, &menuItemPointer]() {
      m_mainWindow.draw(mainMenu);
      m_mainWindow.draw(menuItemPointer);
      m_mainWindow.display();
    };

    updateMenu();

    sf::Event event;
    BEGIN_EVENT_LOOP_SECTION(m_mainWindow, event)

    switch (event.type) {
      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Return:
            switch (menuItemPointer.getCurrent()->action) {
              case Menu::Action::Play:
                m_state = State::Playing;
                break;
              case Menu::Action::Exit:
                m_state = State::Exiting;
                break;
            }
            return;
          case sf::Keyboard::Up:
            menuItemPointer.prev();
            updateMenu();
            break;
          case sf::Keyboard::Down:
            menuItemPointer.next();
            updateMenu();
            break;
        }
        break;
      case sf::Event::Closed:
        m_state = State::Exiting;
        return;
    }

    END_EVENT_LOOP_SECTION
  }

  void renderGame() {
    GameMap::Map map;
    GameMap::Parser("map.mp") >> map;

    GameObjects::BattleGround battleGround(SCREEN_WIDTH, SCREEN_HEIGHT);
    battleGround.loadMap(map);
    {
      auto tank = std::make_unique<GameObjects::Tank>();
      auto tankController =
          std::make_unique<GameObjects::TankController>(std::move(tank), battleGround);
      tankController->updatePosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50});
      battleGround.registerGameObject(std::move(tankController));
    }

    auto updateGame = [this, &battleGround]() {
      m_mainWindow.clear(CLEAR_COLOR);
      battleGround.updateAll();
      m_mainWindow.draw(battleGround);
      m_mainWindow.display();
    };

    updateGame();

    sf::Event event;
    while (true) {
      m_mainWindow.pollEvent(event);

      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_state = State::ShowingMenu;
        showMenu();
        return;
      } else if (event.type == sf::Event::Closed) {
        m_state = State::Exiting;
        return;
      }

      updateGame();
    }
  }

 public:
  sf::RenderWindow m_mainWindow;
  State m_state;
};

Game::Game() : m_impl(std::make_unique<Game::Implementation>()) {}

Game::~Game() = default;

void Game::start() {
  if (m_impl->m_state != State::Uninitialized) {
    return;
  }

  m_impl->init();

  try {
    while (m_impl->m_state != State::Exiting) {
      m_impl->playLoop();
    }
  } catch (const std::exception& e) {
    std::cout << "[Err] " << e.what() << "\n";
  }

  m_impl->finilize();
}

}  // namespace Shooter
