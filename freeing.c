/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:13:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/06 13:35:37 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*del;
	t_token	*temp;

	del = *tokens;
	while (del)
	{
		temp = del;
		del = del->next;
		free(temp);
	}
	*tokens = NULL;
}

void	free_cmd_list(t_command **cmds)
{
	t_command	*del;
	t_command	*temp;

	del = *cmds;
	while (del)
	{
		temp = del;
		del = del->next;
		free_temp(temp);
	}
	*cmds = NULL;
}

void	free_temp(t_command *temp)
{
	if (temp->cmd)
		free(temp->cmd);
	if (temp->options)
		free_split_thalia(temp->options);
	if (temp->full_cmd)
		free_split_thalia(temp->full_cmd);
	close_io(temp);
	if (temp->filename)
		free(temp->filename);
	if (temp->builtin_type)
		free(temp->builtin_type);
	if (temp->builtin_arg)
		free(temp->builtin_arg);
	if (temp->to_split && temp->to_split[0] != '\0')
		free(temp->to_split);
	free(temp);
}

void	free_shell(t_shell *shell_info)
{
	// free(shell_info->cwd);
	// free(shell_info->oldpwd);
	free(shell_info->user_input);
	free(shell_info->status);
}

void	free_split_thalia(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = 0;
}

// t_env_mini	*get_nextnode(t_env_mini *env_mini)
// {
// 	t_env_mini	*output;

// 	output = 0;
// 	if (env_mini)
// 	{
// 		if (env_mini->value && ft_strlen(env_mini->value))
// 		{
// 			if (env_mini->name && ft_strlen(env_mini->name))
// 				output = env_mini;
// 		}
// 	}
// 	return (output);
// }

t_env_mini	*get_nextnode(t_env_mini *env_mini)
{
	t_env_mini	*output;

	output = 0;
	if (env_mini)
	{
		if (env_mini->next)
			output = env_mini;
		else
		{
			if (env_mini->value && ft_strlen(env_mini->value))
			{
				if (env_mini->name && ft_strlen(env_mini->name))
					output = env_mini;
			}
		}

	}
	return (output);
}

void	free_envmini(t_env_mini *env_mini)
{
	t_env_mini	*next_node;
	t_env_mini	*current;
	int			i;

	i = 0;
	current = env_mini;
	while (current != NULL)
	{
		if (current->next)
			next_node = current->next;
		if (ft_strlen(current->name))
			free(current->name);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = get_nextnode(next_node);
	}
	env_mini = NULL;
}

// void	free_envmini(t_env_mini *env_mini)
// {
// 	t_env_mini	*next_node;
// 	t_env_mini	*current;
// 	int			i;
// 	i = 0;

// 	current = env_mini;
// 	while (current != NULL)
// 	{
// 		printf("hello\n");
// 		printf("current = %p\n", current);
// 		printf("current->next = %p\n", current->next);
// 		if (current->next) 
// 			next_node = current->next;
// 		printf("current->name = %s\n", current->name);
// 		if (ft_strlen(current->name))
// 		{
// 		printf("current->namein = %s\n", current->name);
// 			free(current->name);
// 		}
// 		printf("current->value = %s\n", current->value);
// 		if (current->value)
// 			free(current->value);
// 		if (current)
// 			free(current);
// 		if (next_node)
// 		{
// 				// printf("current->value11 = %s\n", current->value);
// 			if (next_node->value && ft_strlen(next_node->value))
// 			{
// 				if (next_node->name && ft_strlen(next_node->name))
// 				{
// 					printf("in\n");
// 					current = next_node;
// 				} 
// 				else
// 					break ;
// 			}
// 			else
// 				break ;
// 		}
// 		else
// 			break ;
// 		printf("next_node = %p\n\n", current);
// 		if (i == 120)
// 			exit(0);
// 		i++;
// 	}
// 	env_mini=NULL;
// }
