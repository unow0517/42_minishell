/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:56:47 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/26 17:19:49 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	void	*content;
	t_list	*new_node;

	res = 0;
	while (lst)
	{
		if (f)
			content = f(lst->content);
		if (!content)
			ft_lstclear(&res, del);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			ft_lstclear(&res, del);
			del(content);
		}
		ft_lstadd_back(&res, new_node);
		lst = lst->next;
	}
	return (res);
}

//making head, then iterate following nodes.