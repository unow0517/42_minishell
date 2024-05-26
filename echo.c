/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:56:43 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/19 16:57:29 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_from_beiginnig(char *inpt, t_shell *shell_info)
{
	char	q;
	char	*first_q_ptr;
	int		len;
	int		noq_len;
	char	*till_first_q;
	char	*start;
	char	*str_in_q;

	q = 0;
	len = 0;
	noq_len = 0;
	start = inpt;
	while (inpt && *inpt)
	{
		if (*inpt == q)
		{
			str_in_q = ft_substr(first_q_ptr + 1, 0, len - 1);
			shell_info->temp = ft_strjoin(shell_info->temp, str_in_q);
			q = 0;
		}
		else if (*inpt == '\'' || *inpt == '"')
		{
			q = *inpt;
			first_q_ptr = inpt;
			till_first_q = ft_substr(start, 0, inpt - start);
			// shell_info->temp = till_first_q;
			shell_info->temp = ft_strjoin(shell_info->temp, str_in_q);
		}
		printf("len %d\n", len);
		printf("q %c\n", q);
		printf("inpt %s\n", inpt);
		printf("shellinfo %s\n\n", shell_info->temp);
		if (q)
		{
			len++;
			noq_len = 0;
		}
		else
		{
			noq_len++;
			len = 0;
		}
		inpt++;
	}
}

// void	run_echo(char *inpt)
void	run_echo(char *inpt, t_shell *shell_info)
{
	// char	*str;
	// char	q;

	// (void)shell_info;
	ft_printf("start: %s\n", inpt);
	// str = inpt;
	// q = first_quote(inpt);
	// str = rm_quotes(str, q);
	exp_from_beiginnig(inpt, shell_info);

	// str = ec_rm_outest_q_and_exp(inpt, shell_info);
	// ft_printf("test: %s\n", str);
	ft_printf("RESULT: %s\n", shell_info->temp);

	// write(2, "HELLO\n", ft_strlen("HELLO\n"));
	//OPTION 1. WHEN THE WHOLE INPUT IS PASSED
	// if (inputstartswith(inpt, "echo -n "))
	// 	ft_printf("%s", inpt + 5);
	// else
	// 	ft_printf("%s\n", inpt + 5);
	// *(shell_info->status) = 0;
	//OPTION 1. END


	// //OPTION 2. WHEN THE STRING AFTER 'echo ' IS PASSED
	// if (inputstartswith(inpt, "echo -n "))
	// 	ft_printf("%s", inpt);
	// else
	// 	ft_printf("%s\n", inpt);
	// *(shell_info->status) = 0;
	// // //OPTION 2. END


	// char	**output;
	// char	*str;

	// output = ft_split(inpt + 5, ' ');
	// // str = *output;
	// // while (str)
	// // {
	// // 	str = backslash_piece(str);
	// // 	str++;
	// // }
	// while (*output)
	// {
	// ft_printf("op %s\n",*output);
	// // ft_printf("bs %s\n",backslash_piece(*output));
	// 	// *output = backslash_piece(*output);
	// 	output++;
	// }
	// str = *output;
	// while (str)
	// {
	// 	ft_printf("%s", str);
	// 	str++;
	// }
	// ft_printf("bs %s\n",backslash(inpt));
	// ft_printf('\\');
}



//ECHO WITH OPTION N!