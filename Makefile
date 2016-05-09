##
## Makefile for indie in /home/drouar_b/rendu/cpp_indie_studio
## 
## Made by Benjamin DROUARD
## Login   <drouar_b@epitech.eu>
## 
## Started on  Mon May  2 14:03:38 2016 Benjamin DROUARD
## Last update Mon May  9 10:40:47 2016 Alexis Trouve
##

NAME		=	indie

CXX		=	g++ ${MYDBG}

RM		=	rm -rf

SRCS		=	srcs/main.cpp			\
			srcs/World.cpp			\
			srcs/NSocket.cpp		\
			srcs/SocketException.cpp	\

OBJS		=	$(SRCS:srcs/%.cpp=obj/%.o)

INCLUDES	=	-I includes/

LIBS		=	-lpthread

CXXFLAGS	+=	$(INCLUDES) -W -Wall -Wextra

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CXX) $(OBJS) $(LIBS) -o $(NAME)

obj/%.o		:	srcs/%.cpp
			@ [ -d $(@D) ] || echo "mkdir -p $(@D)"; mkdir -p $(@D)
			$(CXX) -o $@ -c $< $(CXXFLAGS)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean
			@$(MAKE)
