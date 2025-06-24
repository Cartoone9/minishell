/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:27:27 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 19:58:01 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_echo(t_data *data, t_cmd *cmd)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (cmd->args[i] && ft_is_newline(cmd->args[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	data->exit_status = 0;
	return (0);
}

int	ft_is_newline(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] && arg[i] == '-')
	{
		i++;
		while (arg[i] && arg[i] == 'n')
			i++;
		if (i == ft_strlen(arg))
			return (1);
	}
	return (0);
}
