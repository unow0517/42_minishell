/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:39:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/10 14:50:08 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_al_num_udsc_c(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

//if $ in str, return lenth of varname
int	varname_len(char *str)
{
	int			i;

	i = 0;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
		}
		while (is_al_num_udsc_c(*str))
		{
			i++;
			str++;
		}
		if (!is_al_num_udsc_c(*str))
			break ;
		str++;
	}
	return (i);
}
char	*varvalue(int len, char *str, t_env_mini *env_mini)
{
	char	*ptr_dollar;
	char	*varname;
	
	ptr_dollar = ft_strchr(str, '$');
	varname = ft_substr(ptr_dollar + 1, 0, len);
	ft_printf("vn %s\n", varname);
	while (env_mini)
	{
		env_mini = env_mini->next;
	}
	return (str);
}

char	*dollar_expand(t_shell *shell_info)
{
	// t_env_mini	*env_mini;
	char		*str;
	// char		*var_name;
	// char		*ptr;
	int			i;

	i = 0;
	str = NULL;
	if (shell_info->user_input)
		str = shell_info->user_input;
	// 			ft_printf("i %d\n", i);
	ft_printf("str %s\n", str);
	// ft_printf("isalnumun %s\n", is_al_num_underscore(0));
	// while (*str)
	// {
	// 	i = cnt_varname_len(str);
	// 	str++;
	// }
	i = varname_len(str);
	ft_printf("i %d\n", i);
	varvalue(i, str, shell_info->env_mini);
	// env_mini = shell_info->env_mini;
	// while (env_mini)
	// {
	// 	if (ft_strncmp(env_mini->name, str, ft_strlen(str)) == 0)
	// 		env_mini->value;
	// }
	return (str);
}

//$? required