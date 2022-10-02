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
#include <thread>

#include "SafeQueue.h"
#include "Handler.hpp"

#define MAX_HANDLERS 10

typedef std::chrono::steady_clock::time_point TimePoint;
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

class Server
{
private:
  std::string             mRequirementPath;
  std::string             mLogFile;
  std::vector<HandlerPtr> mListHandlers;
  std::vector<uint8_t>    mListTasks;
  uint8_t                 mNumberOfHandlers;
  uint8_t                 mMaxHandlers;
  uint16_t                mTotalWork;
  std::mutex              mMutex;
  TimePoint               mTimeStart;
  TimePoint               mTimeEnd;

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