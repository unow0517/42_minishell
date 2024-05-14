/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:08:52 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/25 14:23:55 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*first_node;

	first_node = (t_list *)malloc(sizeof(t_list));
	if (!(first_node))
		return (0);
	first_node->content = content;
	first_node->next = 0;
	return (first_node);
}

// int	main()
// {
// 	char str[] = "hello";
// 	t_list *ptr;

// 	ptr = ft_lstnew(str);
// 	while(ptr != NULL)
// 	{
// 		printf("%s", ptr->content);
// 		ptr = ptr->next;
// 	}
// 	return (0);
// }