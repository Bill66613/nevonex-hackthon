#include <iostream>
#include "Server.hpp"

int main(int argc, char const *argv[])
{
  std::string filePath = "/media/sf_VMFolder/Nevonex-Hackathon/src/requirement.txt";
  std::string logFile = "/media/sf_VMFolder/Nevonex-Hackathon/src/logfile.txt";
  Server Boss(filePath, logFile);
  Boss.GetRequirement();
  Boss.AssignTask();
  // Boss.WriteReport(); // once the tasks are finished
  // Boss.ReadReport(); // once the WriteReport is done
  return 0;
}
