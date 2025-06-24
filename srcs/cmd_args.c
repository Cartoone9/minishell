/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:40:57 by *******           #+#    #+#             */
/*   Updated: 2025/04/15 17:18:21 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

// Processes ARG_ID and CMD_ID tokens, adding them to cmd->args
// Special case for ls cmds to add --color
int	ft_process_arg_cmd(t_cmd *cmd, t_tkn *tkn, size_t *i_ptr)
{
	if (cmd->error != 0)
		return (0);
	cmd->args[*i_ptr] = ft_strdup(tkn->arg);
	if (!cmd->args[*i_ptr])
		return (ERROR);
	(*i_ptr)++;
	if (*i_ptr == 1 && ft_strncmp(tkn->arg, "ls", 3) == 0)
	{
		cmd->args[*i_ptr] = ft_strdup("--color");
		if (!cmd->args[*i_ptr])
			return (ERROR);
		(*i_ptr)++;
	}
	return (0);
}

// Processes PIPE_ID tokens, creating a new command node.
int	ft_process_pipe(t_data *data, t_cmd **cmd_ptr, size_t *i_ptr)
{
	if (ft_new_cmd_node(data) == ERROR)
		return (ERROR);
	*cmd_ptr = (*cmd_ptr)->next;
	*i_ptr = 0;
	return (0);
}

// Allocates and initializes the args array for a command
int	ft_allocate_cmd_args(t_cmd *cmd, t_tkn *tkn)
{
	size_t	args_size;
	size_t	j;

	args_size = ft_args_size(tkn);
	if (args_size == 0)
		return (ft_error("args size is 0 in alloc_cmd_args"), ERROR);
	cmd->args = malloc(sizeof(char *) * (args_size + 1));
	if (!cmd->args)
		return (ft_error("malloc failed in loop alloc_cmd_args"), ERROR);
	j = 0;
	while (j < args_size + 1)
	{
		cmd->args[j] = NULL;
		j++;
	}
	return (0);
}

size_t	ft_args_size(t_tkn *cursor_tkn)
{
	size_t	ret;

	ret = 0;
	if (!cursor_tkn)
		return (0);
	if (ft_strncmp(cursor_tkn->arg, "ls", 3) == 0)
		ret++;
	while (cursor_tkn)
	{
		ret++;
		if (cursor_tkn->type == PIPE_ID)
			break ;
		cursor_tkn = cursor_tkn->next;
	}
	return (ret);
}

void	ft_cmd_node_null(t_cmd *new_cmd)
{
	new_cmd->args = NULL;
	new_cmd->path = NULL;
	new_cmd->pid = 0;
	new_cmd->fd_in = 0;
	new_cmd->fd_out = 0;
	new_cmd->pipe[0] = -1;
	new_cmd->pipe[1] = -1;
	new_cmd->error = 0;
	new_cmd->next = NULL;
}
