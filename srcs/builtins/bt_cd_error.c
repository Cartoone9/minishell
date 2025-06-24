/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:19 by *******           #+#    #+#             */
/*   Updated: 2025/04/17 21:55:04 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_cd_error_home_not_set(t_data *data)
{
	data->exit_status = 1;
	return (ft_error_found(NULL, NULL, 5), 1);
}

int	ft_cd_error_home_empty(t_data *data)
{
	data->exit_status = 1;
	return (ft_error_found(NULL, NULL, 5), 1);
}

int	ft_cd_error_strjoin(t_data *data)
{
	data->exit_status = 1;
	return (ft_error("strjoin failed in ft_cd home"), 1);
}

int	ft_cd_error_getcwd(t_data *data)
{
	data->exit_status = 1;
	return (ft_error("getcwd failed in ft_cd"), 1);
}

int	ft_cd_error_chdir_home(t_data *data, char *source)
{
	data->exit_status = 1;
	return (ft_error_found(NULL, source, 8), 1);
}
