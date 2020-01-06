#include "menu/item_pointer.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Shooter::Menu {

ItemPointer::ItemPointer() {
  m_texture = std::make_unique<sf::Texture>();
  if (!m_texture->loadFromFile("resources/images/pointer.png")) {
    throw std::exception("Unable to load main menu texture.");
  }

  m_sprite = std::make_unique<sf::Sprite>(*m_texture);
}

ItemPointer::~ItemPointer() = default;

const ItemListIter& ItemPointer::getCurrent() const { return m_current; }

void ItemPointer::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const {
  target.draw(*m_sprite, states);
}

void ItemPointer::next() {
  if (m_current == m_end) {
    m_current = m_begin;
  } else {
    m_current++;
  }

  updatePosition();
}

void ItemPointer::prev() {
  if (m_current == m_begin) {
    m_current = m_end;
  } else {
    m_current--;
  }

  updatePosition();
}

void ItemPointer::setUp(ItemListIter beg, ItemListIter end) {
  m_begin = beg;
  m_end = std::prev(end);
  m_current = beg;

  updatePosition();
}

void ItemPointer::updatePosition() {
  auto rect = m_current->rect;
  m_sprite->setPosition(rect.left - 30.f, rect.top + rect.height / 2.f - 10);
}

}  // namespace Shooter::Menu
