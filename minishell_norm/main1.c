/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:38:47 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 12:13:00 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	*mini;
	int			pid;
	char		*str;
	char		*color_str;
	int			status;

	(void)ac;
	(void)av;
	mini = init_minishell();
	init_env(mini, env);
	while (1)
	{
		remove_duplicate_from_node(mini->env);
		setup_signals();
		str = "|Minishell|->";
		color_str = colorize(str, COLOR_GREEN);
		input = readline(color_str);
		if (!input)
		{
			free(color_str);
			break ;
		}
		if (input[0] == '\0')
		{
			free(color_str);
			free(input);
			continue ;
		}
		mini->head = NULL;
		mini->tree = NULL;
		tokenize_input(mini, input);
		if (!check_input(mini->head))
		{
			freelinkedlist_tok(mini->head);
			free(color_str);
			free(input);
			mini->exit_code = 1;
			update_question_mark(mini);
			continue ;
		}
		quotes(mini->head, mini->env);
		rearrange(&(mini->head));
		mini->tree = buildtree(mini->head);
		pid = fork();
		signal(SIGINT, ctrl_c_pressed_child);
		signal(SIGQUIT, ctrl_c_pressed_child);
		g_signal_num = 0;
		if (pid == 0)
		{
			if (mini->tree && (mini->tree->type != WORD
					|| !is_builtin(mini->tree->value[0])))
				execute(mini, mini->tree, mini->env);
			exit(0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (mini->tree && mini->tree->type == WORD
				&& is_builtin(mini->tree->value[0]))
				mini->exit_code = execute_builtin(mini->tree->value, mini);
			else
			{
				if (WIFEXITED(status))
					mini->exit_code = WEXITSTATUS(status);
				else
					mini->exit_code = 0;
			}
		}
		else
		{
			perror("fork");
			exit(1);
		}
		if (g_signal_num != 0)
			mini->exit_code = g_signal_num;
		update_question_mark(mini);
		add_history(input);
		free(color_str);
		free(input);
		free_tree(mini->tree);
	}
	freelinkedlist_ev(mini->env);
	free(mini);
	return (0);
}
