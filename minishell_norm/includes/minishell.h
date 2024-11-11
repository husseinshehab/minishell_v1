/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:59:06 by hshehab           #+#    #+#             */
/*   Updated: 2024/11/05 12:13:53 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ftprint/ft_printf.h"
# include "../getnextline/get_next_line.h"
# include "../libft/libft.h"
# include <aio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_RESET "\x1b[0m"

extern int				g_signal_num;

typedef enum s_type
{
	WORD,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC,
	ENV_VAR,
}						t_type;

typedef struct s_execution_organiser
{
	int					current_pipe;
	int					input_fd;
	int					output_fd;
	int					input_file_count;
	int					output_file_count;
	int					pipes_count;
	int					has_in_file;
	int					has_out_file;
	int					is_redir_pipe;
	int					heredoc;
	int					child_count;
	int					heredoc_second;
}						t_execution_organiser;

typedef enum e_file_type
{
	UNSET,
	EXECUTABLE,
	DONE,
	OUT,
	OUT_APPEND,
	IN,
	IN_APPEND,
}						t_file_type;

typedef struct s_treenode
{
	t_type				type;
	int					pipefd[2];
	t_file_type			file_type;
	char				**value;
	struct s_treenode	*left;
	struct s_treenode	*right;
}						t_treenode;

typedef struct s_node
{
	struct s_node		*next;
	struct s_node		*previous;
	char				*string;
	t_type				type;
}						t_node;

typedef struct s_env
{
	char				*string;
	struct s_env		*next;
	int					flag;
}						t_env;

typedef struct s_minishell
{
	t_env				*env;
	t_node				*head;
	int					infd;
	int					outfd;
	t_treenode			*tree;
	int					exit_code;
}						t_minishell;

typedef struct s_stat
{
	dev_t				st_dev;
	ino_t				st_ino;
	mode_t				st_mode;
	nlink_t				st_nlink;
	uid_t				st_uid;
	gid_t				st_gid;
	dev_t				st_rdev;
	off_t				st_size;
	long				st_blksize;
	blkcnt_t			st_blocks;
}						t_stat;

typedef struct s_strlist
{
	char				c;
	struct s_strlist	*next;
}						t_strlist;

void					execute_here_doc_main(t_minishell *mini,
							t_treenode *root, t_env *env);
int						ft_pwd(t_env *head);
int						ft_cd(char **path, t_minishell *mini);
int						ft_echo(char **command);
t_minishell				*init_minishell(void);
void					printlinkedlist_tok(t_node *head);
void					printlinkedlist_env(t_env *head);
void					freelinkedlist_ev(t_env *head);
t_env					*createnode_env(char *str);
void					freelinkedlist_tok(t_node *head);
t_env					*pushtoback_env(t_env *head, char *str);
t_env					*duplicate_env_list(t_minishell *mini);
t_node					*createnode(char *str, t_type type);
t_node					*pushtoback(t_node *head, char *str, t_type type);
char					*trim_my_token(char *src, int j, int i);
char					*extract_quotes(char *str, int *i, int j, t_type *type);
char					*extract_quotes1(char *str, int *i, int j,
							t_type *type);
char					*extract_pipe(char *str, int *i, int j, t_type *type);
char					*extract_redirectin(char *str, int *i, int j,
							t_type *type);
char					*extract_redirectout(char *str, int *i, int j,
							t_type *type);
char					*extract_appendin(char *str, int *i, int j,
							t_type *type);
char					*extract_heredoc(char *str, int *i, int j,
							t_type *type);
char					*extract_cmd(char *str, int *i, int j, t_type *type);
char					*extract_token(char *str, int *i, t_type *type);
void					tokenize_input(t_minishell *mini, char *inputstr);
void					swap_nodes(t_env *a, t_env *b);
void					bubble_sort_list(t_env *head);
void					init_env(t_minishell *mini, char **env);
void					free_mini(t_minishell *mini);
void					resetfd(t_minishell *mini);
char					*get_env_path(const char *location, t_minishell *mini,
							int size);
int						update_old_pwd(t_minishell *mini,
							const char *currentpwd);
int						go_to_home(t_minishell *mini);
int						go_back(t_minishell *mini);
int						go_to_last(t_minishell *mini);
int						ft_cd(char **path, t_minishell *mini);
int						no_new_line(char **s, int *j);
void					print_echo_arg(char *str);
int						ft_echo(char **command);
int						ft_export(char **command, t_minishell *mini);
int						ft_env(t_minishell *mini);
t_treenode				*buildtree(t_node *head);
void					leftordertraversal(t_treenode *root);
void					rearrange(t_node **head);
int						thereispipe(t_node *head);
void					split_token_list(t_node *head, t_node **left,
							t_node **right, t_node *min);
t_treenode				*create_treenode(t_type type);
void					free_tree(t_treenode *root);
t_treenode				*buildtree(t_node *head);
t_treenode				*create_tree_node_if_no_special(t_node *head);
t_node					*find_min_redirection(t_node *head);
void					split_token_list(t_node *head, t_node **left,
							t_node **right, t_node *min);
int						thereispipe(t_node *head);
int						thereisred(t_node *head);
void					process_type_less_equal_2(t_node **ptr,
							t_node **newlist);
void					process_type_greater_2(t_node **ptr, t_node **newlist);
void					clean_and_update_head(t_node **head, t_node *newlist);
void					rearrange(t_node **head);
int						listlength(t_node *head);
char					**joinlist(t_node *head);
int						count_rows(char **matrix);
char					**copymatrix1(char **oldmatrix);
int						listlength1(t_env *head);
char					**joinlist1(t_env *head);
int						is_redir_type(t_type type);
int						type_exists(t_treenode *root, t_type type);
void					execute(t_minishell *mini, t_treenode *root,
							t_env *env);
int						update_pwd(t_minishell *mini, const char *currentpwd);
size_t					find_equal_sign_index(char *str);
char					*create_header(char *str, size_t index);
int						foundenv(char *str, t_env *env);
int						is_valid_env_name(char *str);
char					*last_input(t_treenode *root, int *flag);
char					*last_output(t_treenode *root, int *flag);
void					quotes(t_node *head, t_env *env);
char					*expand(char *str, t_env *env);
char					*returnvar(char *str, t_env *head);
void					execute_tree(t_minishell *mini, t_treenode *root,
							t_env *env);
int						ft_unset(t_minishell *mini);
void					setup_signals(void);
void					ctrl_c_pressed_child(int signal_number);
void					ctrl_c_pressed(int signal_num);
void					printlinkedlist_export(t_env *head);
void					create_pipe(int pipefd[2]);
pid_t					fork_process(void);
void					close_pipe_and_wait(int pipefd[2], pid_t left_pid,
							pid_t right_pid);
void					execute_right_command(t_minishell *mini,
							t_treenode *root, t_env *env, int pipefd[2]);
void					execute_left_command(t_minishell *mini,
							t_treenode *root, t_env *env, int pipefd[2]);
int						belongsto(char c);
int						ft_strcmp(const char *s1, const char *s2);
int						is_builtin(char *str);
void					quit_heredoc(int sig);
void					remove_duplicate_from_node(t_env *head);
void					ft_exit(t_minishell *mini);
void					update_question_mark(t_minishell *mini);
int						execute_builtin(char **str, t_minishell *mini);
int						check_tree(t_treenode *root);
int						belongstozabta(char *s);
void					ft_exort_helper(char **command, t_minishell *mini,
							int i);
void					update_env(char *str, t_env *env);
char					*process_nextpart(char *str, char *header);
void					handle_command(char **command, t_minishell *mini,
							int *flag);
int						go_back_helper(char *prev_pwd, char *currentpwd);
t_treenode				*get_heredoc(t_treenode *root);
void					execute_heredoc(t_treenode *root, t_env *env,
							char *delimeter);
void					perform_execution(t_minishell *mini, t_treenode *root,
							t_env *env);
char					*get_command_path(char *cmd, t_env *my_env);
int						handle_tree_checks(t_treenode *root);
void					execute_builtin_command(t_treenode *root,
							t_minishell *mini);
void					execute_external_command(t_treenode *root,
							t_minishell *mini, t_env *env);
void					handle_output_redirection(char *lastout, int flag);
void					handle_input_redirection(int flag_fd, char *lastin);
char					*colorize(const char *text, const char *color);
int						check_input(t_node *head);

#endif
