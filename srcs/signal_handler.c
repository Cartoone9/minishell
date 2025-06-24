/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:50:01 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_sigint(int signal)
{
	(void)signal;
	if (g_signal == 0)
		g_signal = 2;
	write(1, "^C", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal == 2)
		close(STDIN_FILENO);
}

void	ft_handle_hdoc_sigint(int signal)
{
	(void)signal;
	g_signal = 1;
	write(1, "^C", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
}

void	ft_handle_pipe_sigint(int signal)
{
	(void)signal;
	g_signal = 3;
	write(1, "^C", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
}

/*void	ft_handle_spe_sigint(int signal)*/
/*{*/
/*	(void)signal;*/
/*	if (g_signal == 0)*/
/*		g_signal = 3;*/
/*	rl_replace_line("", 0);*/
/*	rl_on_new_line();*/
/*	if (g_signal == 3)*/
/*		rl_redisplay();*/
/*}*/
