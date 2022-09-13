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
#include "Handler.hpp"
#include "SafeQueue.h"

#define MAX_HANDLERS 10

class Server
{
private:
  std::string             mRequirementPath;
  std::vector<HandlerPtr> mListHandlers;
  SafeQueue<uint64_t>     mListTasks;
  uint8_t                 mNumberOfHandlers;
  uint8_t                 mMaxHandlers;

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