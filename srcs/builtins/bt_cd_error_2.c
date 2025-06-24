/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:19 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 18:57:40 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_cd_error_too_many_args(t_data *data)
{
	data->exit_status = 1;
	return (ft_error_min("minishell: cd: too many arguments"), 1);
}

int	ft_cd_error_access_fok(t_data *data, char *arg)
{
	ft_error_found(NULL, arg, 8);
	data->exit_status = 1;
	return (1);
}

int	ft_cd_error_not_directory(t_data *data, char *arg)
{
	ft_error_found(NULL, arg, 10);
	data->exit_status = 1;
	return (1);
}

int	ft_cd_error_access_xok(t_data *data, char *arg)
{
	ft_error_found(NULL, arg, 9);
	data->exit_status = 1;
	return (1);
}
