/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_doublearray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:22:31 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/28 22:58:05 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_doublearray(char ***array)
{
	int	i;

	i = -1;
	if (*array)
	{
		while ((*array)[++i])
			ft_strdel(&(*array)[i]);
		free((*array)[i]);
		free(*array);
		*array = NULL;
	}
}
