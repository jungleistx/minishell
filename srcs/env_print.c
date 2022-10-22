/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:18:46 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/21 23:19:52 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_list(char **env, t_ms_help *help)
{
	int	i;

	i = 0;
	while (i < help->env_size && env[i])
		ft_printf("%s\n", env[i++]);
}
