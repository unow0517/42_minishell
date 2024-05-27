/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:07:18 by tsimitop          #+#    #+#             */
/*   Updated: 2024/03/24 20:09:55 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Deletes and frees the given node and every successor of that node, using the
// function ’del’ and free(3). Finally, the pointer to the list must be set to
// NULL.
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
