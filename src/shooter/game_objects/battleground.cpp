#include "game_objects/battleground.h"

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

BattleGround::BattleGround(uint32_t width, uint32_t height)
    : m_size{width, height} {}

BattleGround::~BattleGround() = default;

void BattleGround::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
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
}

void BattleGround::unregisterGameObject(Object::Id id) {
  m_gameObjects.erase(id);
  INDEXER.freeId(id);
}

namespace {

using ActionHandlers = std::unordered_map<
    Actions::Action::Type,
    std::function<void(const GameObjects::Updatable& object,
                       const Actions::ActionData& actionData)>>;
const ActionHandlers HANDLERS = {
    {Actions::Action::Type::MOVE,
     [](const GameObjects::Updatable& object,
        const Actions::ActionData& actionData) {
       if (GameObjects::Object::Type::BULLET == object.getType()) {
         std::cout << "[Info] A bullet moves" << std::endl;
         // 1. If the bullet gets out of the screen - it removes
         // 2. If the bullet hits a map object - it removes
         // 3. If the bullet hits a player - it removes, the player dies
       } else {
         std::cout << "[Info] An object moves: "
                   << "id " << object.getId().value() << "; position "
                   << actionData.position.x << ":" << actionData.position.y
                   << "; angle " << actionData.angle << std::endl;
         // 1. Check that the object remain inside the view
         // 2. Check that the object is not inside the map objects
         // 3. Doesn't intersect with other players
       }
     }},
    {Actions::Action::Type::SHOOT, [](const GameObjects::Updatable& object,
                                      const Actions::ActionData& actionData) {
       // Create a bullet
       std::cout << "[Info] A bullet created"
                 << "position " << actionData.position.x << ":"
                 << actionData.position.y << "; angle " << actionData.angle
                 << "\n";
     }}};

}  // namespace

void BattleGround::registerAction(const Actions::Action& action) {
  using ActionType = Actions::Action::Type;

  if (action.type != ActionType::MOVE && action.type != ActionType::SHOOT) {
    // TODO: Print warn message to log
    std::cout << "[Warn] Unexpected action type. The sender is "
              << action.senderId << "\n";
    return;
  }

  const auto objId = action.senderId;

  auto it = m_gameObjects.find(objId);
  if (it == m_gameObjects.end()) {
    // TODO: Print warn message to log
    std::cout << "[Warn] The object is unknown. Skip."
              << "\n";
    return;
  }

  HANDLERS.at(action.type)(*(it->second), action.data);
}

}  // namespace Shooter::GameObjects
