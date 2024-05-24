/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/13 15:16:58 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_declare_env(t_shell *shell_info)
{
	t_env_mini	*env_mini;

	env_mini = shell_info->env_mini;
	// ft_printf("envmini %d\n", shell_info->env_mini->name);
	while (env_mini)
	{
		if (env_mini->value)
			ft_printf("declare -x %s=\"%s\"\n", env_mini->name, env_mini->value);
		else
			ft_printf("declare -x %s\n", env_mini->name);
		env_mini = env_mini->next;
	}
	*(shell_info->status) = 0;
}

// t_env_mini	*ft_lstnew_envmini(char *inpt)
// {
// 	t_env_mini	*first_node;
// 	char		*ptr_to_equal;

// 	first_node = (t_env_mini *)malloc(sizeof(t_env_mini));
// 	if (!(first_node))
// 		return (0);
// 	ptr_to_equal = ft_strchr(inpt + 7, '=');
// 	if (ptr_to_equal == 0)
// 	{
// 		// printf("ptrequal=%s\n", ptr_to_equal);
// 		first_node->name = inpt + 7;
// 		first_node->value = NULL;
// 		return (first_node);
// 	}
// 	first_node->name = ft_substr(inpt + 7, 0, ptr_to_equal - (inpt + 7));
// 	first_node->value = ft_substr(ptr_to_equal + 1, 0, ft_strlen(ptr_to_equal));
// 	first_node->next = 0;
// 	return (first_node);
// }

t_env_mini	*ft_lstnew_envmini(char *name, char *value)
{
	t_env_mini	*first_node;

  first_node = (t_env_mini *)malloc(sizeof(t_env_mini));
	first_node->name = name;
//   printf("value=%s\n", value);
  first_node->value = value;
//   printf("envminivalue=%s\n", first_node->value);

	first_node->next = 0;
	return (first_node);
}

t_env_mini	*ft_lstlast_envmini(t_env_mini *lst)
{
	t_env_mini	*result;

	if (!lst)
		return (0);
	result = lst;
	while (result->next != 0)
		result = result->next;
	return (result);
}

void	ft_lstadd_back_envmini(t_env_mini **lst, t_env_mini *new)
{
	if (!*lst || !lst)
		*lst = new;
	else
		ft_lstlast_envmini(*lst)->next = new;
}

int	is_al_num_underscore(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str && str)
	{
		if (ft_isalnum(*str) || *str == '_')
			str++;
		else
			return (0);
	}
	return (1);
}

// void	run_export_singlekeyword(t_shell *shell_info)
// {
// 	char		*inpt;
// 	t_env_mini	*env_mini;
// 	char		*ptr_to_equal;
// 	char		*var_name;
// 	char		*var_value;

// 	inpt = shell_info->user_input;
// 	ptr_to_equal = ft_strchr(inpt + 7, '=');
// 	if (ptr_to_equal == 0)
// 	{
// 		// printf("ptrequal=%s\n", ptr_to_equal);
// 		var_name = inpt + 7;
// 		var_value = NULL;
// 	}
// 	else
// 	{
// 		var_name = ft_substr(inpt + 7, 0, ptr_to_equal - (inpt + 7));
// 		var_value = ft_substr(ptr_to_equal + 1, 0, ft_strlen(ptr_to_equal));
// 	}
// printf("ivn %s ivv %s\n", var_name, var_value);
// 	// printf("isalnu %d\n",  is_al_num_underscore(inpt + 7));
// 	// printf("inpt7 %s\n", inpt + 7);
// 	if (!var_name || !is_al_num_underscore(var_name))
// 		ft_printf("minishell: export: `%s' not a valid identifier\n", inpt + 7);
// 	if (inputis(inpt, "export") || inputis(inpt, "export "))
// 		run_declare_env(shell_info);
// 	else if (inputstartswith(inpt, "export ") && is_al_num_underscore(var_name))
// 	{
// 		// printf("inside ivn %s ivv %s\n", var_name, var_value);
// 		// env_mini = ft_lstnew_envmini(inpt);
// 		env_mini = ft_lstnew_envmini(var_name, var_value);
// 		ft_lstlast_envmini(shell_info->env_mini)->next = env_mini;
// 	}
// }

void	run_export_keyword(char	*str, t_shell *shell_info)
{
	char		*ptr;
	char		*ptr_to_equal;
	char		*var_name;
	char		*var_value;
	t_env_mini	*env_mini;

	ptr = str;
	printf("hi\n");
	ptr_to_equal = ft_strchr(ptr, '=');
	if (ptr_to_equal == 0)
	{
		// printf("ptrequal=%s\n", ptr_to_equal);
		var_name = ptr;
		var_value = NULL;
	}
	else
	{
		var_name = ft_substr(ptr, 0, ptr_to_equal - ptr);
		var_value = ft_substr(ptr_to_equal + 1, 0, ft_strlen(ptr_to_equal));
	}
	// printf("inside ivn %s ivv %s\n", var_name, var_value);
	if (!var_name || !is_al_num_underscore(var_name))
	{
		*(shell_info->status) = 1;
		ft_printf("minishell: export: `%s' not a valid identifier\n", ptr);
	}
	else if (is_al_num_underscore(var_name))
	{
		// printf("inside ivn %s ivv %s\n", var_name, var_value);
		// env_mini = ft_lstnew_envmini(inpt);
		env_mini = ft_lstnew_envmini(var_name, var_value);
		ft_lstlast_envmini(shell_info->env_mini)->next = env_mini;
		*(shell_info->status) = 0;
	}
}


// void	run_export_multiple(t_shell *shell_info)
void	run_export(char *str, t_shell *shell_info)
{
	char	*inpt;
	char	**keywords;

	inpt = str;
	
	// //OPTION1. WHEN ONLY KEYWORDS ARE PASSED
	// if (!ft_strlen(inpt))
	// 	run_declare_env(shell_info);
	// else
	// {
	// 	keywords = ft_split(inpt, ' ');
	// //OPTION1. END

	//OPTION2. WHEN WHOLE STRING IS PASSED
	if (inputis(inpt, "export") || inputis(inpt, "export "))
		run_declare_env(shell_info);
	else
	{
		keywords = ft_split(inpt + 7, ' ');
	//OPTION2. END

		printf("kw %s\n", *keywords);
		if (keywords  && *keywords && ft_strlen(*keywords))
			ft_printf("kwlen %d\n", ft_strlen(*keywords));

		while (keywords && *keywords)
		{
			run_export_keyword(*keywords, shell_info);
			keywords++;
		}
	}
}

//var name = >onlyUNDERSCORE, ALPHANUMERIC!
//EXPORT =>  makes the specified variable available to child processes of the current shell. 
//DECLARE => 
//export 'hey=pi' all="mor>>|ning"

//	if (inputis(inpt, "export") || inputis(inpt, "export "))
//		run_declare_env(shell_info);