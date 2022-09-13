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

enum HANDLER_STATE_E
{
  INACTIVE,
  ACTIVE
};

typedef HANDLER_STATE_E handler_state_e;

class Handler
{
private:
  std::string         mName;
  handler_state_e     mState;
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
  void SetState(handler_state_e newState);

public:
  void            ReceiveTask (uint64_t task);
  void            ExecuteTask ();
  std::string     GetName     () { return mName; };
  handler_state_e GetState    () { return mState; };
  uint64_t        GetWorkLog  () { return mWorkLog; };
  uint64_t        GetTotalWork() { return mTotalWork; };
  void            LogWork     (uint64_t workLog);

};

typedef std::shared_ptr<Handler> HandlerPtr;