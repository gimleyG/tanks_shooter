#include "game_objects/tank.h"

namespace Shooter::GameObjects {

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

Object::Type Tank::getType() const { return Type::TANK; }

}  // namespace Shooter::GameObjects
