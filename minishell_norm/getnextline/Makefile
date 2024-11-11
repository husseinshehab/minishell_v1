CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = getnextline.a
SRCS = get_next_line.c get_next_line_utils.c ft_split.c ft_strjoin.c parsingmap.c parsingmap1.c parsingmap2.c parsingmap3.c
OBJS = $(SRCS:.c=.o)
HEADERS = get_next_line.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
