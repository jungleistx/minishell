/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:35:59 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/10/10 14:00:29 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/printf/includes/ft_printf.h"

#include <stdio.h>	//	----	----	----	DELETE	 ----	----
// space = 32
// tab	 = 9
// ;   	 = 59
// nl 	 = 10


typedef struct s_ms_help
{
	int		found;
	char	**env;
	int		env_size;
}			t_ms_help;

// parser.c
int		skip_whitespace(char *str);
int		find_argument_len(char *str);
char	**get_arguments(char *str, int argc);
int		ms_count_arguments(char *str);
void	parse_input(char *str, char ***args);

// parser_quotes.c
int		count_quotes(char *str);
int		find_matching_quote(char *str, char quote);
void	strip_quotes(char ***args, int argc);

#endif

/*	EXIT
1	gnl
2	strsplit
3	arg malloc
4	copy env list malloc
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
