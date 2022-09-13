/**
 * @file Server.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Server.hpp"
#include <fstream>
#include <iostream>
#include <thread>

Server::Server()
: mMaxHandlers(MAX_HANDLERS)
{
}

Server::Server(std::string &rFilePath)
: mMaxHandlers(MAX_HANDLERS)
, mRequirementPath(rFilePath)
{
}

Server::~Server()
{
}

/**
 * @brief In order to update the path of requirement apart from contructor, use this function
 *
 * @param rFilePath
 */
void Server::UpdateRequirementPath(std::string &rFilePath)
{
  mRequirementPath = rFilePath;
}

/**
 * @brief Parse the requirement file from mRequirementPath, push data to mListTasks
 *
 * @param rFilePath
 */
void Server::GetRequirement()
{
  std::ifstream file(mRequirementPath);
  int number;
  if (file.is_open())
  {
    while (file >> number)
    {
      mListTasks.push(number);
    }
    file.close();
  }
  else
  {
    printf("[ERROR] Cannot open file");
  }
}

/**
 * @brief Sort the requirement
 *
 */
void Server::SortRequirement()
{
}

/**
 * @brief Create handler for each task: create thread / handler
 *  Maximum number of handlers = 10
 *  If reaches, assign tasks to existing handlers, with the lowest task weight
 *
 */
void Server::AssignTask()
{
  while (!mListTasks.empty())
  {
    if (mListHandlers.size() < 10)
    {
      // Create handler
      HandlerPtr new_handler = std::make_shared<Handler>();
      mListHandlers.push_back(new_handler);
      mListHandlers.back()->ReceiveTask(mListTasks.front());
      mListHandlers.back()->ExecuteTask();
      mListTasks.pop();
    }
    else
    {
      // Assign to an existing handler

      // Get the min total work of handlers
      uint64_t min_work = UINT64_MAX;
      HandlerPtr chosen_handler;
      for (auto &handler_itr : mListHandlers)
      {
        if (min_work > handler_itr->GetTotalWork())
        {
          min_work = handler_itr->GetTotalWork();
          chosen_handler = handler_itr;
        }
      }
      chosen_handler->ReceiveTask(mListTasks.front());
      mListTasks.pop();
    }
  }
}

/**
 * @brief
 *
 */
void Server::DecreaseNumberOfActiveHandlers()
{
  mNumberOfHandlers--;
}

/**
 * @brief
 *
 */
void Server::ReadReport()
{
  std::ifstream file(mRequirementPath);
  if (file.is_open())
  {
    std::string line;
    while(getline(file, line))
    {
      std::cout << line << std::endl;
    }
  }
  else
  {
    printf("Cannot open file");
  }
}

/**
 * @brief
 *
 */
void Server::WriteReport()
{
  std::ofstream file(mRequirementPath, std::ofstream::out);
  if (file.is_open())
  {
    int i = 0;
    while(!mListHandlers.empty())
    {
      file << "Name: " << mListHandlers[i]->GetName() << " - Worklog: " << mListHandlers[i]->GetWorkLog() << "\n";
    }
    file.close();
  }
  else
  {
    printf("Cannot open file");
  }
}

Server Boss;