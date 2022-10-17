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
	{
		update_env("OLDPWD", *pwd, &(help->env));
	}

	ft_memdel((void **)&tmp);
	ft_memdel((void **)pwd);
	*pwd = getcwd(NULL, 0);
	update_env("PWD", *pwd, &(help->env));
}

void	execute_commands(char **args, t_ms_help *help)
{
	char	*buf;
	int		i;

	i = 0;
	buf = getcwd(NULL, 0);
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
	else if (ft_strcmp("unsetenv", args[0]) == 0)
	{
		// print_env_list(help->env, help);
	}
	else if (ft_strcmp("setenv", args[0]) == 0)
	{
		// parse the arg[1];
		// SHELL=randomness  '='count == 1									->

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
	// ft_printf("env_func\t(%s)\n", var);
	// check pos[0] !isnum
	while (var[i] && ((ft_isalnum(var[i])) || var[i] == '_'))
		i++;
	return (ft_strsub((const char *)var, 0, (size_t)i));
}

// get_post_dollar_content(*str, i, ft_strlen(content), post_len);
char	*get_post_dollar_content(char *str, int i, size_t len, size_t post_len)
{
	char	*tmp;

	// ft_printf("POST\ti %d, len %d, post_len %d\n", i, len, post_len);
	// ft_printf("POST\t(%s)\n", &(str[(size_t)i + len]));
	tmp = ft_strsub((const char *)&str[(size_t)i + len + 1], 0, post_len);
	if (!tmp)
		exit(12);
	return (tmp);
}

void	replace_dollar(char **str, char *cont, char **pre_d, int i, char **post)
{
	if (i > 0)
	{
		*str = ft_strncpy(*str, (const char *)*pre_d, (size_t)i);
		*str = ft_strcat(*str, (const char *)cont);
		ft_strdel(pre_d);
	}
	else
		*str = ft_strcpy(*str, (const char *)cont);
	if (*post)
	{
		*str = ft_strcat(*str, (const char *)*post);
		ft_strdel(post);
	}
}

void	update_arg_dollar(int i, char **str, char **env, t_ms_help *help)
{
	char	*tmp;
	char	*content;
	char	*pre_dollar;
	size_t	post_len;
	size_t	new_full_len;
	size_t	env_len;

	tmp = get_full_env_name(&(*str)[i + 1]);
	env_len = ft_strlen(tmp);
	content = get_env(tmp, env, help);
	post_len = ft_strlen(*str) - env_len - (size_t)i - 1;
	ft_strdel(&tmp);
	if (post_len > 0)
		tmp = get_post_dollar_content(*str, i, env_len, post_len);
	if (i > 0)
		pre_dollar = ft_strsub((const char *)(*str), 0, (size_t)i);
	new_full_len = (size_t)i + ft_strlen(content) + post_len;
	ft_strdel(str);
	*str = ft_strnew(new_full_len);
	if (!*str)
		exit(9);
	replace_dollar(str, content, &pre_dollar, i, &tmp);
	ft_strdel(&content);
}

void	update_home(char **str, char **env, t_ms_help *help)
{
	char	*home;
	char	*post_tilde;
	size_t	tot_len;

	tot_len = ft_strlen(*str);
	home = get_env("HOME", env, help);
	// if (ft_strlen(home) == 0)
	// 	exit(13);
	if (tot_len > 1)
	{
		post_tilde = ft_strsub((const char *)*str, 1, tot_len - 1);
		if (post_tilde[0] == '/' || ft_iswhitespace(post_tilde[0]))
		{
			ft_bzero((void *)*str, tot_len);
			ft_strdel(str);
			*str = ft_strjoin((const char *)home, (const char *)post_tilde);
		}
		ft_strdel(&post_tilde);
	}
	else
	{
		ft_bzero((void *)*str, 1);
		ft_strdel(str);
		*str = ft_strdup((const char *)home);
	}
	ft_strdel(&home);
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
				update_arg_dollar(i, &(*args)[a], env, help);
				i = -1;
			}
			else if ((*args)[a][i] == '~' && i == 0)
			{
				update_home(&(*args)[a], env, help);
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

void	test_update_env(char **env, t_ms_help *help)
{
	(void)env;
	print_env_list_orig(help->env);
	update_env("LOGNAME", "newtest", &(help->env), help);
	print_env_list_orig(help->env);
	exit(0);
}

// void	set_env(char **args, t_ms_help *help)
void	test_set_env(char **env, t_ms_help *help)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
	{
		ft_printf("error in test_update_tilde, exiting\n");
		exit(11);
	}
	arr[2] = NULL;
	arr[0] = ft_strdup("NEWTEST=yayyy");
	arr[1] = ft_strdup("TESTING=fun");

	help->arguments = 2;
	print_env_list_orig(env);
	set_env(arr, help);
	print_env_list_orig(env);

	exit(0);
}

void	test_update_tilde(char **env, t_ms_help *help)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 8);
	if (!arr)
	{
		ft_printf("error in test_update_tilde, exiting\n");
		exit(11);
	}
	arr[7] = NULL;
	arr[0] = ft_strdup("~");
	arr[1] = ft_strdup("~/asddas");
	arr[2] = ft_strdup("~repos");
	arr[3] = ft_strdup("asd~");
	arr[4] = ft_strdup("asd/~");
	arr[5] = ft_strdup("asd ~");
	arr[6] = ft_strdup("~ asd");

	help->arguments = 7;
	print_env_list_orig(arr);
	convert_env_list(&arr, 7, env, help);
	// ft_printf("134124142\n");
	print_env_list_orig(arr);

	exit(0);
}


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
	// add_env(str, env, help);
	// add_env("testing", "foo", env, help, 0)
	(void)str;
	ft_printf("\n- - - - - - - - - - - -\n(%d)\n", help->env_size);
	print_env_list(*env, help);
	exit(1);
}

void	test_update_dollar(char **env, t_ms_help *help)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * 9);
	if (!arr)
	{
		ft_printf("error in test_update_dollar, exiting\n");
		exit(11);
	}
	arr[8] = NULL;
	arr[0] = ft_strdup("hello$LOGNAME");
	arr[1] = ft_strdup("hello$LANG.asd");
	arr[2] = ft_strdup("hello$LANGasd");
	arr[3] = ft_strdup("hello$LOGNAM");
	arr[4] = ft_strdup("$LOGNAME.asd");
	arr[5] = ft_strdup("$LOGNAME_asd");
	arr[6] = ft_strdup("\"$SHELL\".random\'$USER\'");
	arr[7] = ft_strdup("hello$LOGNAME.random\"$USER\"$LOGNAME.hello");
	// arr[7] = ft_strdup("hello$LOGNAME.random$USER.$LOGNAM.hello");

	help->arguments = 8;
	print_env_list_orig(arr);
	convert_env_list(&arr, 8, env, help);
	print_env_list_orig(arr);

	// ft_printf("test final\t(%s)\n", arr[0]);
	// update_arg_dollar(5, &arr[0], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[0]);
	// ft_printf("-	-	-	-	-	-	-	\n");

	// ft_printf("test final\t(%s)\n", arr[1]);
	// update_arg_dollar(5, &arr[1], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[1]);
	// ft_printf("-	-	-	-	-	-	-	\n");

	// ft_printf("test final\t(%s)\n", arr[2]);
	// update_arg_dollar(5, &arr[2], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[2]);
	// ft_printf("-	-	-	-	-	-	-	\n");

	// ft_printf("test final\t(%s)\n", arr[3]);
	// update_arg_dollar(5, &arr[3], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[3]);
	// ft_printf("-	-	-	-	-	-	-	\n");

	// ft_printf("test final\t(%s)\n", arr[4]);
	// update_arg_dollar(0, &arr[4], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[4]);
	// ft_printf("-	-	-	-	-	-	-	\n");

	// ft_printf("test final\t(%s)\n", arr[5]);
	// update_arg_dollar(0, &arr[5], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[5]);
	// ft_printf("-	-	-	-	-	-	-	\n");

	// ft_printf("test final\t(%s)\n", arr[6]);
	// update_arg_dollar(0, &arr[6], env, help);
	// ft_printf("test final\t(%s)\n\n", arr[6]);
	// ft_printf("-	-	-	-	-	-	-	\n");

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
