#pragma once

#include "menu/item.h"

namespace Shooter::Menu {

using ItemListIter = ItemList::const_iterator;

class ItemPointer final : public sf::Drawable {
 public:
  ItemPointer();
  ~ItemPointer() override;

  const ItemListIter& getCurrent() const;

  // Drawable
 public:
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 public:
  void setUp(ItemListIter beg, ItemListIter end);

  void prev();
  void next();

 private:
  void updatePosition();

 private:
  ItemListIter m_begin;
  ItemListIter m_end;
  ItemListIter m_current;

  std::unique_ptr<sf::Texture> m_texture;
  std::unique_ptr<sf::Sprite> m_sprite;
};

}  // namespace Shooter::Menu
