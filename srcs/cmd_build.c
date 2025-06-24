/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:40:57 by *******           #+#    #+#             */
/*   Updated: 2025/04/16 03:36:26 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_build_cmd_list(t_data *data)
{
	t_tkn	*tkn;
	t_hdoc	*hdoc;
	t_cmd	*cmd;

	if (ft_init_build_vars(data, &cmd, &hdoc, &tkn) == ERROR)
		return (ERROR);
	return (ft_process_token_loop(data, &cmd, tkn, &hdoc));
}

// Initializes cursors and performs initial checks
int	ft_init_build_vars(t_data *data, t_cmd **cmd_ptr, t_hdoc **hdoc_ptr,
		t_tkn **tkn_ptr)
{
	if (!data || !data->tkn_list)
		return (ft_error("missing data/data->tkn_list in init_build_vars"),
			ERROR);
	if (ft_new_cmd_node(data) == ERROR || !data->cmd_list)
		return (ERROR);
	*cmd_ptr = data->cmd_list;
	*hdoc_ptr = NULL;
	if (data->hdoc_list)
		*hdoc_ptr = data->hdoc_list;
	*tkn_ptr = data->tkn_list;
	return (0);
}

int	ft_process_token_loop(t_data *data, t_cmd **cmd_ptr, t_tkn *tkn,
		t_hdoc **hdoc_ptr)
{
	size_t	i;
	int		status;

	i = 0;
	while (tkn)
	{
		if (ft_ensure_cmd_args(*cmd_ptr, tkn, &i) == ERROR)
			return (ERROR);
		status = 0;
		if (tkn->type == ARG_ID || tkn->type == CMD_ID)
			status = ft_process_arg_cmd(*cmd_ptr, tkn, &i);
		else if (tkn->type == PIPE_ID)
			status = ft_process_pipe(data, cmd_ptr, &i);
		else if (tkn->type <= A_OUT_ID)
		{
			status = ft_handle_redir_token(data, *cmd_ptr, &tkn, hdoc_ptr);
			if (status == 2)
				continue ;
		}
		tkn = tkn->next;
	}
	return (0);
}

int	ft_ensure_cmd_args(t_cmd *cmd, t_tkn *current_tkn, size_t *i_ptr)
{
	if (!cmd->args)
	{
		if (ft_allocate_cmd_args(cmd, current_tkn) == ERROR)
			return (ERROR);
		*i_ptr = 0;
	}
	return (0);
}

int	ft_new_cmd_node(t_data *data)
{
	t_cmd	*new_cmd;
	t_cmd	*cursor_cmd;

	if (!data)
		return (ft_error("missing data in new_cmd_node"), ERROR);
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (ft_error("malloc failed in init_cmd_node"), ERROR);
	ft_cmd_node_null(new_cmd);
	if (data && !data->cmd_list)
		data->cmd_list = new_cmd;
	else
	{
		cursor_cmd = data->cmd_list;
		while (cursor_cmd && cursor_cmd->next)
			cursor_cmd = cursor_cmd->next;
		cursor_cmd->next = new_cmd;
	}
	return (0);
}

/*static int	ft_handle_stdin_redir(t_tkn *tkn)*/
/*{*/
/*if (tkn->next && tkn->next->arg && ft_strncmp(tkn->next->arg,*/
/*		"/dev/stdin", 11) == 0)*/
/*	{*/
/*		ft_free_str(&tkn->next->arg);*/
/*		tkn->next->arg = ft_strdup("/dev/null");*/
/*		if (!tkn->next->arg)*/
/*			return (ft_error("strdup failed in handle_stdin_redir"), ERROR);*/
/*	}*/
/*	return (0);*/
/*}*/
