/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldarsa <ldarsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:53:35 by ldarsa            #+#    #+#             */
/*   Updated: 2024/11/05 07:41:09 by ldarsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ctrl_c_pressed(int signal_num)
{
	(void)signal_num;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	write(3, "asd\n\n\n", 6);
}

void	ctrl_c_pressed_child(int signal_number)
{
	(void)signal_number;
	if (signal_number == 2)
		g_signal_num = 130;
	else
	{
		ft_putstr_fd("exit", 1);
		g_signal_num = 131;
	}
	write(1, "\n", 1);
}

void	setup_signals(void)
{
	signal(SIGINT, ctrl_c_pressed);
	signal(SIGQUIT, SIG_IGN);
}
