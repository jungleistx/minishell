/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:16:42 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/07 17:12:10 by rvuorenl         ###   ########.fr       */
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

	// --	TODO
// char	*get_home_env()
// char	*get_oldpwd_env()
// char	*get_pwd()
// void	update_env(char *env, char *new)

int	get_env_list_size(char **env)
{
	int	total;

	total = 0;
	while (env[total])
		total++;
	return (total);
}


void	copy_env_list(char **env)
{
	char	**env_copy;
	int		env_size;

	env_size = (get_env_list_size(env);
	env_copy = (char **)malloc(sizeof(char *) * env_size);
	if (!env_copy)
		exit(4);

	env_copy[env_size] = NULL;
	while (env_size >= 0)
	{
		env_copy[env_size] = ft_strdup(env[env_size]);
		env_size--;
	}
}

void	change_dir(char **pwd, char *dest)
{
	// multiple input
		// 22-10-07, 16:42 ~/hive/repos/minishell -> cd asdasd ~
		// cd: string not in pwd: asdasd
		// 22-10-07, 16:42 ~/hive/repos/minishell -> cd ~ asdasd
		// cd: no such file or directory: asdasd/hive/repos/minishell
	char	*tmp;

	if (!dest)
		tmp = get_home_env();
	else if (ft_strcmp("-", dest) == 0)
		tmp = get_old_pwd();
	else
		tmp = ft_strdup(dest);

	if (chdir(tmp) == -1)
	{
		ft_printf("cd: no such file or directory: %s\n", tmp);
		ft_memdel((void **)&tmp);
		return ;
	}
	else
		update_env("OLDPWD", *pwd);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)pwd);
	*pwd = getcwd(NULL, 0);
	update_env("PWD", *pwd);
}

void	execute_commands(char **args)
{
	char *buf;

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
	else if (ft_strcmp("pwd", args[0]) == 0)
	{
		buf = getcwd(NULL, 0);
		ft_printf("%s\n", buf);
	}
	else if (ft_strcmp("cd", args[0]) == 0)
	{
		buf = getcwd(NULL, 0);
		change_dir(&buf, args[1]);
	}
	ft_memdel((void **)&buf);
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
			i += j - 1;
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

				i = quote2 - 2;
			}
		}
	}
}

// void	check_dollar_tilde(char ***args, int argc)
// {
// 	int	a;
// 	int	i;
// 	int	len;

// 	a = -1;
// 	while (++a < argc)
// 	{
// 		len = (int)ft_strlen((*args)[a]);
// 		i = -1;
// 		while ((*args)[a][++i])
// 		{
// 			if ((*args)[a][i] == '$')
// 			{
// 				if
// 			}
// 			else if ((*args)[a][i] == '~' && i == 0)
// 			{

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
	ft_strdel(&trimmed);
	if (argc > 10)
	{
		ft_printf("Too many arguments\n");
	}
	// check_dollar_tilde(args, argc);

	strip_quotes(args, argc);

	// test print
	// int a = 0;
	// ft_printf("\t\tOriginal: (%s)(%d)\n", str, argc);
	// while (a < argc)
	// {
	// 	ft_printf("(%d)(%s)\n", a, (*args)[a]);
	// 	a++;
	// }
	// ft_printf("(%d)(%s)\n", a, (*args)[a]);
	//

}

char	*get_input(void)
{
	char	*str;

	if (get_next_line(0, &str) != -1)
		return (str);
	return (NULL);
}

void	reset_help(t_ms_help *help)
// void	reset_help(t_ms_help *help, char **commands)
{
	help->found = 0;
	// commands = {"cd\0", "echo\0", "pwd\0", "exit\0", "setenv\0",
	// "ls\0"  };
}

int	main(void)
{
	char		*str;
	char		**args;
	t_ms_help	help;
	// char		*commands[];		// [?]

	reset_help(&help);
	// reset_help(&help, &commands);

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
