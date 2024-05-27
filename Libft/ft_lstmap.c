/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:07:40 by tsimitop          #+#    #+#             */
/*   Updated: 2024/03/24 20:07:42 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Iterates the list ’lst’ and applies the function ’f’ on the content of each
// node. Creates a new list resulting of the successive applications of the
// function ’f’. The ’del’ function is used to delete the content of a node
// if needed.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_list;
	void	*f_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		f_content = f(lst->content);
		tmp = ft_lstnew(f_content);
		if (!tmp)
		{
			ft_lstclear(&new_list, del);
			del(f_content);
			return (NULL);
		}
		ft_lstadd_back(&new_list, tmp);
		lst = lst->next;
	}
	return (new_list);
}
