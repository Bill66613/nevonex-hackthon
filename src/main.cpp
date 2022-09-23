#include <iostream>
#include "Server.hpp"

int main(int argc, char const *argv[])
{
  std::string filePath = "/home/nog6hc/workspace/repos/temp/nevonex-hackthon/src/requirement.txt";
  std::string logFile = "/home/nog6hc/workspace/repos/temp/nevonex-hackthon/src/logfile.txt";
  Server Boss(filePath, logFile);
  Boss.GetRequirement();
  Boss.SortRequirement();
  Boss.AssignTask();
  // Boss.WriteReport(); // once the tasks are finished
  // Boss.ReadReport(); // once the WriteReport is done
  return 0;
}
