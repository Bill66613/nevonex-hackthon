#include "Server.hpp"
#include <fstream>
#include <iostream>
#include <thread>

Server::Server()
: mMaxHandlers(MAX_HANDLERS)
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
void Server::GetRequirement(std::string &rFilePath)
{
  std::ifstream file(rFilePath);
  int number;
  while (file >> number)
  {
    mListTasks.push(number);
  }
  file.close();
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
  
}

/**
 * @brief 
 * 
 */
void Server::ReadReport()
{
}

/**
 * @brief 
 * 
 */
void Server::WriteReport()
{
}

Server Boss;