/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:52:45 by *******           #+#    #+#             */
/*   Updated: 2025/06/24 13:15:45 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

volatile sig_atomic_t	g_signal;
int						g_stdin_save;

static void	ft_general_command(t_data *data)
{
	if (ft_build_cmd_list(data) == ERROR)
		ft_exit_seq(data, errno);
	if (ft_remove_slash(data) == ERROR)
		ft_exit_seq(data, errno);
	if (ft_convert_first_arg(data) == ERROR)
		ft_exit_seq(data, errno);
	data->exit_status = ft_start_execution(data);
	if (!ft_is_a_child(data))
		data->exit_status = ft_wait(data);
	else
		ft_exit_seq_silent(data, data->exit_status);
}

static void	ft_process_command(t_data *data)
{
	ft_check_exit(data->full_input, data);
	if (*data->full_input)
		add_history(data->full_input);
	if (data->error)
	{
		data->error = 0;
		data->exit_status = 2;
	}
	else if (ft_strncmp(data->full_input, "hclear", 7) == 0)
	{
		rl_clear_history();
		printf("Command history cleared !\n");
	}
	else if ((ft_strncmp(data->full_input, "clear", 6) == 0)
		|| (ft_strncmp(data->full_input, "cl", 3) == 0))
		ft_display_hud();
	else
		ft_general_command(data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ft_full_init_main(ac, av, envp, &data) == ERROR)
		return (1);
	while (1)
	{
		ft_main_signals();
		ft_data_init_one(&data);
		ft_get_input(&data, 0);
		ft_data_init_two(&data);
		if (data.full_input && g_signal == 0)
		{
			ft_process_command(&data);
		}
		ft_free_loop(&data);
	}
	return (errno);
}
