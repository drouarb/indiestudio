//
// ScopedLock.cpp for ScopedLock in /home/trouve_b/Desktop/CPP_project/cpp_plazza/tests_thr_pool
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed Apr 13 10:35:39 2016 Alexis Trouve
// Last update Mon May 30 14:24:04 2016 Alexis Trouve
//

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(std::mutex *nMutex)
{
  myMutex = nMutex;
  myMutex->lock();
}

ScopedLock::~ScopedLock()
{
  myMutex->unlock();
}
