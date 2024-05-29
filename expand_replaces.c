/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:57:48 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/29 14:36:34 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_bs_dollar(t_shell *shell_info)
{
	char	*inpt;
	int		i_sq;

	inpt = 0;
	i_sq = 0;
	if (shell_info->user_input)
		inpt = shell_info->user_input;
	while (inpt && *inpt)
	{
		update_quoted(inpt, &i_sq);
		if (!i_sq)
		{
			if (*inpt == '\\' && *(inpt + 1) == '$')
				*(inpt + 1) = '^';
			else if (*inpt == '$' && *(inpt + 1) == '\\')
				*inpt = '^';
		}
		inpt++;
	}
}

char	*replace_exp(char *inpt, char *var_value, int var_name_len)
{
	char	*str_till_dollar;
	char	*str_after_varname;
	char	*ptr_dollar;

	if (!inpt)
		return (0);
	str_till_dollar = 0;
	str_after_varname = 0;
	ptr_dollar = ft_strchr(inpt, '$');
	if (ptr_dollar)
	{
		str_till_dollar = ft_substr(inpt, 0, ptr_dollar - inpt);
		str_after_varname = ptr_dollar + var_name_len + 1;
	}
	if (str_till_dollar && var_value && str_after_varname)
		return (join_three(str_till_dollar, var_value, str_after_varname));
	else if (ptr_dollar && !var_value)
	{
		if (!ft_strlen(str_till_dollar) && !ft_strlen(str_after_varname))
			return ("");
		else
			return (ft_strjoin(str_till_dollar, str_after_varname));
	}
	else
		return (inpt);
}

void	replace_dollar_question(t_shell *shell_info)
{
	char	*str;
	char	*inpt;
	char	*till_d;
	char	*after_q;
	char	*j;

	str = 0;
	if (shell_info->user_input)
		str = shell_info->user_input;
	inpt = str;
	till_d = 0;
	after_q = 0;
	while (*str)
	{
		if (*str == '$' && *(str + 1) == '?')
		{
			till_d = ft_substr(inpt, 0, str - inpt);
			after_q = str + 2;
			j = join_three(till_d, ft_itoa(*(shell_info->status)), after_q);
			shell_info->user_input = j;
		}
		if (str + 1)
			str++;
	}
}

void	replace_caret(t_shell *shell_info)
{
	char	*inpt;
	int		cnt;
	char	*output;

	inpt = shell_info->user_input;
	cnt = 0;
	while (*inpt)
	{
		if (*inpt == '\\' && *(inpt + 1) == '^')
			cnt++;
		if (*inpt == '^' && *(inpt + 1) == '\\')
			cnt++;
		inpt++;
	}
	inpt = shell_info->user_input;
	output = malloc(ft_strlen(inpt) - cnt + 1);
	cpy_str(inpt, output, cnt);
	shell_info->user_input = output;
}

void	replace_exps_loop(t_shell *shell_info)
{
	char	*str;
	int		i_sq;
	char	*start;

	str = 0;
	i_sq = 0;
	if (shell_info->user_input)
		str = shell_info->user_input;
	start = str;
	while (*str)
	{
		update_quoted(str, &i_sq);
		exp_shell(str, &i_sq, start, shell_info);
		if (str + 1)
			str++;
	}
}
