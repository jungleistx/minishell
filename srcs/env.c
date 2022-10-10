/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:33:29 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/10 19:08:24 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_list_size(char **env)
{
	int	total;

	total = 0;
	while (env[total])
		total++;
	ft_printf("total = %d\n", total);	//
	return (total);
}

char	**copy_env_list(char **env, t_ms_help *help)
{
	char	**env_copy;
	int		env_size;

	// ft_printf("a\n");
	env_size = get_env_list_size(env);
	help->env_size = env_size;
	env_copy = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!env_copy)
		exit(4);

	// ft_printf("(env_size %d)\n", env_size);
	env_copy[env_size--] = NULL;
	while (env_size >= 0)
	{
		// ft_printf("%d\n", env_size);
		env_copy[env_size] = ft_strdup(env[env_size]);
		// ft_printf("(%s)\n(%s)\n\n", env[env_size], env_copy[env_size]);
		env_size--;
		// ft_printf("(%d) -> ", env_size);
	}
	// ft_printf("c\n");
	return (env_copy);
}

void	print_env_list(char **env, t_ms_help *help)
{
	int	i;

	i = 0;
	while (i < help->env_size)
		ft_printf("%s\n", env[i++]);
}

char	*get_env(char *name, char **env, t_ms_help *help)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < help->env_size)
	{
		/*
		// if (ft_strchr(name, '/'))
			//

			num != first
		while  (ft_isalpha(str[i]) || str[i] == '_') && str[i])

		*/
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			tmp = ft_strchr(env[i], 61);
			if (tmp[1])
				return (ft_strdup(&tmp[1]));
			return (ft_strdup(tmp));
		}
		i++;
	}
	return (NULL);	// or "" ?
}

void	update_env(char *name, char *var, char ***env)
{
	int		a;
	char	*tmp;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(var) + 2;
	a = -1;
	while ((*env)[++a])
	{
		if (ft_strncmp((*env)[a], name, ft_strlen(name)) == 0)
		{
			ft_strdel(&(*env)[a]);
			tmp = (char *)malloc(sizeof(char) + len);
			if (!tmp)
				exit (5);
			ft_bzero((void *)tmp, len);
			tmp = ft_strcpy(tmp, (const char *)name);
			ft_strcat(tmp, "=");
			ft_strcat(tmp, var);
			*(*env)[a] = ft_strdub(tmp);
			free(tmp);
		}
	}
}
