#pragma once
#include <mutex>
#include <memory>
#include <thread>
#include <iostream>

#include "utils.h"
#include "board.h"

class Game {
  public:

  Game(int n, int m) : m_board(std::make_unique<Board>(n, m)) {

  }

  void run() {
    m_start = std::chrono::high_resolution_clock::now();
    while (not m_finished) {
      std::unique_lock<std::mutex> lock(m);
      cv.wait_for(lock, std::chrono::seconds(1));
      if (m_finished) {
        break;
      }
      if (m_new_key_pressed) {
        m_new_key_pressed = false;
        auto seconds_passed = get_seconds_since_start();
        m_board->update(seconds_passed.count(), std::make_optional(m_key_pressed));
      }
      m_board->update(get_seconds_since_start().count(), std::nullopt);
    }
  };

  // candidate to be private
  std::chrono::seconds get_seconds_since_start() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_start);
  }

  bool finished() const {
    return m_finished;
  };

  void print_board() const {
    m_board->print();
  }

  void register_user_input(char key_pressed) {
    {
      std::lock_guard{m};
      m_key_pressed = key_pressed;
      m_new_key_pressed = true;
      if (m_key_pressed == 'q') {
        m_finished = true;
      }
    }
    cv.notify_one();
  }

private:
  mutable std::mutex m;
  std::condition_variable cv;
  char m_key_pressed;
  bool m_new_key_pressed = false;
  bool m_finished = false;

  std::unique_ptr<Board> m_board;

  std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};