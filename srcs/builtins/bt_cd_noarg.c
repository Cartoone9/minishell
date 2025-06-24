/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_noarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:19 by *******           #+#    #+#             */
/*   Updated: 2025/04/17 21:59:23 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_cd_no_arg(t_data *data)
{
	char	*home;
	char	*temp;
	char	cwd[PATH_MAX];

	ft_init_buffer(cwd);
	home = ft_getenv(data, "HOME");
	if (!home)
		return (ft_cd_error_home_not_set(data), ERROR);
	if (home[0] == '\0')
		return (ft_cd_error_home_empty(data), ft_free_str(&home), ERROR);
	temp = ft_strjoin("/", home);
	if (!temp)
		return (ft_cd_error_strjoin(data), ft_free_str(&home), ERROR);
	ft_free_str(&home);
	home = temp;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_cd_error_getcwd(data), ft_free_str(&home), ERROR);
	if (ft_export_cd(data, "OLDPWD=", cwd) == ERROR)
		return (ft_free_str(&home), ERROR);
	if (chdir(home) != 0)
		return (ft_cd_error_chdir_home(data, home + 1),
			ft_free_str(&home), ERROR);
	ft_free_str(&home);
	return (ft_cd_update_pwd(data));
}

int	ft_cd_update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	ft_init_buffer(cwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		data->exit_status = 1;
		return (ft_error("getcwd failed in ft_cd"), 1);
	}
	if (ft_export_cd(data, "PWD=", cwd) == ERROR)
	{
		data->exit_status = 1;
		return (ERROR);
	}
	data->exit_status = 0;
	return (0);
}
