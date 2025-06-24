/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:24:26 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_close_fd_in(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
}

void	ft_close_fd_out(t_cmd *cmd)
{
	if (cmd->fd_out > 0)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}

void	ft_close_all_fd(t_data *data)
{
	t_cmd	*cursor_cmd;

	if (!data || !data->cmd_list)
		return ;
	cursor_cmd = data->cmd_list;
	while (cursor_cmd)
	{
		if (cursor_cmd->fd_in > 0)
		{
			close(cursor_cmd->fd_in);
			cursor_cmd->fd_in = -1;
		}
		if (cursor_cmd->fd_out > 0)
		{
			close(cursor_cmd->fd_out);
			cursor_cmd->fd_out = -1;
		}
		cursor_cmd = cursor_cmd->next;
	}
}

void	ft_close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_unlink_hdoc_file(int hdoc_filen)
{
	char	*itoa_filen;
	char	*filename;

	if (hdoc_filen)
		itoa_filen = ft_itoa(hdoc_filen);
	else
		itoa_filen = NULL;
	if (itoa_filen)
	{
		filename = ft_strjoin(HDOC_FILE, itoa_filen);
		ft_free_str(&itoa_filen);
		if (filename)
		{
			unlink(filename);
			ft_free_str(&filename);
		}
	}
}
