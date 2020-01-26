#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <optional>

namespace Shooter::GameObjects {

class Object : public sf::Drawable {
 public:
  using UPtr = std::unique_ptr<Object>;

 public:
  enum class Type { TANK = 0, BULLET, WALL };

 public:
  ~Object() override = default;

  std::optional<uint16_t> getId() const { return m_id; }
  void setId(uint16_t id) { m_id = id; }

  virtual Type getType() const = 0;

 private:
  std::optional<uint16_t> m_id;
};

}  // namespace Shooter::GameObjects
