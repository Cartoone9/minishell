/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_main_signals(void)
{
	rl_catch_signals = 0;
	g_signal = 0;
	ft_signals();
}

void	ft_free_loop(t_data *data)
{
	ft_free_tokens(data->tkn_list);
	ft_free_hdoc(data->hdoc_list);
	ft_free_cmds(data->cmd_list);
	ft_free_str(&data->full_input);
}

int	ft_is_a_child(t_data *data)
{
	t_cmd	*cursor_cmd;

	if (!data || !data->cmd_list)
		return (0);
	cursor_cmd = data->cmd_list;
	while (cursor_cmd && cursor_cmd->next != NULL)
	{
		cursor_cmd = cursor_cmd->next;
	}
	if (cursor_cmd->pid == 0)
		return (1);
	return (0);
}
