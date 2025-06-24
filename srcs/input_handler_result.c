/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_result.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

static int	ft_handle_piped_signal_dup(t_data *data)
{
	add_history(data->full_input);
	data->exit_status = 130;
	if (dup2(g_stdin_save, STDIN_FILENO) == -1)
		return (ft_error("dup2 failed in wait_for_hdoc"), ERROR);
	return (0);
}

static int	ft_handle_null_input_signaled(t_data *data, int piped)
{
	if (!piped && g_signal == 2)
	{
		data->exit_status = 130;
		if (dup2(g_stdin_save, STDIN_FILENO) == -1)
			return (ft_error("dup2 failed in wait_for_hdoc"), ERROR);
	}
	else if (piped && g_signal == 3)
	{
		if (ft_handle_piped_signal_dup(data) == ERROR)
			return (ERROR);
		return (ERROR);
	}
	else if (piped)
	{
		if (ft_handle_piped_signal_dup(data) == ERROR)
			return (ERROR);
	}
	g_signal = 0;
	return (0);
}

static int	ft_handle_null_input(t_data *data, int piped)
{
	if (!piped)
		ft_free_str(&data->prompt);
	if (g_signal == 0)
	{
		if (piped)
			ft_error_min("minishell : syntax error: unexpected end of file");
		ft_exit_seq(data, EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	else
	{
		return (ft_handle_null_input_signaled(data, piped));
	}
}

static int	ft_handle_valid_input(t_data *data, int piped)
{
	if (!piped)
	{
		ft_free_str(&data->prompt);
		data->prompt = NULL;
	}
	if (data->input[0] == '\0' && g_signal == 0)
	{
		ft_free_str(&data->input);
		ft_get_input(data, piped);
		return (0);
	}
	if (ft_check_missing_quotes(data->input))
	{
		data->exit_status = 1;
		add_history(data->input);
		ft_free_str(&data->input);
		ft_get_input(data, piped);
		return (0);
	}
	return (0);
}

int	ft_handle_input_result(t_data *data, int piped)
{
	if (!data->input)
	{
		return (ft_handle_null_input(data, piped));
	}
	else
	{
		return (ft_handle_valid_input(data, piped));
	}
}
