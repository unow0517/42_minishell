/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:13:33 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/18 18:41:06 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(unsigned int nitems, unsigned int size)
{
	void	*ptr;

	ptr = malloc(nitems * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, nitems * size);
	return (ptr);
}

// calloc initialize the memory allocating 0 on it
// int main(){
//     int i, n;
//     int* a;
//     printf("Number of elements to be entered:");
//     scanf("%d", &n);
//     // a=(int*)calloc(n,sizeof(int));
//     a=(int*)ft_calloc(n,sizeof(int));
//     printf("a[0]: %d, a[1]: %d,  a[2]: %d\n", a[0],a[1],a[2]);
//     printf("Enter %d numbers:\n",n);
//     for(i=0; i < n; i++){
//         scanf("%d",&a[i]);
//     }
//     printf("The numbers entered are: ");
//     for(i=0; i<n; i++){
//         printf("%d",a[i]);
//     }
//     free (a);
//     return 0;
// }