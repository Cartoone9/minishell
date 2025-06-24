/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:40:57 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 20:45:38 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_handle_redir_token(t_data *data, t_cmd *cmd, t_tkn **tkn_ptr,
		t_hdoc **hdoc_ptr)
{
	int		ret;
	t_tkn	*current_tkn;

	current_tkn = *tkn_ptr;
	ret = ft_handle_redirection(data, cmd, current_tkn, hdoc_ptr);
	if (ret == 2)
	{
		current_tkn = current_tkn->next;
		if (current_tkn)
			current_tkn = current_tkn->next;
		*tkn_ptr = current_tkn;
		return (2);
	}
	return (ret);
}

int	ft_handle_redirection(t_data *data, t_cmd *cmd, t_tkn *tkn,
		t_hdoc **hdoc_ptr)
{
	int	ret;

	ret = 0;
	if (cmd->error != 0)
		return (0);
	if (tkn->type == IN_ID || tkn->type == HDOC_IN_ID)
	{
		ret = ft_process_input_redir(data, cmd, tkn, *hdoc_ptr);
		if (ret == 0 && tkn->type == HDOC_IN_ID && *hdoc_ptr)
			*hdoc_ptr = (*hdoc_ptr)->next;
	}
	else if (tkn->type == OUT_ID || tkn->type == A_OUT_ID)
	{
		ret = ft_process_output_redir(data, cmd, tkn);
	}
	return (ret);
}

int	ft_process_input_redir(t_data *data, t_cmd *cmd, t_tkn *tkn,
		t_hdoc *hdoc_node)
{
	char	*filename;
	int		check_ret;

	filename = NULL;
	if (tkn->type == IN_ID)
	{
		filename = tkn->next->arg;
		check_ret = ft_check_redir_ambiguous(data, cmd, &filename);
		if (check_ret == ERROR)
			return (ft_free_str(&filename), ERROR);
		if (check_ret == 1)
			return (ft_free_str(&filename), 2);
	}
	else
	{
		if (hdoc_node)
			filename = ft_filename_hdoc(hdoc_node);
	}
	if (!filename)
		return (ERROR);
	ft_open_and_handle_input(data, cmd, tkn, filename);
	ft_free_str(&filename);
	return (0);
}

int	ft_process_output_redir(t_data *data, t_cmd *cmd, t_tkn *tkn)
{
	char	*filename;
	int		open_flags;
	int		status;

	filename = tkn->next->arg;
	status = ft_check_redir_ambiguous(data, cmd, &filename);
	if (status == ERROR)
		return (ERROR);
	if (status == 1)
		return (2);
	if (tkn->type == OUT_ID)
		open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	else
		open_flags = O_WRONLY | O_APPEND | O_CREAT;
	if (ft_open_output_file(data, cmd, filename, open_flags) == ERROR)
		return (ft_free_str(&filename), ERROR);
	if (ft_another_output(tkn->next))
	{
		close(cmd->fd_out);
		cmd->fd_out = 0;
	}
	return (ft_free_str(&filename), 0);
}

int	ft_check_redir_ambiguous(t_data *data, t_cmd *cmd,
		char **filename_ptr)
{
	int	ret;

	ret = ft_clean_filename(filename_ptr);
	if (ret == ERROR)
		return (ERROR);
	if (ret == 0 && (ft_strchr(*filename_ptr, '*')
			|| ((*filename_ptr)[0] == '$' && (*filename_ptr)[1])))
	{
		cmd->error = 1;
		data->exit_status = 1;
		ft_error_found(NULL, *filename_ptr, 13);
		return (1);
	}
	return (0);
}
