/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:16:42 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/05 13:28:18 by rvuorenl         ###   ########.fr       */
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

void	execute_commands(char **args)
{
	if (ft_strcmp("exit", args[0]) == 0)
	{
		ft_printf("BYE!\n");
		exit(10);
	}
	else if (ft_strcmp("echo", args[0]) == 0)
	{
		int i = 0;
		while (args[++i])
			ft_printf("%s ", args[i]);
		ft_printf("\n");
	}
}



// char	*trim_mid(char *str)
// {
// 	char	*trimmed;
// 	trimmed = NULL;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	len = 0;

// 	(void)str;
// 	return (trimmed);
// }

// char	**trim_input(char *str)
// {
// 	char	*trim_end;
// 	// char	*trim_mid;

// 	trim_end = ft_strtrim(str);
// 	// trim_mid = trim_mid(trim_end);

// 	// ft_strdel(&trim_mid);


// 	//
// 	return (NULL);
// }

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
/*
count until match
count_until_whitespace
	save to array[i] -> malloc, strncpy
*/

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
			i += j;
		}
		// ft_printf("(%d)\n", i);
	}
	array[argc] = NULL;
	return (array);
	//    012 456 891 11='\0'
	//    asd dqe sad
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

				i = quote2 - 2; // ?
			}
		}
	}
}

// void	check_dollar_tilde(char ***args, int argc)
// {
// 	int	a;
// 	int	i;

// 	a = -1;
// 	while (++a < argc)
// 	{
// 		i = -1;
// 		while ((*args)[a][++i])
// 		{
// 			if ((*args)[a][i] == '$')
// 			{
// 				if
// 			}
// 		}
// 	}
// }

void	parse_input(char *str, char ***args)
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

	*args = get_arguments(trimmed, argc);

	// check_dollar_tilde(args, argc);

	strip_quotes(args, argc);
	int a = 0;
	ft_printf("		PARSER\n");
	ft_printf("Orig: (%s)(%d)\n", str, argc);
	while (a < argc)
	{
		ft_printf("(%d)(%s)\n", a, (*args)[a]);
		a++;
	}
	ft_printf("(%d)(%s)\n", a, (*args)[a]);
	/*
	// count quotes % 2 == 0	(except \")
	// ft_strtrim input +
	// in the middle
//EDGE
	// echo    "asd     'asd  s"  xx' + NULL
	// echo    "asd     asd  s"     "asdads" + NULL
	// 0 echo
	// 1 asd   asd s
	// 2 asdasd
	// 3 $HOME$KHSDA$SHELL

	0	ls
	1 - l

	// trim the first and last ' || "
	// check $ && ~ && convert to proper output
	*/

	// *args = ft_strsplit(str, 32);
	// if (!*args)
	// 	exit(2);
}

char	*get_input(void)
{
	char	*str;

	if (get_next_line(0, &str) != -1)
		return (str);
	return (NULL);
}

void	reset_help(t_ms_help *help)
{
	help->found = 0;
}

int	main(void)
{
	char		*str;
	char		**args;
	t_ms_help	help;

	reset_help(&help);

	while (1)
	{
		args = NULL;
		ft_printf("$> ");
		str = get_input();
		if (str && (str[0] != 0))
		{
			parse_input(str, &args);
			execute_commands(args);
		}
		ft_strdel(&str);
		ft_free_doublearray(&args);
	}
	return (0);
}


// //	v1, doesnt count the ("word"word2) as 1 argument
// int	count_arguments(char *str)
// {
// 	int	args;
// 	int	i;
// 	int	quote;

// 	i = -1;
// 	args = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] != '\t' && str[i] != ' ')
// 		{
// 			if (str[i] == '\'' || str[i] == '\"')
// 			{
// 				quote = str[i++];
// 				while (str[i] != quote)
// 					i++;
// 			}
// 			else
// 			{
// 				while (str[i] != '\t' && str[i] != ' ' && str[i] && str[i] != '\'' && str[i] != '\"')
// 					i++;
// 			}
// 			args++;
// 			if (!str[i])
// 				break;
// 		}
// 		else
// 		{
// 			// while (str[i] == '\t' || str[i] == ' ')
// 			while (ft_iswhitespace(str[i]))
// 				i++;
// 			i--;
// 		}
// 	}
// 	return (args);
// }

//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*

// void test_args(void)
// {
// 	char *str;

// 	while (get_next_line(0, &str) != -1)
// 	{
// 		if (ft_strcmp("exit", str) == 0)
// 		{
// 			ft_printf("BYE!\n");
// 			exit(10);
// 		}
// 		ft_printf("(%s) = %d\n", str, count_arguments(str));
// 		free(str);
// 	}
// }
void test_ms_args(void)
{
	char *str;

	while (get_next_line(0, &str) != -1)
	{
		if (ft_strcmp("exit", str) == 0)
		{
			ft_printf("BYE!\n");
			exit(10);
		}
		ft_printf("(%s) = %d\n", str, ms_count_arguments(str));
		free(str);
	}
}

void test_quotes(void)
{
	char *str;

	while (get_next_line(0, &str) != -1)
	{
		if (ft_strcmp("exit", str) == 0)
		{
			ft_printf("BYE!\n");
			exit(10);
		}
		ft_printf("(%s) = %d\n", str, count_quotes(str));
	// return (0);			// unmatched quote, ERROR
	// return (1);			// matched quote, OK
		free(str);
	}
}

// //main for quotes
// int main(void)
// {
// 	// test_quotes();
// 	// test_args();
// 	// test_ms_args();
// }
