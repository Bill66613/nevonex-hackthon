#include <iostream>
#include "Server.hpp"

int main(int argc, char const *argv[])
{
  std::cout << "Hello World";
  Boss.GetRequirement();
  Boss.AssignTask();
  // Boss.WriteReport(); // once the tasks are finished
  // Boss.ReadReport(); // once the WriteReport is done
  return 0;
}
