/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:47:58 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/10 16:45:42 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
			|| str[i] == '\n' || str[i] == '\f' || str[i] == '\v') && str[i])
				i++;
			if (str[i])
				return (i - 1);
		}
	}
	return (0);
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
		// ft_printf("(%d)->", i);
		if (!ft_iswhitespace(str[i]))
		{
			j = i;
			i = find_argument_len(&str[i]);
			array[arg++] = ft_strsub(str, (unsigned int)j, (size_t)i);
			i += j - 1;
		}
		// ft_printf("(%d)\n", i);
	}
	array[argc] = NULL;
	return (array);
}

int	ms_count_arguments(char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		// ft_printf("s(%d)", i);
		if (!ft_iswhitespace(str[i]))
		{
			// ft_printf("	is(%d) ", i);
			while (!ft_iswhitespace(str[i]) && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i += find_matching_quote(&str[i], str[i]);
				i++;
			}
			ret++;
			// ft_printf("	ie(%d) ", i);
			if (str[i] == '\0')
				break ;
		}
		else
		{
			// ft_printf("	es(%d) ", i);
			i += skip_whitespace(&str[i]);
			// ft_printf("	ee(%d) ", i);
		}
		// ft_printf("e(%d)\n", i);
	}
	return (ret);
	// 	      7  10     17		  27='\0'
	// "hello "  "asddsa"  asd asd
}

void	parse_input(char *str, char ***args, t_ms_help *help)
{
	char	*trimmed;
	int		argc;

	argc = count_quotes(str);
	if (argc == 0)
	{
		// error_msg
		return ;
	}
	trimmed = ft_strtrim(str);
	argc = ms_count_arguments(trimmed);
	help->arguments = argc;
	*args = get_arguments(trimmed, argc);
	ft_strdel(&trimmed);
	if (argc > 10)
	{
		ft_printf("Too many arguments\n");
	}
	// convert_env_list(args, argc, help->env, help);

	strip_quotes(args, argc);
}
