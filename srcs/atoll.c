/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:02:20 by *******           #+#    #+#             */
/*   Updated: 2025/04/11 17:51:50 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_atoll_safe(char *str, long long *ret)
{
	unsigned long long	temp;
	long long			neg;
	long long			last_digit;
	size_t				i;

	if (!str || !ret)
		return (ERROR);
	last_digit = 7;
	temp = 0;
	neg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (ft_error_found(NULL, str, 12), ERROR);
	if (ft_atoll_safe_handle_sign(str, &neg, &last_digit, &i) == ERROR)
		return (ERROR);
	while (str[i] && str[i] == '0')
		i++;
	if (ft_atoll_safe_parse_digits(str, &temp, last_digit, &i) == ERROR)
		return (ft_error_found(NULL, str, 12), ERROR);
	*ret = (long long)(neg * temp);
	return (0);
}

int	ft_atoll_safe_handle_sign(char *str, long long *neg, long long *last_digit,
		size_t *i)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
		{
			*neg = -1;
			*last_digit = 8;
		}
		(*i)++;
		if (!str[*i])
			return (ft_error_found(NULL, str, 12), ERROR);
	}
	return (0);
}

int	ft_atoll_safe_parse_digits(char *str, unsigned long long *temp,
		long long last_digit, size_t *i)
{
	long long	digit;

	while (str[*i])
	{
		if (!ft_isdigit(str[*i]) && !ft_empty_str(&str[*i]))
			return (ERROR);
		else if (ft_empty_str(&str[*i]))
			break ;
		digit = str[*i] - '0';
		if (*temp > (unsigned long long)LLONG_MAX / 10
			|| (*temp == (unsigned long long)LLONG_MAX / 10
				&& digit > last_digit))
			return (ERROR);
		*temp = *temp * 10 + digit;
		(*i)++;
	}
	return (0);
}
