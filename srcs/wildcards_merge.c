/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:19:15 by *******           #+#    #+#             */
/*   Updated: 2025/04/14 01:42:44 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_merge_strr(char ***old_strr, char **new_strr, t_sizet *szt)
{
	char	**merged_strr;
	size_t	last_str_pos;
	size_t	new_len;
	size_t	merged_len;

	if (!old_strr || !(*old_strr) || !new_strr || !szt || szt->strr_len == 0)
		return (ft_error("invalid input to ft_merge_strr"), ERROR);
	last_str_pos = szt->j - 1;
	if (last_str_pos > szt->strr_len)
		return (ft_error("invalid index in ft_merge_strr"), ERROR);
	new_len = ft_strrlen(new_strr);
	if (new_len == 0)
		return (ft_error("empty new_strr in ft_merge_strr"), ERROR);
	merged_len = szt->strr_len + new_len - 1;
	merged_strr = malloc(sizeof(char *) * (merged_len + 1));
	if (!merged_strr)
		return (ft_error("malloc failed in merge_strr"), ERROR);
	if (ft_copy_initial_part(merged_strr, *old_strr, last_str_pos) == ERROR)
		return (free(merged_strr), ft_free_strr(old_strr), ERROR);
	if (ft_copy_new_part(merged_strr, new_strr, last_str_pos, new_len) == ERROR)
		return (ft_free_strr(&merged_strr), ERROR);
	*old_strr = merged_strr;
	szt->strr_len = merged_len;
	szt->j = last_str_pos + new_len;
	return (0);
}

int	ft_copy_initial_part(char **merged_strr, char **old_strr, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		merged_strr[i] = ft_strdup(old_strr[i]);
		if (!merged_strr[i])
			return (ft_error("strdup failed in copy_initial_part"), ERROR);
		i++;
	}
	i = 0;
	while (i <= count)
	{
		ft_free_str(&old_strr[i]);
		i++;
	}
	free(old_strr);
	return (0);
}

int	ft_copy_new_part(char **merged_strr, char **new_strr,
		size_t start_index, size_t new_len)
{
	size_t	j;

	j = 0;
	while (j < new_len)
	{
		merged_strr[start_index + j] = ft_strdup(new_strr[j]);
		if (!merged_strr[start_index + j])
			return (ft_error("strdup failed in copy_new_part"), ERROR);
		j++;
	}
	merged_strr[start_index + j] = NULL;
	return (0);
}
