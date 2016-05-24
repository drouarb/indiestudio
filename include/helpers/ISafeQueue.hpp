//
// ISafeQueue.hpp for safequeue in /home/trouve_b/Desktop/CPP_project/cpp_plazza/tests_thr_pool
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed Apr 13 12:02:33 2016 Alexis Trouve
// Last update Mon Apr 25 15:19:03 2016 Alexis Trouve
//

#ifndef ISAFEQUEUE_HPP_
# define ISAFEQUEUE_HPP_

/*!
 * \class ISafeQueue
 * \brief ISafequeue is used as a overload of the std::queue
 * for the uses of this queue in several threads, this queue
 * must be used to have not threads conflict.
 * This class is templated to be used in every cases and to be
 * the best generic as possible.
 */

template<typename Type>
class	ISafeQueue
{
public:
  virtual ~ISafeQueue() {};

  /*!
   * \brief Just push an element in the queue, be carefull
   * to use lock in this method.
   */

  virtual void push(Type value) = 0;

  /*!
   * \brief try to pop an element from the queue and to put it
   * in the passed parameter this method always delete the poped
   * element from the queue.
   * this method return false if the queue is empty and true
   * if you have pop an element.
   */

  virtual bool tryPop(Type *value) = 0;

  /*!
   * \brief return false if the queue if have have called
   * the method setFinished.
   */

  virtual bool isFinished() = 0;

  /*!
   * \brief set the safequeue to finished, when the safequeue
   * is set to finished can't anymore push new element in it.
   * When the safequeue is finished you can't set it to unfinished.
   */

  virtual void setFinished() = 0;

  /*!
   * \brief return true if the queue is empty and false in the
   * other cases.
   */

  virtual bool empty() = 0;

  /*!
   * \brief clear the content of te safequeue
   */

  virtual void clear() = 0;

  /*!
   * \brief return the number of element present in the queue.
   */

  virtual unsigned int size() = 0;
};

#endif
