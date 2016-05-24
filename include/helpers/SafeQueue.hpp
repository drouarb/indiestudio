//
// SafeQueue.hpp for SafeQueue in /home/trouve_b/Desktop/CPP_project/cpp_plazza/tests_thr_pool
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed Apr 13 12:08:45 2016 Alexis Trouve
// Last update Mon May  2 13:58:46 2016 Alexis Trouve
//

#ifndef SAFEQUEUE_HPP_
# define SAFEQUEUE_HPP_

#include <queue>
#include "ScopedLock.hpp"
#include "ISafeQueue.hpp"
#include "Mutex.hpp"

template<typename Type>
class	SafeQueue : public ISafeQueue<Type>
{
private:
  std::queue<Type>	myQueue;
  Mutex			*myMutex;
  bool			finished;
public:
  SafeQueue();
  ~SafeQueue();
  virtual void	push(Type value);
  virtual bool	tryPop(Type *value);
  virtual bool	isFinished();
  virtual void	setFinished();
  virtual bool	empty();
  virtual void	clear();
  virtual unsigned int size();
};




template <typename Type>
SafeQueue<Type>::SafeQueue()
{
  finished = false;
  myMutex = new Mutex();
}

template <typename Type>
SafeQueue<Type>::~SafeQueue()
{
  ;
}

template <typename Type>
void            SafeQueue<Type>::push(Type value)
{
  myMutex->lock();
  if (finished == true)
    return ;
  myQueue.push(value);
  myMutex->unlock();
}

template <typename Type>
bool            SafeQueue<Type>::tryPop(Type *value)
{
  ScopedLock    myScop(myMutex);

  if (myQueue.empty())
    return (false);
  (*value) = myQueue.front();
  myQueue.pop();
  return (true);
}

template <typename Type>
bool            SafeQueue<Type>::isFinished()
{
  ScopedLock	myScop(myMutex);

  return (finished);
}

template <typename Type>
void            SafeQueue<Type>::setFinished()
{
  ScopedLock	myScop(myMutex);

  finished = true;
}

template <typename Type>
bool		SafeQueue<Type>::empty()
{
  ScopedLock	myScop(myMutex);

  return (myQueue.empty());
}

template <typename Type>
void		SafeQueue<Type>::clear()
{
  ScopedLock	myScop(myMutex);

  while (myQueue.empty() == false)
    myQueue.pop();
}

template <typename Type>
unsigned int	SafeQueue<Type>::size()
{
  ScopedLock	myScop(myMutex);

  return (myQueue.size());
}

#endif
