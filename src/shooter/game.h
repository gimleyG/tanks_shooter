#pragma once

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
  ~Game();

  void start();

 private:
  class Implementation;
  std::unique_ptr<Implementation> m_impl;
};

}  // namespace Shooter
