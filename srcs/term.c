/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:06:00 by *******           #+#    #+#             */
/*   Updated: 2025/04/10 23:54:24 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_save_stdin(void)
{
	g_stdin_save = dup(STDIN_FILENO);
	if (g_stdin_save == ERROR)
		return (ft_error("dup failed in ft_save_stdin"), ERROR);
	return (0);
}
