/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:54:04 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:41:15 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// the calloc() function allocates memory and initializes all bits to zero.
void	*ft_calloc(size_t count, size_t size)
{
	int	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
/*
ptr = (castType*) malloc(size);				MALLOC SYNTAX
ptr = (float*) malloc(100 * sizeof(float));	MALLOC EXAMPLE
	The above statement allocates 400 bytes of memory. It's because the size of 
	float is 4 bytes. And, the pointer ptr holds the address of the first byte 
	in the allocated memory.

The malloc() function allocates memory and leaves the memory uninitialized, 
whereas the calloc() function allocates memory and initializes all bits to zero.
The name "calloc" stands for contiguous allocation.

ptr = (castType*)calloc(n,size);			CALLOC SYNTAX
ptr = (float*) calloc(25, sizeof(float));	CALLOC EXAMPLE
	The above statement allocates contiguous space in memory for 25 elements of 
	type float.
*/