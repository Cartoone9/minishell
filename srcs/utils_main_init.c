/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_full_init_main(int ac, char **av, char **envp, t_data *data)
{
	if (!isatty(STDIN_FILENO) || ft_is_a_pipe(STDIN_FILENO)
		|| ft_is_a_pipe(STDOUT_FILENO) || ft_is_a_file(STDIN_FILENO)
		|| ft_is_a_file(STDOUT_FILENO))
		return (ft_error_min("minishell:"
				" cannot run in a pipe or with a redirection"),
			ERROR);
	(void)av;
	if (ac > 1)
		return (ft_error_min("minishell: too many arguments"), ERROR);
	if (ft_save_stdin() == ERROR)
		return (ERROR);
	ft_data_init_zero(data);
	if (ft_init_envcpy(envp, data) == ERROR || !data->env)
		return (ft_error("env copy failed"), ERROR);
	if (ft_build_path(data) == ERROR)
		return (ft_error("build_path failed"), ERROR);
	ft_display_hud();
	return (0);
}

void	ft_data_init_zero(t_data *data)
{
	data->env = NULL;
	data->path = NULL;
	data->exit_status = 0;
	data->envless = 0;
}

void	ft_data_init_one(t_data *data)
{
	data->error = 0;
	data->tkn_list = NULL;
	data->hdoc_list = NULL;
	data->cmd_list = NULL;
	data->full_input = NULL;
}

void	ft_data_init_two(t_data *data)
{
	data->input = NULL;
	data->prompt = NULL;
}
