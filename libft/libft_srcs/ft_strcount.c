/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:04 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/17 14:09:42 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcount(char *str, char target)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while (str[++i])
	{
		if (str[i] == target)
			found++;
	}
	return (found);
}
