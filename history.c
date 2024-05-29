/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:14:03 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/16 23:14:23 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(t_shell *shell_info)
{
	char			*inpt;
	int				inpt_len;
	int				i;
	HISTORY_STATE	*my_hist;
	HIST_ENTRY		**his_list;

	inpt = shell_info->user_input;
	using_history();
	my_hist = history_get_history_state();
	his_list = history_list();
	inpt_len = ft_strlen(inpt);
	if (inpt_len < 7)
		inpt_len = 7;
	i = 0;
	while (i < my_hist->length)
	{
		printf("\t%i  ", i + 1);
		printf("%s\n", his_list[i]->line);
		i++;
	}
	free(my_hist);
	proc_exit(0, shell_info);
}
