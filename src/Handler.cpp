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
#include <chrono>
#include <fstream>
#include <iostream>
#include "Handler.hpp"
#include "Server.hpp"

Handler::Handler(std::string name, Server &rServer, std::string &logFile)
: mName("Handler " + name)
, rServer(rServer)
, mLogFile(logFile)
, mTotalWork(0)
, mWorkLogMs(0)
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
  return (mTaskQueue.empty() && rServer.IsEmptyTask())? false : true;
}

/**
 * @brief
 *
 * @param task
 */
void Handler::ReceiveTask(uint8_t task)
{
  mTaskQueue.push(task);
  mTotalWork += task;
}

/**
 * @brief
 *
 */
void Handler::ExecuteTaskProc()
{
  while (CheckAvailableTask())
  {
    if(mTaskQueue.size() > 0){
        printf("Name: %s - Doing task: %u(s)\n", mName.c_str(), mTaskQueue.front());
        typedef std::chrono::high_resolution_clock Time;
        typedef std::chrono::milliseconds ms;
        typedef std::chrono::duration<float> fsec;
        auto t0 = Time::now();
        std::this_thread::sleep_for(std::chrono::seconds(mTaskQueue.front()));
        auto t1 = Time::now();
        fsec fs = t1 - t0;
        ms d = std::chrono::duration_cast<ms>(fs);
        LogWork(mTaskQueue.front(), d.count());
        mTaskQueue.pop();
    }
  }
  rServer.DecreaseNumberOfActiveHandlers();
  std::cout<<"Thread is dead: "<<this->mName<<std::endl;
}

/**
 * @brief
 *
 */
void Handler::ExecuteTask()
{
  std::thread ExecuteTaskThread(&Handler::ExecuteTaskProc, this);
  ExecuteTaskThread.detach();
}

/**
 * @brief
 *
 * @param task
 */
void Handler::LogWork(uint8_t task, int64_t actualTime)
{
  mWorkLogMs += actualTime;
  std::ofstream file(mLogFile, std::ios::app);
  if (file.is_open())
  {
    file << "Name: " << this->GetName()
         << " - Task: " << std::to_string(task)
         << "(s) - Actual finish time: " << std::to_string(actualTime) << "(ms)\n";
    file.close();
  }
  else
  {
    printf("[ERROR] Cannot open file\n");
  }
}
