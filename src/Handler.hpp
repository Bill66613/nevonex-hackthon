/**
 * @file Handler.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <string>
#include <memory>
#include "SafeQueue.h"

class Server;

class Handler
{
private:
  std::string         mName;
  int64_t             mWorkLogMs;
  uint16_t            mTotalWork;
  SafeQueue<uint8_t>  mTaskQueue;
  std::string         mLogFile;
  void                ExecuteTaskProc();
  Server &rServer;

public:
  Handler();
  Handler(std::string name, Server &rServer, std::string &logFile);
  ~Handler();

private:
  bool CheckAvailableTask();

public:
  void            ReceiveTask (uint8_t task);
  void            ExecuteTask ();
  std::string     GetName     () { return mName; };
  int64_t         GetWorkLog  () { return mWorkLogMs; };
  uint16_t        GetTotalWork() { return mTotalWork; };
  void            LogWork     (uint8_t task, int64_t actualTime);
};

typedef std::shared_ptr<Handler> HandlerPtr;
