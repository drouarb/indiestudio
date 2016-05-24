//
// Thread.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Fri Apr 15 14:03:55 2016 Esteban Lewis
// Last update Tue May 24 15:16:38 2016 Esteban Lewis
//

#ifndef  THREAD_HPP_
# define THREAD_HPP_

# include <iostream>
# include <stdexcept>
# include <pthread.h>

namespace				helpers
{
  template <typename FUNC, typename OBJECT>
  class					Thread
  {
    struct				Arguments
    {
      Arguments(FUNC f, OBJECT * o) : func(f), obj(o)
      { }

      FUNC				func;
      OBJECT *				obj;
    };

  public:
    Thread(FUNC func, OBJECT * obj)
    {
      Arguments * a = new Arguments(func, obj);

      if (pthread_create(&thread, NULL, reinterpret_cast<void*(*)(void*)>(&c_fun), a))
	throw (std::runtime_error("pthread_create"));
    }

    ~Thread()
    { }

    void *				join()
    {
      void *				retval;

      retval = NULL;
      if (pthread_join(thread, &retval))
	throw (std::runtime_error("pthread_join"));
      return (retval);
    }

    void				cancel()
    {
      if (pthread_cancel(thread))
	throw (std::runtime_error("pthread_cancel"));
    }

    static void				exit(void * retval)
    {
      pthread_exit(retval);
    }

  private:
    pthread_t				thread;

    static void *			c_fun(Arguments * a)
    {
      (a->obj->*(a->func))();
      delete (a);
      return (NULL);
    }
  };
};

#endif
