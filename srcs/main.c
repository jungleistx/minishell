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
		tmp = get_env("HOME", help->env, help);
	else if (ft_strcmp("-", dest) == 0)
		tmp = get_env("OLDPWD", help->env, help);
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
		while (args[++i])
			ft_printf("%s ", args[i]);
		ft_printf("\n");
	}
	else if (ft_strcmp("pwd", args[0]) == 0)
	{
		ft_printf("%s\n", buf);
	}
	else if (ft_strcmp("cd", args[0]) == 0)
	{
		// buf = getcwd(NULL, 0);
		change_dir(&buf, args[1], help);
	}
	else if (ft_strcmp("env", args[0]) == 0)
	{
		print_env_list(help->env, help);
	}
	else if (ft_strcmp("setenv", args[0]) == 0)
	{
		// parse the arg[1];
		// SHELL=randomness  '='count == 1

		update_env("SHELL", "randomness", &(help->env));
	}
	// else
	// {
		// /usr/bin/arg[0];
	// }
	ft_memdel((void **)&buf);
}

char	*get_env_name(char *var)
{
	int	i;

	i = 0;
	ft_printf("env_full\t(%s)\n", var);
	while (var[i] && ((ft_isalnum(var[i])) || var[i] == '_'))
	{
		i++;
	}
	return (ft_strsub((const char *)var, 0, (size_t)i));
}

/*
if 0, get name, if !NULL, sub, if len < str, append rest
*/

// *args[a] = update_arg_dollar(i, &(*args)[a], env, help)
void	update_arg_dollar(int i, char **str, char **env, t_ms_help *help)
{
	char	*tmp;
	char	*content;
	char	*pre_dollar;
	size_t	orig_len;
	size_t	content_len;
	size_t	env_len;
	size_t	post_env_len;

	// ft_printf("updatestr \t(%s)\n", *str);
	tmp = get_env_name(&(*str)[i + 1]);
	// ft_printf("env_name\t(%s)\n", tmp);
	content = get_env(tmp, env, help);
	// ft_printf("content\t\t(%s)\n", content);
	/*	mallocs:
	tmp, content
	*/
// env_full        (LOGNAME)
// env_name        (LOGNAME)
// content         (rvuorenl)
// predoll         (hello)
// test final      (hello$LOGNAME)

	orig_len = ft_strlen(*str);
	content_len = ft_strlen(content);
	env_len = ft_strlen(tmp);
	post_env_len = ft_strlen(tmp);
// env_full        (LOGNAME)
// len str         13 (hello$LOGNAME)
// i               5
// len tmp         7 (LOGNAME)
// len cont        8 (rvuorenl)
// predoll         (hello)
// test final      (hello$LOGNAME)

	// ft_printf("len str\t\t%d (%s)\n", ft_strlen(*str), *str);
	// ft_printf("i\t\t%d\n",i);
	// ft_printf("len tmp\t\t%d (%s)\n", ft_strlen(tmp), tmp);
	// ft_printf("len content\t%d (%s)\n", ft_strlen(content), content);

	if (i > 0)
	{
		if (content)
		{
			pre_dollar = ft_strsub((const char *)(*str), 0, (size_t)i);
			ft_printf("predoll\t\t(%s)\n", pre_dollar);
			// ft_strcat(pre_dollar, content);
		}
		else
		{

		}
	}
	else
	{
		// if ()
	}
	// char	*tmp;

	// // tmp = get_env(&(*str)[i], env, help);
	// tmp = get_env(&(*str)[i + 1], env, help);
	// ft_printf("tmp = (%s)(%d)\n", tmp, i);
	// ft_printf("str[i]\t(%s)\n", &(*str)[i]);
	// ft_printf("str\t(%s)\n", *str);
	// if (i > 0)
	// {
	// 	if (tmp == NULL)
	// 	{
	// 		ft_strdel(&tmp);
	// 		*env = (char *)malloc(sizeof(char) * (i + 1));	// check amount
	// 		if (!(*env))
	// 			exit(7);
	// 		tmp = ft_strsub((const char *)str, 0, (size_t)i);
	// 		ft_strdel(str);
	// 		ft_strdup((const char *)tmp);
	// 		ft_strdel(&tmp);
	// 		return ;
	// 	}
	// 	/*
	// 	// if (ft_strchr(name, '/'))
	// 		//
	// 		num != first
	// 	while  (ft_isalpha(str[i]) || str[i] == '_') && str[i])
	// 	*/
	// 	ft_strdel(str);
	// }
	// else
	// {
	// 	ft_strdel(str);
	// 	*str = ft_strdup(tmp);
	// }
}

void	convert_env_list(char ***args, int argc, char **env, t_ms_help *help)
{
	int	a;
	int	i;
	int	len;

	a = -1;
	(void)help;
	(void)env;
	while (++a < argc)
	{
		len = (int)ft_strlen((*args)[a]);
		i = -1;
		while ((*args)[a][++i])
		{
			if ((*args)[a][i] == '$')
			{
				// $HOMEabc
				// *args[a] = update_arg_dollar(i, &(*args)[a], env, help)

				// char *tmp = get_env("HOME", help.env, &help);
				// ft_printf("\n- - - - - -\n%s\n- - - - - - -\n", tmp);
				// ft_strdel(&tmp);

			}
			else if ((*args)[a][i] == '~' && i == 0)
			{

			}
		}
	}
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
	help->env_size = 0;

}

// int main(int argc, char **agrv, char **env)
int	main(void)
{
	char		*str;
	char		**args;
	t_ms_help	help;
	extern char **environ;

	reset_help(&help);
	help.env = copy_env_list(environ, &help);

	// test_update_dollar(help.env, &help);
	// test_add_env(&(help.env), &help);

	while (1)
	{
		args = NULL;
		ft_printf("$> ");
		str = get_input();
		if (str && (str[0] != 0))
		{
			if (parse_input(str, &args, &help))
				execute_commands(args, &help);
		}
		ft_strdel(&str);
		ft_free_doublearray(&args);
	}
	ft_free_doublearray(&(help.env));
	return (0);
}


//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*


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

void	test_add_env(char ***env, t_ms_help *help)
{
// void	add_env(char *var, char ***env, t_ms_help *help)
	char *str = "testing=foo";

	print_env_list(*env, help);
	ft_printf("(%d)", help->env_size);
	add_env(str, env, help);
	ft_printf("\n- - - - - - - - - - - -\n(%d)\n", help->env_size);
	print_env_list(*env, help);
	exit(1);
}

void	test_update_dollar(char **env, t_ms_help *help)
{
	// char *arr[2] =  {"hello$LOGNAME", NULL};
	// char *arr2[2] = {"hella$LOGNAMEH", NULL};
	char **arr;
	// char **arr2;

	arr = (char **)malloc(sizeof(char *) * 5);
	arr[4] = NULL;
	arr[0] = ft_strdup("hello$LOGNAME");
	arr[1] = ft_strdup("hello$LOGNAME.asd");
	arr[2] = ft_strdup("hello$LOGNAMEasd");
	arr[3] = ft_strdup("hello$LOGNAM");

	// update_arg_dollar(2, &arr[0], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[0]);
	update_arg_dollar(5, &arr[0], env, help);
	ft_printf("test final\t(%s)\n\n", arr[0]);
	// update_arg_dollar(6, &arr[0], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[0]);
	// update_arg_dollar(7, &arr[0], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[0]);

	// update_arg_dollar(2, &arr[1], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[1]);
	// update_arg_dollar(5, &arr[1], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[1]);
	// update_arg_dollar(6, &arr[1], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[1]);
	// update_arg_dollar(7, &arr[1], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[1]);

	// update_arg_dollar(2, &arr[2], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[2]);
	// update_arg_dollar(5, &arr[2], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[2]);
	// update_arg_dollar(6, &arr[2], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[2]);
	// update_arg_dollar(7, &arr[2], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[2]);

	// update_arg_dollar(2, &arr[3], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[3]);
	// update_arg_dollar(5, &arr[3], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[3]);
	// update_arg_dollar(6, &arr[3], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[3]);
	// update_arg_dollar(7, &arr[3], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[3]);

	exit(0);
}

void	print_env_list_orig(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%d: %s\n",i, env[i]);
		i++;
	}
	ft_printf("------\n");
}
