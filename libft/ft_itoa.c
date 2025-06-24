/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:14:51 by *******           #+#    #+#             */
/*   Updated: 2025/03/05 20:45:03 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

static void		ft_rec_fill(size_t i, char *ret, long n_ln);
static size_t	ft_intlen(int n);

char	*ft_itoa(int n)
{
	size_t	length;
	size_t	i;
	long	n_ln;
	char	*ret;

	length = ft_intlen(n);
	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return (NULL);
	ret[length] = '\0';
	i = 0;
	if (n == 0)
	{
		ret[i] = '0';
		return (ret);
	}
	n_ln = (long)n;
	if (n_ln < 0)
	{
		ret[i] = '-';
		i++;
		n_ln = -(n_ln);
	}
	ft_rec_fill((length - 1), ret, n_ln);
	return (ret);
}

static void	ft_rec_fill(size_t length, char *ret, long n_ln)
{
	if (n_ln >= 10 && length > 0)
	{
		ft_rec_fill((length - 1), ret, n_ln / 10);
	}
	ret[length] = (n_ln % 10) + 48;
}

static size_t	ft_intlen(int n)
{
	size_t	sum;
	long	n_ln;

	sum = 0;
	n_ln = (long)n;
	if (n_ln == 0)
		return (1);
	if (n_ln < 0)
	{
		n_ln = -(n_ln);
		sum++;
	}
	while (n_ln > 0)
	{
		n_ln /= 10;
		sum++;
	}
	return (sum);
}
