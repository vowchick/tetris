#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_set>
#include "game.h"


void game_thread_func(Game *game) {
  game->run();
}

void printer_thread_func(Game *game) {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (game->finished()) {
      return;
    }
    game->print_board();
  }
}

int main () {
  const std::unordered_set<char> possible_chars = {'w', 'a', 's', 'd', 'q'};
  auto game = std::make_unique<Game>(10, 20);
  std::thread t(game_thread_func, game.get());
  std::thread p(printer_thread_func, game.get());
  
  char user_input;
  while (not game->finished()) {
    std::cin >> user_input;
    if (possible_chars.count(user_input) != 0) {
      game->register_user_input(user_input);
    }
  }

  t.join();
  p.join();

  return 0;
}