/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:35:59 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/24 14:54:06 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/printf/includes/ft_printf.h"
# include <sys/stat.h>

typedef struct s_ms_help
{
	char	**env;
	int		env_size;
	int		arguments;
}			t_ms_help;

// main.c
void	ms_exit_error(char *msg, int ret);
int		validate_whitespace(char *str);
void	reset_help(t_ms_help *help);
void	free_helpers(char **str, char **pw, char ***args);
// binaries.c
int		validate_executable(char *path, char **command);
int		validate_paths(char ***env, char **command, t_ms_help *help);
int		validate_bin_name(char **command, char ***env, t_ms_help *help);
void	execute_bins(char ***args, t_ms_help *help, char ***env);
// builtin.c
void	builtin_echo(char **args);
char	*builtin_cd_get_dest(char *dest, t_ms_help *help);
void	builtin_cd(char **pwd, char *dest, t_ms_help *help);
void	execute_commands(char ***args, t_ms_help *help);
// convert.c
char	*get_post_dollar_content(char *str, int i, size_t len, size_t post_len);
void	replace_dollar(char **str, char *cont, char **pre, char **post);
void	update_arg_dollar(int i, char **str, char **env, t_ms_help *help);
void	update_home(char **str, char **env, t_ms_help *help);
void	convert_env_list(char ***args, int argc, char **env, t_ms_help *help);
// env.c
char	**copy_env_list(char **env, t_ms_help *help);
size_t	get_longest_env_len(char *name, char *env);
char	*get_env(char *name, char **env, t_ms_help *help);
char	*get_full_env_name(char *var);
// env_print.c
void	print_env_list(char **env, t_ms_help *help);
// env_set.c
void	update_env(char *name, char *cont, char ***env, t_ms_help *h);
void	set_env(char **args, t_ms_help *help);
void	add_env(char **var, char ***env, t_ms_help *h);
// env_unset.c
void	copy_env_list_unset(char ***new, char ***env, char *name);
void	unset_env(char ***env, char *name, t_ms_help *help);
void	loop_unset_env(char ***env, char **args, t_ms_help *help);
// input.c
char	*get_input(void);
int		skip_whitespace(char *str);
int		minishell_arguments(char *str);
int		find_argument_len(char *str);
char	**get_arguments(char *str, int argc);
// parser.c
int		find_matching_quote(char *str, char quote);
void	strip_quotes(char ***args, int argc, int a);
int		count_quotes(char *str);
int		parse_input(char *str, char ***args, t_ms_help *help);

#endif

/*	EXIT_CODES
0	exit command (SUCCESS)
3	get_arguments char** malloc
4	copy_env_list char** malloc
6	add_env char** malloc
9	update_arg_dollar ft_strnew NULL
12	get_post_dollar_content ft_strsub NULL
15	unset_env new char** malloc
16	copy_env_list_unset ft_strsub NULL
17	validate_paths ft_strsplit NULL
18	validate_executable ft_strjoin_three NULL
19	execute_bins fork > 0
20	execute_bins execve == -1
21	parser ft_strtrim NULL
*/
