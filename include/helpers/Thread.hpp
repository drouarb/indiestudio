//
// Thread.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Fri Apr 15 14:03:55 2016 Esteban Lewis
// Last update Fri May 20 22:30:05 2016 Esteban Lewis
//

#ifndef  PLAZZA_THREAD_HPP_
# define PLAZZA_THREAD_HPP_

# include <iostream>
# include <stdexcept>
# include <pthread.h>

namespace				gauntlet
{
  template <typename FUNC, typename OBJECT>
  class					Thread
  {
    struct				Arguments
    {
      Arguments(FUNC f, OBJECT * o, void * a) : func(f), obj(o), arg(a)
      { }
      
      FUNC				func;
      OBJECT *				obj;
      void *				arg;
    };

  public:
    Thread(FUNC func, OBJECT * obj, void * arg)
    {
      Arguments * a = new Arguments(func, obj, arg);

      if (pthread_create(&thread, NULL, reinterpret_cast<void*(*)(void*)>(&c_fun), a))
	throw (std::runtime_error("pthread_create"));
    }

    ~Thread()
    { }

    void *				Join()
    {
      void *				retval;

      retval = NULL;
      if (pthread_join(thread, &retval))
	throw (std::runtime_error("pthread_join"));
      return (retval);
    }

    void				Cancel()
    {
      if (pthread_cancel(thread))
	throw (std::runtime_error("pthread_cancel"));
    }

    static void				Exit(void * retval)
    {
      pthread_exit(retval);
    }

  private:
    pthread_t				thread;

    static void *			c_fun(Arguments * a)
    {
      (a->obj->*(a->func))(a->arg);
      delete (a);
      return (NULL);
    }
  };
};

#endif
