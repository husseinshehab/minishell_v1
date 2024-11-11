CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -g
EXTRAFLAGS = -lreadline -lncurses
 
SRC = main.c \
		main1.c \
		signal.c \
		buildtree/buildtree.c \
		buildtree/buildtree1.c \
		buildtree/buildtree2.c \
		buildtree/buildtree3.c \
		buildtree/buildtree4.c \
		builtins/cd.c \
		builtins/cd1.c \
		builtins/cd2.c \
		builtins/export.c \
		builtins/export1.c \
		builtins/export2.c \
		builtins/pwd.c \
		builtins/echo.c \
		builtins/exit.c \
		builtins/env.c \
		builtins/unset.c \
		execution/execution1.c \
		execution/execution11.c \
		execution/execution12.c \
		execution/execution.c \
		execution/execution2.c \
		execution/execution3.c \
		execution/execution_heredoc.c \
		execution/execution_heredoc1.c \
		expand/expand1.c \
		expand/expand2.c \
		lex/tokens.c \
		lex/tokens1.c \
		lex/tokens2.c \
		lex/utils.c \
		lex/utils1.c \
		lex/utils2.c \
		lex/utils3.c 

OBJ = $(SRC:.c=.o)
EXEC = minishell
LIBDIR = ftprint
LIBDIR1 = libft
LIBDIR2 = getnextline
LIB = libftprintf.a
LIB1 = libft.a
LIB2 = getnextline.a


all: $(LIBDIR)/$(LIB) $(LIBDIR2)/$(LIB2) $(LIBDIR1)/$(LIB1) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)  $(LIB) $(LIB1) $(LIB2) $(EXTRAFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I includes -c $< -o $@

$(LIBDIR)/$(LIB):
	$(MAKE) -C $(LIBDIR)
	cp $(LIBDIR)/$(LIB) .

$(LIBDIR1)/$(LIB1):
	$(MAKE) -C $(LIBDIR1)
	cp $(LIBDIR1)/$(LIB1) .

$(LIBDIR2)/$(LIB2):
	$(MAKE) -C $(LIBDIR2)
	cp $(LIBDIR2)/$(LIB2) .

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBDIR) clean
	$(MAKE) -C $(LIBDIR1) clean
	$(MAKE) -C $(LIBDIR2) clean

fclean: clean
	rm -f $(EXEC) $(LIB)
	$(MAKE) -C $(LIBDIR) fclean
	$(MAKE) -C $(LIBDIR1) fclean
	$(MAKE) -C $(LIBDIR2) fclean

re: fclean all

.PHONY: all clean fclean re

