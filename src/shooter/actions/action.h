#pragma once

#include "actions/action_data.h"

namespace Shooter::Actions {

struct Action {
  enum class Type
  {
    SHOOT = 0,
    MOVE,
    TURN
  };
  using SenderId = std::uint16_t;

  Type type;
  SenderId senderId;
  ActionData data;
};

}  // namespace Shooter::Actions
