/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:53:21 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/26 17:53:21 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_except_literal(t_shell *shell_info)
{
	replace_bs_dollar(shell_info);
	replace_dollar_question(shell_info);
	replace_exps_loop(shell_info);
}

void	rm_outest_q_and_exp(t_shell *shell_info)
{
	char	c;
	char	*str;

	c = 0;
	str = shell_info->user_input;
	while (str && *str)
	{
		c = first_quote(str);
		if (c != 'n')
		{
			if (c == '"')
				expand_except_literal(shell_info);
		}
		else
			expand_except_literal(shell_info);
		str++;
	}
}

void	rm_outest_q(t_shell *shell_info)
{
	char	c;
	char	*str;

	str = shell_info->user_input;
	c = first_quote(str);
	if (c != 'n')
		shell_info->user_input = rm_quotes(shell_info->user_input, c);
}

void	rm_ws_following_d_less(t_shell *shell_info)
{
	char	*str;
	char	*inpt;
	char	*str_till_dless;
	char	*str_after_dless;

	str = shell_info->user_input;
	inpt = str;
	str_till_dless = 0;
	str_after_dless = 0;
	while (str && *str)
	{
		if (*str == '<' && *(str + 1) == '<')
		{
			str_till_dless = ft_substr(inpt, 0, (str + 1) - inpt + 1);
			str_after_dless = str + 2;
			shell_info->isheredoc = 1;
			break ;
		}
		if (str + 1)
			str++;
	}
	rm_ws_aft_dl(str_till_dless, str_after_dless, shell_info);
	if (str_till_dless)
	{
		free(str_till_dless);
		str_till_dless = NULL;
	}
}

void	ft_expand(t_shell *shell_info)
{
	if (!shell_info->user_input)
		return ;
	if (ft_strchr(shell_info->user_input, '$') == 0)
		return ;
	rm_ws_following_d_less(shell_info);
	if (shell_info->isheredoc == 0)
		rm_outest_q_and_exp(shell_info);
	else
	{
		rm_outest_q(shell_info);
		shell_info->isheredoc = 0;
	}
	replace_caret(shell_info);
}
