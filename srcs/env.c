/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:33:29 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/12 11:31:47 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_list_size(char **env)
{
	int	total;

	total = 0;
	while (env[total])
		total++;
	return (total);
}

char	**copy_env_list(char **env, t_ms_help *help)
{
	char	**env_copy;
	int		env_size;

	env_size = get_env_list_size(env);
	help->env_size = env_size;
	env_copy = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!env_copy)
		exit(4);

	// ft_printf("(env_size %d)\n", env_size);
	env_copy[env_size--] = NULL;
	while (env_size >= 0)
	{
		env_copy[env_size] = ft_strdup(env[env_size]);
		// ft_printf("(%s)\n(%s)\n\n", env[env_size], env_copy[env_size]);
		env_size--;
	}
	return (env_copy);
}

void	print_env_list(char **env, t_ms_help *help)
{
	int	i;

	i = 0;
	while (i < help->env_size && env[i])
		ft_printf("%s\n", env[i++]);
}

size_t	get_longest_env_len(char *name, char *env)
{
	size_t	len;
	size_t	name_len;

	len = 0;
	while (env[len] != '=' && env[len])
		len++;
	name_len = ft_strlen((const char *)name);
	if (name_len > len)
		len = name_len;
	return (len);
}

char	*get_env(char *name, char **env, t_ms_help *help)
{
	int		i;
	char	*tmp;
	size_t	env_len;

	i = 0;
	while (i < help->env_size)
	{
		env_len = get_longest_env_len(name, env[i]);
		if (ft_strncmp(env[i], name, env_len) == 0)
		{
			tmp = ft_strchr(env[i], 61);
			if (tmp[1])
				return (ft_strdup(&tmp[1]));
			return (ft_strdup(tmp));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	build_env(char *name, char *cont, char **dest, size_t size)
{
	*dest = ft_strnew(size);
	*dest = ft_strcpy(*dest, (const char *)name);
	ft_strcat(*dest, "=");
	ft_strcat(*dest, cont);
}

void	update_env(char *name, char *cont, char ***env, t_ms_help *h)
{
	int		a;
	size_t	update_len;
	size_t	env_len;
	int		found;

	found = 0;
	update_len = ft_strlen(name) + ft_strlen(cont) + 1;
	a = -1;
	while ((*env)[++a])
	{
		env_len = get_longest_env_len(name, (*env)[a]);
		if (ft_strncmp((*env)[a], name, env_len) == 0)
		{
			found = 1;
			ft_strdel(&(*env)[a]);
			build_env(name, cont, &(*env)[a], update_len);
			break ;
		}
	}
	if (found == 0)
		add_env(name, cont, env, h, update_len);
}

void	add_env(char *name, char *cont, char ***env, t_ms_help *h, size_t size)
{
	char	**new_env;
	int		arr_size;
	char	*var;

	build_env(name, cont, &var, size);
	h->env_size++;
	arr_size = h->env_size;
	new_env = (char **)malloc(sizeof(char *) * (arr_size + 1));
	if (!new_env)
		exit(6);
	new_env[arr_size--] = NULL;
	new_env[arr_size] = ft_strdup(var);
	while (--arr_size >= 0)
	{
		new_env[arr_size] = ft_strdup((*env)[arr_size]);
	}
	ft_free_doublearray(env);
	ft_strdel(&var);
	*env = new_env;
}

void	copy_env_list_unset(char ***new, char ***env, char *name)
{
	int		i;
	int		j;
	size_t	len;

	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		len = get_longest_env_len(name, (*env)[i]);
		if (ft_strncmp((const char *)(*env)[i], name, len) == 0)
			continue ;
		(*new)[j] = ft_strdup((*env)[i]);
		if (!(*new)[j++])
			exit(16);
	}
	(*new)[j] = NULL;
}

void	unset_env(char ***env, char *name, t_ms_help *help)
{
	char	*tmp;
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp = get_env(name, *env, help);
	if (ft_strlen(tmp) == 0)
	{
		ft_strdel(&tmp);
		return ;
	}
	new = (char **)malloc(sizeof(char *) * help->env_size);
	if (!new)
		exit(15);
	copy_env_list_unset(&new, env, name);
	help->env_size--;
	ft_free_doublearray(env);
	*env = new;
}

void	loop_unset_env(char ***env, char **args, t_ms_help *help)
{
	int	i;

	i = 0;
	while (++i < help->arguments)
		unset_env(env, args[i], help);
}
