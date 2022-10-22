/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:03:18 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/21 23:11:45 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_post_dollar_content(char *str, int i, size_t len, size_t post_len)
{
	char	*tmp;

	tmp = ft_strsub((const char *)&str[(size_t)i + len + 1], 0, post_len);
	if (!tmp)
		exit(12);
	return (tmp);
}

void	replace_dollar(char **str, char *cont, char **pre, int i, char **post)
{
	if (i > 0)
	{
		*str = ft_strncpy(*str, (const char *)*pre, (size_t)i);
		*str = ft_strcat(*str, (const char *)cont);
		ft_strdel(pre);
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
	// size_t	env_len;

	tmp = get_full_env_name(&(*str)[i + 1]);
	// env_len = ft_strlen(tmp);
	content = get_env(tmp, env, help);
	// post_len = ft_strlen(*str) - env_len - (size_t)i - 1;
	post_len = ft_strlen(*str) - ft_strlen(tmp) - (size_t)i - 1;
	ft_strdel(&tmp);
	if (post_len > 0)
		tmp = get_post_dollar_content(*str, i, ft_strlen(tmp), post_len);
		// tmp = get_post_dollar_content(*str, i, env_len, post_len);
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
	if (tot_len > 1)
	{
		post_tilde = ft_strsub((const char *)*str, 1, tot_len - 1);
		if (post_tilde[0] == '/')
		{
			ft_strdel(str);
			*str = ft_strjoin((const char *)home, (const char *)post_tilde);
		}
		ft_strdel(&post_tilde);
	}
	else
	{
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
				update_home(&(*args)[a], env, help);
		}
	}
}
