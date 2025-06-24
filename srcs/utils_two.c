/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:27:03 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 02:19:47 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_has_only_digit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && ft_empty_str(&str[i]))
			return (1);
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_init_strr(char ***strr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		(*strr)[i] = NULL;
		i++;
	}
}

void	ft_init_buffer(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < PATH_MAX)
	{
		buffer[i] = 0;
		i++;
	}
}

int	ft_is_separator(char check_char, char c, char c_2)
{
	if (check_char == c || check_char == c_2 || check_char == '\''
		|| check_char == '"' || check_char == '|' || check_char == '<'
		|| check_char == '>' || check_char == '$' || check_char == '*')
	{
		return (1);
	}
	return (0);
}

int	ft_is_separator_nospace(char check_char)
{
	if (check_char == '\'' || check_char == '"'
		|| check_char == '|' || check_char == '<'
		|| check_char == '>' || check_char == '$' || check_char == '*')
	{
		return (1);
	}
	return (0);
}
