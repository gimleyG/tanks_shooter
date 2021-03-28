#pragma once

#include "actions/action.h"

namespace Shooter::Actions {

class Registrator {
 public:
  virtual ~Registrator() = default;

  virtual void registerAction(Action&&) = 0;
};

}  // namespace Shooter::Actions
