/**
 * @file Handler.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <thread>
// #include <pthread.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include "Handler.hpp"
#include "Server.hpp"

Handler::Handler(std::string name, Server &rServer, std::string &logFile)
: mName("Handler " + name)
, rServer(rServer)
, mLogFile(logFile)
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
  return (mTaskQueue.empty() ? false : true);
}

/**
 * @brief
 *
 * @param task
 */
void Handler::ReceiveTask(uint8_t task)
{
  mTaskQueue.push(task);
}

/**
 * @brief
 *
 */
void Handler::ExecuteTaskProc()
{
  while (CheckAvailableTask())
  {
    printf("Name: %s - %lu\n", mName.c_str(), mTaskQueue.front());
    std::this_thread::sleep_for(std::chrono::seconds(mTaskQueue.front()));
    LogWork(mTaskQueue.front());
    mTaskQueue.pop();
  }
}

/**
 * @brief
 *
 */
void Handler::ExecuteTask()
{
  // std::thread ExecuteTaskThread(&Handler::ExecuteTaskProc, this);
  // ExecuteTaskThread.join();
  ExecuteTaskProc();
  // NotifyServer
  rServer.DecreaseNumberOfActiveHandlers();
}

/**
 * @brief
 *
 * @param workLog
 */
void Handler::LogWork(uint8_t workLog)
{
  std::ofstream file(mLogFile, std::ios::app);
  if (file.is_open())
  {
    file << "Name: " << this->GetName() << " - Log work: " << workLog << "\n";
    mWorkLog += workLog;
    file.close();
  }
  else
  {
    printf("[ERROR] Cannot open file\n");
  }
}
