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

class Handler
{
private:
  std::string         mName;
  uint64_t            mWorkLog;
  uint64_t            mTotalWork;
  SafeQueue<uint64_t> mTaskQueue;
  void * ServerNotifier;

public:
  Handler();
  Handler(void * serverNotifier);
  ~Handler();

private:
  bool CheckAvailableTask();

public:
  void            ReceiveTask (uint64_t task);
  void            ExecuteTask ();
  std::string     GetName     () { return mName; };
  uint64_t        GetWorkLog  () { return mWorkLog; };
  uint64_t        GetTotalWork() { return mTotalWork; };
  void            LogWork     (uint64_t workLog);

};

typedef std::shared_ptr<Handler> HandlerPtr;