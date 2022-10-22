/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:22:09 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/22 20:26:04 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(char **var, char ***env, t_ms_help *h)
{
	char	**new_env;
	int		arr_size;

	h->env_size++;
	arr_size = h->env_size;
	new_env = (char **)malloc(sizeof(char *) * (arr_size + 1));
	if (!new_env)
		exit(6);
	new_env[arr_size--] = NULL;
	new_env[arr_size] = ft_strdup(*var);
	while (--arr_size >= 0)
		new_env[arr_size] = ft_strdup((*env)[arr_size]);
	ft_free_doublearray(env);
	ft_strdel(var);
	*env = new_env;
}

void	update_env(char *name, char *cont, char ***env, t_ms_help *h)
{
	int		a;
	size_t	env_len;
	int		found;
	char	*tmp;

	found = 0;
	a = -1;
	while ((*env)[++a])
	{
		env_len = get_longest_env_len(name, (*env)[a]);
		if (ft_strncmp((*env)[a], name, env_len) == 0)
		{
			found = 1;
			ft_strdel(&(*env)[a]);
			(*env)[a] = ft_strjoin_three(name, "=", cont);
			break ;
		}
	}
	if (found == 0)
	{
		tmp = ft_strjoin_three(name, "=", cont);
		add_env(&tmp, env, h);
	}
}

void	set_env(char **args, t_ms_help *help)
{
	int		i;
	char	*name;
	char	*content;
	int		env_len;

	i = 0;
	while (++i < help->arguments)
	{
		env_len = (int)ft_strlen_match(args[i], '=');
		name = ft_strsub((const char *)args[i], 0, env_len);
		content = ft_strchr((const char *)args[i], 61);
		content++;
		if (ft_strcount(args[i], '=') > 0 && (ft_isalpha((*args)[0])
			|| (*args)[0] == '_'))
			update_env(name, content, &(help->env), help);
		ft_strdel(&name);
	}
}
