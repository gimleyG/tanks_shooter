#pragma once

namespace Shooter::GameObjects {

class Object : public sf::Drawable {
 public:
  using UPtr = std::unique_ptr<Object>;
  using Id = uint16_t;

 public:
  enum class Type
  {
    TANK = 0,
    BULLET,
    WALL
  };

 public:
  ~Object() override = default;

  std::optional<Id> getId() const { return m_id; }
  void setId(Id id) { m_id = id; }

  virtual Type getType() const = 0;

 private:
  std::optional<Id> m_id;
};

}  // namespace Shooter::GameObjects
