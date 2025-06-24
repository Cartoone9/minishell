/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_tokenization(t_data *data)
{
	if (ft_tokenize_current_input(data) == 1)
		return (0);
	if (ft_check_tkn_error(data->tkn_list))
	{
		data->error = 1;
		return (0);
	}
	if (ft_process_heredocs(data) == 1)
		return (1);
	if (ft_islast_pipe(data->tkn_list))
	{
		ft_get_input(data, 1);
	}
	return (0);
}

int	ft_tokenize_current_input(t_data *data)
{
	if (!data->input)
		return (1);
	if (ft_empty_str(data->input))
	{
		add_history(data->input);
		ft_free_str(&data->input);
		return (1);
	}
	if (ft_build_or_append_tkn_list(data))
	{
		data->exit_status = 0;
		add_history(data->input);
		ft_free_str(&data->input);
		return (1);
	}
	ft_merge_data_input(data);
	return (0);
}

int	ft_build_or_append_tkn_list(t_data *data)
{
	t_tkn	*tkn_cursor;

	if (!data->tkn_list)
	{
		data->tkn_list = ft_build_tkn_list(data->input, data);
		if (!data->tkn_list)
			ft_exit_seq(data, errno);
		else if (data->tkn_list->arg && data->tkn_list->arg[0] == '\0'
			&& !data->tkn_list->next && ft_strchr(data->input, '$'))
		{
			data->exit_status = 0;
			return (1);
		}
	}
	else
	{
		tkn_cursor = data->tkn_list;
		while (tkn_cursor->next)
			tkn_cursor = tkn_cursor->next;
		tkn_cursor->next = ft_build_tkn_list(data->input, data);
		if (!tkn_cursor->next)
			ft_exit_seq(data, errno);
	}
	return (0);
}

int	ft_process_heredocs(t_data *data)
{
	t_hdoc	*hdoc_cursor;
	int		ret;

	if (!ft_isthere_hdoc(data))
		return (0);
	hdoc_cursor = data->hdoc_list;
	while (hdoc_cursor)
	{
		if (!hdoc_cursor->saved)
		{
			ret = ft_wait_for_hdoc(data, hdoc_cursor->hdoc_eof);
			if (ret == ERROR)
				ft_exit_seq(data, errno);
			else if (ret == 1)
				return (1);
			hdoc_cursor->saved = 1;
		}
		hdoc_cursor = hdoc_cursor->next;
	}
	return (0);
}

int	ft_islast_pipe(t_tkn *tkn_list)
{
	while (tkn_list && tkn_list->type != ERROR && tkn_list->next)
		tkn_list = tkn_list->next;
	if (tkn_list->type == PIPE_ID)
		return (1);
	return (0);
}
