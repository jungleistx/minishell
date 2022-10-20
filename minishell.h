/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:35:59 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/20 18:53:07 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/printf/includes/ft_printf.h"
# include <sys/stat.h>

#include <stdio.h>	//	----	----	----	DELETE	 ----	----

typedef struct s_ms_help
{
	int		found;		//	?
	char	**env;		//	copy of env
	int		env_size;	//	env_list_size
	int		arguments;	//	# of cla
}			t_ms_help;

// env.c
char	**copy_env_list(char **env, t_ms_help *help);
void	print_env_list(char **env, t_ms_help *help);
int		get_env_list_size(char **env);
void	update_env(char *name, char *var, char ***env, t_ms_help *h);
char	*get_env(char *name, char **env, t_ms_help *help);

// parser.c
int		skip_whitespace(char *str);
int		find_argument_len(char *str);
char	**get_arguments(char *str, int argc);
int		ms_count_arguments(char *str);
int		parse_input(char *str, char ***args, t_ms_help *help);

// parser_quotes.c
int		count_quotes(char *str);
int		find_matching_quote(char *str, char quote);
void	strip_quotes(char ***args, int argc);

// bin_validation.c
int		validate_executable(char *path, char *command);
int		validate_paths(char ***env, char *command, t_ms_help *help);
int		validate_bin_name(char *command, char ***env, t_ms_help *help);

void	execute_bins(char **args, t_ms_help *help, char ***env);
void	convert_env_list(char ***args, int argc, char **env, t_ms_help *help);
size_t	get_longest_env_len(char *name, char *env);
void	print_env_list_orig(char **env);
void	unset_env(char ***env, char *name, t_ms_help *help);
void	loop_unset_env(char ***env, char **args, t_ms_help *help);
#endif

/*	EXIT
1	gnl
2	strsplit
3	arg malloc
4	copy env list malloc
5	update_env_malloc
6	add_env malloc
7	update dollar post malloc
8	update dollar i>0 malloc
9	update dollar i<0 malloc
11  test_update_malloc
12	get_pre_dollar_content malloc
13	update home get_env return ""
14	update home remalloc str
15	unset_env new char** malloc
16	execute_paths strjoin three
17	validate_paths strsplit
18	validate_check_exe strjoin three

10	exit input (SUCCESS)
*/

// 				while true; do leaks minishell; sleep 1; done

// 0 echo
// 1 "1""1"
// 2 "1"

// 0 echo
// 1 11
// 2 1


/*
'$'   -> strip
$''	  -> -$
$""   -> strip
...   -> convert + strip
*/
