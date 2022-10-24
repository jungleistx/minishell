/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:56:10 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/24 13:28:42 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_input(void)
{
	char	*str;

	if (get_next_line(0, &str) != -1)
	{
		if (validate_whitespace(str))
			return (str);
		ft_strdel(&str);
	}
	return (NULL);
}

int	skip_whitespace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\n' || str[i] == '\f' || str[i] == '\v')
		{
			i++;
			while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
					|| str[i] == '\n' || str[i] == '\f'
					|| str[i] == '\v') && str[i])
				i++;
			if (str[i])
				return (i - 1);
		}
	}
	return (0);
}

int	minishell_arguments(char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		if (!ft_iswhitespace(str[i]))
		{
			while (!ft_iswhitespace(str[i]) && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i += find_matching_quote(&str[i], str[i]);
				i++;
			}
			ret++;
			if (str[i] == '\0')
				break ;
		}
		else
			i += skip_whitespace(&str[i]);
	}
	return (ret);
}

int	find_argument_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(ft_iswhitespace(str[i])))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_matching_quote(&str[i], str[i]);
		i++;
	}
	return (i);
}

char	**get_arguments(char *str, int argc)
{
	int		i;
	int		j;
	int		arg;
	char	**array;

	array = (char **) malloc(sizeof(char *) * (argc + 1));
	if (!array)
		exit(3);
	i = -1;
	arg = 0;
	while (str[++i])
	{
		if (!ft_iswhitespace(str[i]))
		{
			j = i;
			i = find_argument_len(&str[i]);
			array[arg++] = ft_strsub(str, (unsigned int)j, (size_t)i);
			i += j - 1;
		}
	}
	array[argc] = NULL;
	return (array);
}
