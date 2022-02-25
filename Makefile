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
		 pipex_utils \
		 bonus \

GNL_FILES = get_next_line \
			get_next_line_utils \

PIPEX_DIR = pipex_dir/

GNL_DIR = gnl/

SRCS =	$(addprefix $(PIPEX_DIR), $(addsuffix .c, $(FILES))) \
		$(addprefix $(GNL_DIR), $(addsuffix .c, $(GNL_FILES))) \

OBJS =	$(addprefix $(PIPEX_DIR), $(addsuffix .o, $(FILES))) \
		$(addprefix $(GNL_DIR), $(addsuffix .o, $(GNL_FILES))) \

.c.o:	$(SRCS)
		$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $@ $^ $(FLAGS)

all: $(NAME)

bonus: all

clean:
	make clean -C libft 
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
