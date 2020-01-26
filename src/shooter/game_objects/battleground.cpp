#include "game_objects/battleground.h"

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
                        sf::RenderStates states) const {}

void BattleGround::registerObject(GameObjects::Object::UPtr object) {
  auto id = INDEXER.getVacantId();
  object->setId(id);
  m_gameObjects.insert({id, std::move(object)});
}

void BattleGround::unregisterObject(Object::Id id) {
  m_gameObjects.erase(id);
  INDEXER.freeId(id);
}

}  // namespace Shooter::GameObjects
