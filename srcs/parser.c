/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:47:58 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/22 22:11:37 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_matching_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void	strip_quotes(char ***args, int argc, int a)
{
	int	i;
	int	quote1;
	int	quote2;
	int	len;

	while (++a < argc)
	{
		i = -1;
		len = (int)ft_strlen((*args)[a]);
		while ((*args)[a][++i])
		{
			if ((*args)[a][i] == '\'' || (*args)[a][i] == '"')
			{
				quote1 = i;
				quote2 = find_matching_quote(&(*args)[a][i], (*args)[a][i]);
				quote2 += quote1;
				ft_memmove((void *)&(*args)[a][i], (void *)&(*args)[a][i + 1],
					len - quote1);
				ft_memmove((void *)&(*args)[a][quote2 - 1],
					(void *)&(*args)[a][quote2], len - quote2);
				i = quote2 - 2;
			}
		}
	}
}

int	count_quotes(char *str)
{
	int	i;
	int	found;
	int	quote;

	found = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			found = 1;
			quote = str[i++];
			while (str[i] != quote && str[i])
				i++;
			if (str[i] == quote)
				found = 0;
			if (!str[i])
				break ;
		}
	}
	if (found)
		return (0);
	return (1);
}

int	parse_input(char *str, char ***args, t_ms_help *help)
{
	char	*trimmed;
	int		argc;

	if (!(count_quotes(str)))
	{
		ft_printf("ERROR, unmatched quotes not supported!\n");
		return (0);
	}
	trimmed = ft_strtrim(str);
	argc = minishell_arguments(trimmed);
	if (argc > 1024)
	{
		ft_printf("Too many arguments!\n");
		ft_strdel(&trimmed);
		return (0);
	}
	help->arguments = argc;
	*args = get_arguments(trimmed, argc);
	ft_strdel(&trimmed);
	convert_env_list(args, argc, help->env, help);
	strip_quotes(args, argc, -1);
	return (1);
}
