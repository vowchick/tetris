#pragma once

#include <algorithm>
#include <vector>
#include <chrono>
#include <memory>
#include "utils.h"

class BaseBlock
{
public:
  BaseBlock(utils::Coordinates center) : m_center(center),
                                                                        m_start_time(std::chrono::high_resolution_clock::now())
  {
  }

  virtual ~BaseBlock() {}

  virtual void rotate(utils::RotationKey key_pressed) = 0;

  void move(utils::MoveKey key_pressed)
  {
    using utils::MoveKey;
    switch (key_pressed)
    {
    case MoveKey::Left:
    {
      m_center.x--;
      break;
    }
    case MoveKey::Right: {
      m_center.x++;
      break;
    }
    }
  }
  
  virtual void reset(utils::Coordinates center)
  {
    m_center = center;
    m_start_time = std::chrono::high_resolution_clock::now();
  }

  virtual std::vector<utils::Coordinates> get_space_taken() const = 0;

private:
protected:
  utils::Coordinates m_center;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
};

class IBlock : public BaseBlock
{
public:
  enum class Rotation : bool
  {
    vertical = true,
    horizontal = false
  };

  void rotate(utils::RotationKey) override
  {
    m_rotation = static_cast<Rotation>(not utils::to_underlying<Rotation>(m_rotation));
  }

  std::vector<utils::Coordinates> get_space_taken() const
  {
  }

private:
  Rotation m_rotation;
};