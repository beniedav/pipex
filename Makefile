NAME = pipex

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DEP = $(filter-out $(LIBFT), $(wildcard $(LIBFT_DIR)/*))

SRCS = pipex.c init_struct.c error_and_free.c processes.c init_struct_helper.c path_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) 

$(LIBFT): $(LIBFT_DIR) $(LIBFT_DEP)
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c pipex.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
