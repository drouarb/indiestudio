//
// ScopedLock.hpp for scopedlock in /home/trouve_b/Desktop/CPP_project/cpp_plazza/tests_thr_pool
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed Apr 13 10:32:27 2016 Alexis Trouve
// Last update Mon May 30 14:23:42 2016 Alexis Trouve
//


#ifndef SCOPEDLOCK_HPP_
# define SCOPEDLOCK_HPP_

#include <mutex>

/*!
 * \class ScopedLock
 * \brief ScopedLock is used to easily lock and unlock mutex
 * the mutex must be initialized before used it in ScopedLock
 * with ScopedLock you can for exemple use it like this:
 *
 *
 *
 * void myfunc(int *value, Mutex *myMutex)
 * {
 *	ScopedLock(myMutex);
 *	(*value)++;
 * }
 *
 *
 *
 * when the destroyer of the classe ScopedLock is called
 * automatically the Mutex is unlock.
 */

class	ScopedLock final
{
private:
  std::mutex		*myMutex;
private:

  /*!
   * \brief the copy by constructor is not allowed
   */

  ScopedLock(ScopedLock const&);

  /*!
   * \brief the copy with the operator= is not allowed
   */

  ScopedLock& operator=(ScopedLock const&);
public:

  /*!
   * \brief lock the Mutex.
   */

  ScopedLock(std::mutex *nMutex);

  /*!
   * \brief unlock the mutex.
   */

  ~ScopedLock();
};

#endif
