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
  uint16_t            mWorkLog;
  uint16_t            mTotalWork;
  SafeQueue<uint8_t> mTaskQueue;
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
  uint16_t        GetWorkLog  () { return mWorkLog; };
  uint16_t        GetTotalWork() { return mTotalWork; };
  void            LogWork     (uint8_t workLog);
};

typedef std::shared_ptr<Handler> HandlerPtr;
