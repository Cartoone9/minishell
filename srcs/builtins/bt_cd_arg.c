/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:19 by *******           #+#    #+#             */
/*   Updated: 2025/04/18 02:26:18 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_cd_with_arg(t_data *data, t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	ft_init_buffer(cwd);
	if (ft_strrlen(cmd->args) >= 3)
		return (ft_cd_error_too_many_args(data));
	else
	{
		if (cmd->args[1][0] == '\0')
			return (ft_cd_no_arg(data));
		if (ft_validate_cd_target(data, cmd->args[1]))
			return (ERROR);
		if (getcwd(cwd, sizeof(cwd)) == NULL
			&& ft_cd_with_arg_checkenv(data, cwd) == ERROR)
			return (ERROR);
		if (ft_export_cd(data, "OLDPWD=", cwd) == ERROR)
			return (ERROR);
		if (chdir(cmd->args[1]) == 0)
			return (ft_cd_update_pwd_with_arg(data, cmd->args[1]));
		ft_error_found(NULL, cmd->args[1], 3);
	}
	data->exit_status = 1;
	return (1);
}

int	ft_validate_cd_target(t_data *data, char *target_path)
{
	if (access(target_path, F_OK))
		return (ft_cd_error_access_fok(data, target_path));
	if (!ft_is_a_directory(target_path))
		return (ft_cd_error_not_directory(data, target_path));
	if (access(target_path, X_OK))
		return (ft_cd_error_access_xok(data, target_path));
	return (0);
}

int	ft_cd_with_arg_checkenv(t_data *data, char cwd[PATH_MAX])
{
	char	*temp_cwd;
	size_t	i;

	temp_cwd = ft_getenv(data, "PWD");
	if (!temp_cwd || temp_cwd[0] == '\0')
	{
		ft_free_str(&temp_cwd);
		ft_cd_error_getcwd(data);
		return (ERROR);
	}
	i = 0;
	while (temp_cwd[i])
	{
		cwd[i] = temp_cwd[i];
		i++;
	}
	ft_free_str(&temp_cwd);
	return (0);
}

int	ft_cd_update_pwd_with_arg(t_data *data, char *arg)
{
	char	cwd[PATH_MAX];

	ft_init_buffer(cwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_cd_handle_getcwd_fail(data, arg));
	if (ft_export_cd(data, "PWD=", cwd) == ERROR)
	{
		data->exit_status = 1;
		return (ERROR);
	}
	data->exit_status = 0;
	return (0);
}

int	ft_cd_handle_getcwd_fail(t_data *data, char *arg)
{
	char	*slash_temp;
	char	*pwd_temp;
	char	*env_temp;

	data->exit_status = 1;
	slash_temp = ft_strjoin("/", arg);
	if (!slash_temp)
		return (ft_error("slash_temp join fail in ft_cd"), 1);
	env_temp = ft_getenv(data, "PWD");
	if (!env_temp)
		return (ft_free_str(&slash_temp), ft_error("ft_getenv failed in bt_cd"),
			1);
	pwd_temp = ft_strjoin(env_temp, slash_temp);
	ft_free_str(&env_temp);
	ft_free_str(&slash_temp);
	if (!pwd_temp)
		return (ft_error("pwd_temp join fail in ft_cd"), 1);
	if (ft_export_cd(data, "PWD=", pwd_temp) == ERROR)
		return (ft_free_str(&pwd_temp), ERROR);
	ft_free_str(&pwd_temp);
	return (ft_error_min("minishell: cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: "
			"No such file or directory"), 1);
}
