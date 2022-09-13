#pragma once
#include "Handler.hpp"
#include "SafeQueue.h"

#define MAX_HANDLERS 10

class Server
{
private:
  std::string          mRequirementPath;
  std::vector<Handler> mListHandlers;
  SafeQueue<uint64_t>  mListTasks;
  uint8_t              mNumberOfHandlers;
  uint8_t              mMaxHandlers;

public:
  Server ();
  Server (std::string &rFilePath);
  ~Server();

  void UpdateRequirementPath         (std::string &rFilePath);
  void GetRequirement                ();
  void SortRequirement               ();
  void AssignTask                    ();
  void DecreaseNumberOfActiveHandlers();
  void WriteReport                   ();
  void ReadReport                    ();
};

extern Server Boss;