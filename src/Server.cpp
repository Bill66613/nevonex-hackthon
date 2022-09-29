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
#include "Handler.hpp"
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

Server::Server()
    : mMaxHandlers(MAX_HANDLERS)
    , mNumberOfHandlers(0)
{
}

Server::Server(std::string &rFilePath, std::string &rLogFile)
: mMaxHandlers(MAX_HANDLERS)
, mNumberOfHandlers(0)
, mRequirementPath(rFilePath)
, mLogFile(rLogFile)
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
  printf("[INFO] Getting requirements\n");
  std::ifstream file(mRequirementPath);
  int number;
  if (file.is_open())
  {
    while (file >> number)
    {
      mListTasks.push_back(number);
    }
    file.close();
  }
  else
  {
    printf("[ERROR] Cannot open file\n");
  }
  printf("[INFO] Finish getting requirements\n");
}

/**
 * @brief Helping function for sort requirement: Heapify
 *  The left and right child cannot exceed the root value
 *
 */
template <class T>
void heapify(std::vector<T> &arr, unsigned int N, unsigned int index)
{
  unsigned int largest = index;
  unsigned int lc = 2 * index + 1;
  unsigned int rc = 2 * index + 2;

  if (lc < N && arr[lc] > arr[largest]) largest = lc;
  if (rc < N && arr[rc] > arr[largest]) largest = rc;

  if (largest != index)
  {
    std::swap(arr[index], arr[largest]);
    heapify(arr, N, largest);
  }
}

/**
 * @brief Sort the requirement : Heap sort
 *
 */
void Server::SortRequirement()
{
  // Build max heap
  for (int i = mListTasks.size() / 2 - 1; i >= 0; i--)
  {
    heapify(mListTasks, mListTasks.size(), i);
  }

  for (int i = mListTasks.size() - 1; i > 0; i--)
  {
    std::swap(mListTasks[0], mListTasks[i]);
    heapify(mListTasks, i, 0);
  }
}

/**
 * @brief Create handler for each task: create thread / handler
 *  Maximum number of handlers = 10
 *  If reaches, assign tasks to existing handlers, with the lowest task weight
 *
 */
void Server::AssignTask()
{
  printf("[INFO] Assigning requirements\n");
  int i = 1;
  while (!mListTasks.empty())
  {
    // if (mListHandlers.size() < 10)
    if (mNumberOfHandlers < 10)
    {
      // Create handler
      mNumberOfHandlers++;
      HandlerPtr new_handler = std::make_shared<Handler>(std::to_string(i), *this, mLogFile);
      mListHandlers.push_back(new_handler);
      auto task = mListTasks.begin();
      new_handler->ReceiveTask(*task);
      new_handler->ExecuteTask();
      mListTasks.erase(task);
      i++;
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
      auto task = mListTasks.begin();
      chosen_handler->ReceiveTask(*task);
      mListTasks.erase(task);
    }
  }
  printf("[INFO] Finish assigning requirements\n");
}

/**
 * @brief
 *
 */
void Server::DecreaseNumberOfActiveHandlers()
{
  // auto handler_pos = std::find(mListHandlers.begin(), mListHandlers.end(), handler);
  // if (handler_pos != mListHandlers.end())
  // {
  //   mListHandlers.erase(handler_pos);
  // }
  mNumberOfHandlers--;
  printf("[DEBUG] Number Of Handlers Decreased, current number: %u\n", mNumberOfHandlers);
  std::lock_guard<std::mutex> lk(this->mMutex);
}

/**
 * @brief
 *
 */
void Server::WriteReport()
{
  while (mNumberOfHandlers > 0)
  {
    // printf("[DEBUG] hehe here num %u\n", mNumberOfHandlers);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  printf("[DEBUG] Start writing file\n");
  std::ofstream file(mLogFile, std::ios::app);
  if (file.is_open())
  {
    while (!mListHandlers.empty())
    {
      auto handler = mListHandlers.begin();
      file << "Name: " << handler->get()->GetName() << " - Worklog: " << std::to_string(handler->get()->GetWorkLog()) << "\n";
      mListHandlers.erase(handler);
    }
    file.close();
  }
  else
  {
    printf("[ERROR] Cannot open file\n");
  }
}

/**
 * @brief
 *
 */
void Server::ReadReport()
{
  std::ifstream file(mLogFile);
  if (file.is_open())
  {
    std::string line;
    while (getline(file, line))
    {
      std::cout << line << std::endl;
    }
  }
  else
  {
    printf("[ERROR] Cannot open file\n");
  }
}