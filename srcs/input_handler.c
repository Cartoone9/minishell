/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_get_input(t_data *data, int piped)
{
	int	status;

	if (ft_setup_prompt_and_signals(data, piped) != 0)
		return (0);
	g_signal = 0;
	data->input = readline(data->prompt);
	if (ft_handle_input_result(data, piped) == ERROR)
		return (ERROR);
	status = ft_tokenization(data);
	if (status == 1)
	{
		add_history(data->full_input);
	}
	return (0);
}

int	ft_setup_prompt_and_signals(t_data *data, int piped)
{
	data->prompt = NULL;
	if (!piped)
		data->prompt = ft_make_prompt(data);
	else if (ft_xterm_isset(data))
		data->prompt = "\001\033[1;38;2;108;86;249m\002pipe>\001\033[0m\002 ";
	else
		data->prompt = "pipe> ";
	if (!data->prompt)
	{
		ft_error("missing prompt in get_input");
		return (1);
	}
	if (piped)
		ft_pipe_signals();
	else
		ft_signals();
	return (0);
}

void	ft_merge_data_input(t_data *data)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin_input(data->full_input, data->input);
	if (!temp)
		ft_exit_seq(data, errno);
	if (data->input)
		ft_free_str(&data->input);
	if (data->full_input)
		ft_free_str(&data->full_input);
	data->full_input = temp;
}

/**/
/*int	ft_handle_post_read_signals(t_data *data)*/
/*{*/
/*	printf("fish\n");*/
/*	if (g_signal == 2)*/
/*	{*/
/*		g_signal = 0;*/
/*		data->exit_status = 130;*/
/*	}*/
/*	else if (g_signal == 1)*/
/*	{*/
/*		data->exit_status = 130;*/
/*		add_history(data->full_input);*/
/*		if (dup2(g_stdin_save, STDIN_FILENO) == -1)*/
/*		{*/
/*			ft_error("dup2 failed in get_input signal handler");*/
/*			return (0);*/
/*		}*/
/*	}*/
/*	return (1);*/
/*}*/
