#pragma once
#include <string>
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
  uint64_t            mWorkLog;
  uint64_t            mTotalWork;
  SafeQueue<uint64_t> mTaskQueue;
  handler_state_e     mState;

private:
  bool CheckAvailableTask();
  void SetState(handler_state_e newState);

public:
  Handler ()
  ~Handler()
  void        ExecuteTask();
  void        ReceiveTask();
  std::string GetName();
  uint64_t    GetWorkLog();
  uint64_t    GetTotalWork();
  handler_state_e GetState();

}; 