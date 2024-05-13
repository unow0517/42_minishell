/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:39:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/13 15:12:32 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_al_num_udsc_c(char c)
// {
// 	if (ft_isalnum(c) || c == '_')
// 		return (1);
// 	return (0);
// }

// //if $ in str, return lenth of first varname
// int	varname_len(char *str)
// {
// 	int			i;
// 	// char		*ptr;

// 	i = 0;
// 	while (*str && str)
// 	{
// 		if (*str == '$')
// 		{
// 			str++;
// 			while (is_al_num_udsc_c(*str))
// 			{
// 				i++;
// 				str++;
// 			}
// 			if (!is_al_num_udsc_c(*str))
// 				break ;
// 		}
// 		str++;
// 	}
// 	return (i);
// }

// //return var value from string, namelen, envlist.
// char	*varvalue(int var_name_len, char *str, t_env_mini *env_mini)
// {
// 	char	*ptr_dollar;
// 	char	*varname;

// 	ptr_dollar = ft_strchr(str, '$'); //first $ position
// 	if (!ptr_dollar)
// 		return (0);
// 	varname = ft_substr(ptr_dollar + 1, 0, var_name_len);
// 	// ft_printf("vn %s\n", varname);
// 	while (env_mini)
// 	{
// 		if (inputis(env_mini->name, varname))
// 			return (env_mini->value);
// 		if (env_mini->next)
// 			env_mini = env_mini->next;
// 		else
// 			break ;
// 	}
// 	return (0);
// }

// //MALLOC!
// char	*replace_expand(char *inpt, char *var_value, int var_name_len)
// {
// 	int		var_value_len;
// 	char	*str_till_dollar;
// 	char	*str_after_varname;
// 	char	*join1;
// 	// char	*join2;
	
// 	var_value_len = ft_strlen(var_value);
// 	str_till_dollar = ft_substr(inpt, 0, ft_strchr(inpt, '$') - inpt);
// 	str_after_varname = ft_strchr(inpt, '$') + var_name_len + 1;
// 		ft_printf("len %d\n", var_name_len);
// 	ft_printf("std %s\n", str_till_dollar);
// 	ft_printf("sav %s\n", str_after_varname);
// 	join1 = ft_strjoin(str_till_dollar, var_value);
// 	ft_printf("join1 %s\n", join1);

// 	return (join1);
// }

// char	*dollar_expand(t_shell *shell_info)
// {
// 	t_env_mini	*env_mini;
// 	char		*inpt;
// 	char		*var_value;
// 	int			len;
// 	char		*replaced;
	
// 	len = 0;
// 	inpt = NULL;
// 	if (shell_info->user_input)
// 		inpt = shell_info->user_input;
// 	// 			ft_printf("i %d\n", i);
// 	ft_printf("inpt %s\n", inpt);
// 	// ft_printf("isalnumun %s\n", is_al_num_underscore(0));
// 	env_mini = shell_info->env_mini;
// 	len = varname_len(inpt);
// 	ft_printf("lens %d\n", len);
// 	var_value = varvalue(len, inpt, env_mini);
// 	ft_printf("vv %s\n", var_value);
// 	replaced = replace_expand(inpt, var_value, len);
// 	// ft_printf("rp %s\n", replaced);

// 	// while (*inpt)
// 	// {
// 	// 	len = varname_len(inpt);
// 	// 	ft_printf("lens %d\n", len);
// 	// 	var_value = varvalue(len, inpt, env_mini);
// 	// 	replace_expand(inpt, var_value, len);
// 	// 	inpt++;
// 	// }

// 	// env_mini = shell_info->env_mini;
// 	// while (env_mini)
// 	// {
// 	// 	if (ft_strncmp(env_mini->name, str, ft_strlen(str)) == 0)
// 	// 		env_mini->value;
// 	// }
// 	return (inpt);
// }

// //$? required