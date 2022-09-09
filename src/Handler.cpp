#include <thread>
#include <chrono>
#include "Handler.hpp"
#include "Server.hpp"

Handler::Handler(void * serverNotifier)
: ServerNotifier(serverNotifier)
{
}

Handler::~Handler()
{
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Handler::CheckAvailableTask()
{
}

/**
 * @brief 
 * 
 * @param newState 
 */
void Handler::SetState(handler_state_e newState)
{
}

/**
 * @brief 
 * 
 * @param task 
 */
void Handler::ReceiveTask(uint64_t task)
{
  mTaskQueue.push(task);
}

/**
 * @brief 
 * 
 */
void Handler::ExecuteTask()
{
  SetState(handler_state_e::ACTIVE);
  while (!mTaskQueue.empty())
  {
    std::this_thread::sleep_for(std::chrono::seconds(mTaskQueue.front()));
    LogWork(mTaskQueue.front());
    mTaskQueue.pop();
  }
  SetState(handler_state_e::INACTIVE);
  // NotifyServer
  Boss.DecreaseNumberOfActiveHandlers();
}

/**
 * @brief 
 * 
 * @param workLog 
 */
void Handler::LogWork(uint64_t workLog)
{
}