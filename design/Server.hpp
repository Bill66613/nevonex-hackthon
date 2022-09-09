#pragma once
#include "Handler.hpp"
#include "SafeQueue.h"
#include <fstream>
#include <iostream>

class Server
{
private:
  std::vector<Handler> mListHandlers;
  SafeQueue<uint64_t>  mListTasks;
  uint8_t              mNumberOfHandlers;

public:
  void GetRequirement (std::string &rFilePath);
  void SortRequirement();
  void AssignTask     ();
  void DecreaseNumberOfActiveHandlers();
  void WriteReport    ();
  void ReadReport     ();
};