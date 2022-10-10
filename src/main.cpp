#include <iostream>
#include "Server.hpp"
#define MAX_REQ 3

void MainActivity(std::string filePath, std::string &logFile){
  Server Boss(filePath, logFile);
  Boss.GetRequirement();
  Boss.SortRequirement();
  Boss.AssignTask();
  Boss.WriteReport(); // once the tasks are finished
  Boss.ReadReport(); // once the WriteReport is done
}


std::string getFilePath(std::string rFilePath, int index){
    rFilePath += std::to_string(index);
    rFilePath += ".txt";
    return rFilePath;
}

int main(int argc, char const *argv[])
{
  // std::string filePath = "../src/requirement/req";
  // std::string logPath = "../src/logfile/log";
  // for(int i = 1; i <= MAX_REQ ; ++i){
  //   std::string reqFile = getFilePath(filePath, i);
  //   std::string logFile = getFilePath(logPath, i);
  //   MainActivity(reqFile,logFile);
  // }
  std::string filePath = "../src/requirement/req3.txt";
  std::string logPath = "../src/logfile/log3.txt";
  MainActivity(filePath,logPath);
  return 0;
}
