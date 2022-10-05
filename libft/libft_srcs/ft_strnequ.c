/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:45:04 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/27 20:14:25 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (i <= n - 1)
	{
		if (s1[i] != s2[i])
			return (0);
		if (s1[i] == '\0')
			return (1);
		i++;
	}
	return (1);
}
