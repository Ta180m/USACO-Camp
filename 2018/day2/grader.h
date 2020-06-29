#include <iostream>

/*
 * You need to implement the following functions:
 */

void add_friend(std::string cow1, std::string cow2, int timestamp);
bool check_friend(std::string cow1, std::string cow2, int timestamp);
int get_number_of_friends(std::string cow, int timestamp);

// Commands have the following format:
// A c1 c2 t
//  - Calls "add"friend" on cows "c1" and "c2" at timestamp t. You are
//    guaranteed that successive calls to A will have increasing values of t.
// C c1 c2 t
//  - Calls "check_friend" on cows "c1" and "c2" at timestamp t.
// N c t
//  - Calls "get_number_of_friends" on cow "c" at timestamp "t".

// You don't need to read or understand any of the code below,
// but it may be helpful.

int main() {
  int num_commands;
  std::cin >> num_commands;

  for (int i = 0; i < num_commands; ++i) {
    std::string command_type;
    std::cin >> command_type;

    if (command_type == "A") {
      std::string cow1, cow2;
      int timestamp;
      std::cin >> cow1 >> cow2 >> timestamp;

      add_friend(cow1, cow2, timestamp);
    } else if (command_type == "C") {
      std::string cow1, cow2;
      int timestamp;
      std::cin >> cow1 >> cow2 >> timestamp;

      std::string responses[] = {"FALSE", "TRUE"};
      std::cout << responses[check_friend(cow1, cow2, timestamp)] << std::endl;
    } else if (command_type == "N") {
      std::string cow;
      int timestamp;
      std::cin >> cow >> timestamp;

      std::cout << get_number_of_friends(cow, timestamp) << std::endl;
    } else {
      std::cout << "Invalid command type: " << command_type << std::endl;
      exit(1);
    }
  }
}
