#include <iostream>
#include "Server.hpp"

int main(int argc, char const *argv[])
{
  std::string filePath = "../../src/requirement.txt";
  std::string logFile = "../../src/logfile.txt";
  Server Boss(filePath, logFile);
  Boss.GetRequirement();
  Boss.SortRequirement();
  Boss.AssignTask();
  Boss.WriteReport(); // once the tasks are finished
  Boss.ReadReport(); // once the WriteReport is done
  Boss.~Server();
  return 0;
}
