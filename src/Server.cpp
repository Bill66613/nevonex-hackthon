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
 * @brief 
 * 
 * @param rFilePath 
 */
void Server::UpdateRequirementPath(std::string &rFilePath)
{
  mRequirementPath = rFilePath;
}

/**
 * @brief 
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
    printf("Cannot open file");
  }
}

/**
 * @brief 
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
      file << "Name: " << mListHandlers[i].GetName() << " - Worklog: " << mListHandlers[i].GetWorkLog() << "\n";
    }
    file.close();
  }
  else
  {
    printf("Cannot open file");
  }
}

Server Boss;