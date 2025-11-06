NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra

SHARED = path_handler.c mem_utilities.c str_utilities.c str_utilities_2.c str_utilities_3.c str_utilities_4.c str_utilities_5.c

SRCS_M = ${SHARED} main.c parse_input.c setup_io_operations.c error_handling.c
SRCS_B = ${SHARED} main_bonus.c parse_input_bonus.c setup_io_operations_bonus.c setup_heredoc_file_bonus.c error_handling_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS_M = ${SRCS_M:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS_M)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(NAME)_bonus
$(NAME)_bonus: $(OBJS_B)
	$(CC) $(CFLAGS) $^ -o $(NAME)
	@touch $@

clean:
	rm -f $(OBJS_M) $(OBJS_B) $(NAME)_bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re