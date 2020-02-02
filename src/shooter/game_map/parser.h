#pragma once

#include <filesystem>
#include <fstream>

#include "game_map/map.h"

namespace Shooter::GameMap {

class Parser final {
 public:
  explicit Parser(const std::filesystem::path& path);
  ~Parser();

  Parser(const Parser&) = delete;
  Parser(Parser&&) = delete;
  Parser& operator=(const Parser&) = delete;
  Parser& operator=(Parser&&) = delete;

  Parser& operator>>(Map& map);

 private:
  std::ifstream m_file;
};

}  // namespace Shooter::GameMap
