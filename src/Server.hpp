/**
 * @file Server.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "SafeQueue.h"
#include <thread>
#include "Handler.hpp"


#define MAX_HANDLERS 10

class Server
{
private:
  std::string             mRequirementPath;
  std::string             mLogFile;
  std::vector<HandlerPtr> mListHandlers;
  SafeQueue<uint64_t>     mListTasks;
  uint8_t                 mNumberOfHandlers;
  uint8_t                 mMaxHandlers;
  std::mutex              mMutex;

public:
  Server ();
  Server (std::string &rFilePath, std::string &rLogFile);
  ~Server();

  void UpdateRequirementPath         (std::string &rFilePath);
  void GetRequirement                ();
  void SortRequirement               ();
  void AssignTask                    ();
  void DecreaseNumberOfActiveHandlers();
  void WriteReport                   ();
  void ReadReport                    ();
};