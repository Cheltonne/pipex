NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FLAGS = -Llibft -lft
RM = rm -f

FILES = pipex \
	     parsing \
		 processes \
		 error_handling \
		 free_fct \

SRCS =  $(addsuffix .c, $(FILES))

OBJS =	$(addsuffix .o, $(FILES))

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $@ $^ $(FLAGS)
	make clean

all: $(NAME)

clean:
	make clean -C libft 
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

norminette: $(SRCS)
	norminette $(SRCS) $(addsuffix .h, $(NAME))

re: clean all

.PHONY: all clean fclean re
