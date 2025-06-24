/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_seq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:20 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 17:54:31 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_exit_seq(t_data *data, int exit_code)
{
	rl_clear_history();
	if (data)
	{
		if (data->env)
			ft_free_strr(&data->env);
		if (data->path)
			ft_free_strr(&data->path);
		if (data->tkn_list)
			ft_free_tokens(data->tkn_list);
		if (data->hdoc_list)
			ft_free_hdoc(data->hdoc_list);
		if (data->cmd_list)
			ft_free_cmds(data->cmd_list);
		if (data->input)
			ft_free_str(&data->input);
		if (data->full_input)
			ft_free_str(&data->full_input);
	}
	printf(RED "\n\n\n                                           B"
		ORANGE "y" YELLOW "e" GREEN " b" TEAL "y" BLUE "e"
		PURPLE " !" RESET "\n\n\n");
	close(g_stdin_save);
	exit(exit_code);
}

void	ft_exit_seq_silent(t_data *data, int exit_code)
{
	rl_clear_history();
	if (data)
	{
		if (data->env)
			ft_free_strr(&data->env);
		if (data->path)
			ft_free_strr(&data->path);
		if (data->tkn_list)
			ft_free_tokens(data->tkn_list);
		if (data->hdoc_list)
			ft_free_hdoc(data->hdoc_list);
		if (data->cmd_list)
			ft_free_cmds(data->cmd_list);
		if (data->prompt)
			ft_free_str(&data->prompt);
		if (data->input)
			ft_free_str(&data->input);
		if (data->full_input)
			ft_free_str(&data->full_input);
	}
	if (exit_code == -1)
		exit(0);
	close(g_stdin_save);
	exit(exit_code);
}
