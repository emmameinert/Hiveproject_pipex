NAME = pipex

SRC = pipex ./sources/processes ./sources/utils

HEADER = ./headers/pipex.h 

CC = cc 

FLAGS = -Wall -Wextra -Werror -I $(HEADER)

FILES  = $(addsuffix .c,$(SRC))

OBJECTS = $(addsuffix .o, $(SRC))

LIBFT = ./sources/libft 

all: $(NAME)

$(NAME): $(OBJECTS) 
		cd $(LIBFT) && $(MAKE)
		$(CC) $(FLAGS) $^ -L$(LIBFT) -lft -o $@

clean:
		rm -f $(OBJECTS)
		cd $(LIBFT) && $(MAKE) clean

fclean: clean 
		rm -f $(NAME)

re: fclean all 