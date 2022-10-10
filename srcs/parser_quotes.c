/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:50:53 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/10 13:51:24 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		}
	}
	if (found)
		return (0);		// unmatched quote, ERROR
	return (1);			// matched quote, OK
}

int	find_matching_quote(char *str, char quote)
{
	int	i;

	i = 1;
	// ft_printf("		---(%c)", quote);
	while (str[i] && str[i] != quote)
	{
		// ft_printf("(%s) ", &str[i]);
		i++;
	}
		// ft_printf("\n");
	return (i);
}

void	strip_quotes(char ***args, int argc)
{
	int	i;
	int	a;
	int	quote1;
	int	quote2;
	int	len;

	a = -1;
	while (++a < argc)
	{
		i = -1;
		len = (int)ft_strlen((*args)[a]);
		// ft_printf("---(%s)len(%d)\n", (*args)[a], len);
		while ((*args)[a][++i])
		{
			if ((*args)[a][i] == '\'' || (*args)[a][i] == '"')
			{
				quote1 = i;
				quote2 = find_matching_quote(&(*args)[a][i], (*args)[a][i]);
				quote2 += quote1;

				// ft_printf("beg (%s)(%d - %d)\n", (*args)[a], quote1, quote2);
				ft_memmove((void *)&(*args)[a][i], (void *)&(*args)[a][i + 1],
					len - quote1);
				// ft_printf("mid (%s)(%d)(%d)\n", (*args)[a], quote1, quote2);

				// if ((*args)[a][quote2 - 1] == '\0')
				// {
				// 	*args[a][quote2 - 2] = '\0';
				// }
				// else
					ft_memmove((void *)&(*args)[a][quote2 - 1],
						(void *)&(*args)[a][quote2], len - quote2);
				// ft_printf("end (%s)(i=%d)\n", (*args)[a], i);

				i = quote2 - 2;
			}
		}
	}
}
