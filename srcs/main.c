/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:16:42 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/24 14:34:04 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_exit_error(char *msg, int ret)
{
	ft_putstr_fd((const char *)msg, 2);
	exit(ret);
}

int	validate_whitespace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_iswhitespace(str[i])))
			return (1);
	}
	return (0);
}

void	reset_help(t_ms_help *help)
{
	help->env_size = 0;
	help->arguments = 0;
}

void	free_helpers(char **str, char **pw, char ***args)
{
	ft_strdel(str);
	ft_strdel(pw);
	ft_free_doublearray(args);
}

int	main(void)
{
	char		*str;
	char		**args;
	t_ms_help	help;
	extern char	**environ;
	char		*pw;

	reset_help(&help);
	help.env = copy_env_list(environ, &help);
	while (1)
	{
		pw = getcwd(NULL, 0);
		args = NULL;
		ft_printf("%sminishell %s%s %s-$> %s", BLUE, YELLOW, pw, GREEN, NOCO);
		str = get_input();
		if (str && (str[0] != 0))
		{
			if (parse_input(str, &args, &help))
				execute_commands(&args, &help);
		}
		free_helpers(&str, &pw, &args);
	}
	ft_free_doublearray(&(help.env));
	return (0);
}
