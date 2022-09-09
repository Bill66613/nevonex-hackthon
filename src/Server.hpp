#pragma once
#include "Handler.hpp"
#include "SafeQueue.h"

#define MAX_HANDLERS 10

class Server
{
private:
  std::vector<Handler> mListHandlers;
  SafeQueue<uint64_t>  mListTasks;
  uint8_t              mNumberOfHandlers;
  uint8_t              mMaxHandlers;

public:
  Server ();
  ~Server();
  void GetRequirement (std::string &rFilePath);
  void SortRequirement();
  void AssignTask     ();
  void DecreaseNumberOfActiveHandlers();
  void WriteReport    ();
  void ReadReport     ();
};

extern Server Boss;