#include "game_map/parser.h"

namespace Shooter::GameMap {

Parser::Parser(const std::filesystem::path& path) {
  if (path.empty() || !path.has_filename()) {
    throw std::logic_error("Wrong filepath " + path.string());
  }

  m_file.open(path.string(), std::ios_base::in);
  if (!m_file.is_open()) {
    throw std::logic_error("Unable to open a file on path " + path.string());
  }
}

Parser::~Parser() {
  if (m_file.is_open()) {
    m_file.close();
  }
}

namespace {
constexpr auto SPACE_CHARS = " \n\r\t\v\f";

constexpr auto WALL_STR = "WALL";
constexpr auto WALL_STR_SIZE = 4;
constexpr auto MAX_SIZE_OF_WALL_DESCRIPTION = 5;

void normalize(std::string& str) {
  std::replace_if(
      str.begin(), str.end(), [](const char& ch) { return std::isspace(ch); },
      ' ');

  str.erase(std::unique(str.begin(), str.end(),
                        [](const char one, const char two) {
                          return one == ' ' && two == ' ';
                        }),
            str.end());
}

}  // namespace

Parser& Parser::operator>>(Map& map) {
  std::string line;
  while (std::getline(m_file, line, ';')) {
    std::string_view lineView = line;

    const auto start = lineView.find_first_not_of(SPACE_CHARS);
    if (start == std::string::npos) {
      continue;
    }
    lineView =
        lineView.substr(start, lineView.find_last_not_of(SPACE_CHARS) + 1);

    if (lineView.compare(0, WALL_STR_SIZE, WALL_STR) != 0) {
      continue;
    }

    line = lineView;
    normalize(line);

    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(), std::back_inserter(tokens));

    if (tokens.size() < MAX_SIZE_OF_WALL_DESCRIPTION) {
      continue;
    }

    Wall wall;
    wall.position = {std::stof(tokens[1]), std::stof(tokens[2])};
    wall.size = {std::stof(tokens[3]), std::stof(tokens[4])};

    map.walls.push_back(wall);
  }

  return *this;
}

}  // namespace Shooter::GameMap
