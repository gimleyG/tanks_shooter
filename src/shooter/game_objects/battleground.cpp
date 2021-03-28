#include "game_objects/battleground.h"

#include "game_objects/bullet.h"
#include "game_objects/wall.h"

namespace Shooter::GameObjects {

namespace {

using Capacity = Object::Id;
const Capacity MAX_INDEXER_CAPACITY = 1024;

class Indexer final {
 public:
  Indexer(Capacity capacity) { reset(capacity); }

  void reset(Capacity capacity) {
    m_indexes.clear();
    for (auto i = 0; i < capacity; ++i) {
      m_indexes.insert({i, true});
    }
  }

  void freeId(Object::Id id) {
    if (id > m_indexes.size()) {
      return;
    }

    m_indexes[id] = true;
  }

  Object::Id getVacantId() {
    auto iter = std::find_if(m_indexes.begin(), m_indexes.end(),
                             [](const auto& elem) { return elem.second; });
    if (m_indexes.end() == iter) {
      throw std::exception("ObjectIndexer: No more vacant indexes!");
    }

    iter->second = false;
    return iter->first;
  }

 private:
  std::map<Object::Id, bool> m_indexes;
} INDEXER(MAX_INDEXER_CAPACITY);

}  // namespace

BattleGround::BattleGround(uint32_t width, uint32_t height) : m_size{width, height} {}

BattleGround::~BattleGround() = default;

void BattleGround::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (auto& [id, objectPtr] : m_mapObjects) {
    if (objectPtr->getType() != Object::Type::WALL) {
      continue;
    }
    target.draw(*objectPtr, states);
  }

  for (auto& [id, objectPtr] : m_gameObjects) {
    target.draw(*objectPtr, states);
  }
}

void BattleGround::loadMap(const GameMap::Map& map) {
  for (const auto& wall : map.walls) {
    auto mapObject = std::make_unique<Wall>(wall.size, wall.position);
    const auto id = INDEXER.getVacantId();
    mapObject->setId(id);

    m_mapObjects.insert({id, std::move(mapObject)});
  }
}

void BattleGround::registerGameObject(GameObjects::Updatable::UPtr object) {
  const auto id = INDEXER.getVacantId();
  object->setId(id);
  m_gameObjects.insert({id, std::move(object)});
}

void BattleGround::updateAll() {
  float timeDelta = m_clock.restart().asSeconds();

  for (auto& [id, objectPtr] : m_gameObjects) {
    objectPtr->update(timeDelta);
  }

  while (!m_actions.empty()) {
    performAction(std::move(m_actions.front()));
    m_actions.pop_front();
  }
}

void BattleGround::unregisterGameObject(Object::Id id) {
  m_gameObjects.erase(id);
  INDEXER.freeId(id);
}

void BattleGround::registerAction(Actions::Action&& action) {
  using ActionType = Actions::Action::Type;

  if (action.type != ActionType::MOVE && action.type != ActionType::SHOOT) {
    // TODO: Print warn message to log
    std::cout << "[Warn] Unexpected action type. The sender is " << action.senderId << "\n";
    return;
  }

  m_actions.push_back(std::move(action));
}

void BattleGround::performAction(Actions::Action&& action) {
  const auto objId = action.senderId;

  auto it = m_gameObjects.find(objId);
  if (it == m_gameObjects.end()) {
    // TODO: Print warn message to log
    std::cout << "[Warn] The object is unknown. Skip."
              << "\n";
    return;
  }

  switch (action.type) {
    case Actions::Action::Type::MOVE: {
      GameObjects::Updatable& object = *(it->second);
      if (GameObjects::Object::Type::BULLET == object.getType()) {
        // 1. If the bullet gets out of the screen - it is removed
        const auto newPosition = action.data.position;
        if ((newPosition.x <= 0) || (newPosition.x >= m_size.x) || (newPosition.y <= 0) ||
            (newPosition.y >= m_size.y)) {
          const auto id = object.getId().value();
          std::cout << "[Debug] Remove bullet with id " << id << " as it got out of bounds."
                    << std::endl;
          unregisterGameObject(id);
          break;
        }
        // 2. If the bullet hits a map object - it is removed
        // 3. If the bullet hits a player - it is removed, the player dies

        std::cout << "[Info] A bullet moves: "
                  << "id " << object.getId().value() << "; position " << action.data.position.x
                  << ":" << action.data.position.y << "; angle " << action.data.angle << std::endl;
        object.updatePosition(action.data.position);
        object.updateAngle(action.data.angle);
      } else {
        // 1. Check that the object remain inside the view
        // 2. Check that the object is not inside the map objects
        // 3. Doesn't intersect with other players

        std::cout << "[Info] An object moves: "
                  << "id " << object.getId().value() << "; position " << action.data.position.x
                  << ":" << action.data.position.y << "; angle " << action.data.angle << std::endl;
        object.updatePosition(action.data.position);
        object.updateAngle(action.data.angle);
      }
    } break;
    case Actions::Action::Type::SHOOT: {
      // Create a bullet
      std::cout << "[Info] A bullet created"
                << "position " << action.data.position.x << ":" << action.data.position.y
                << "; angle " << action.data.angle << "\n";

      registerGameObject(std::make_unique<Bullet>(action.data.position, action.data.angle, *this));
    } break;
  }
}

}  // namespace Shooter::GameObjects
