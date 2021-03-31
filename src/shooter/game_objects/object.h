#pragma once

namespace Shooter::GameObjects {

class Object : public sf::Drawable {
 public:
  using UPtr = std::unique_ptr<Object>;
  using Id = uint16_t;

 public:
  struct State {
    sf::Vector2f position;
    sf::Vector2f size;
    float angle;
  };

  enum class Type
  {
    TANK = 0,
    BULLET,
    WALL
  };

 public:
  Object() : m_state{}, m_id{} {}
  ~Object() override = default;

  std::optional<Id> getId() const { return m_id; }
  void setId(Id id) { m_id = id; }

  virtual Type getType() const = 0;

  const State& getState() const { return m_state; }

 protected:
  State m_state;

 private:
  std::optional<Id> m_id;
};

}  // namespace Shooter::GameObjects
