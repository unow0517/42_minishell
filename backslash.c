/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:56:43 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/18 11:45:42 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*backslash(char	*str)
// {
// 	char	*ptr;
// 	char	*ws;
// 	char	*output;

// 	ptr = str;
// 	output = 0;
// 	// ws = ptr_ws(ptr);
// 	while (*ptr)
// 	{
// 		// if (*ptr == '\\' && *(ptr + 1) == '$')
// 		if (*ptr == '\\')
// 		{
// 			ptr++;
// 			if (*ptr == '$')
// 				ptr++;
// 			else
// 				return (ptr);
// 			ws = ptr_ws(ptr);
// 			// ft_printf("hi ws %s", ws);
// 			printf("hi\n");
// 			if (!ws)
// 				output = ptr;
// 			else
// 				output = ft_substr(ptr + 2, 0, ws - (ptr + 2));
// 		}
// 		ptr++;
// 	}
// 	return (output);
// }

// /$USER /$HOME => $USER
char	*backslash_piece(char	*str)
{
	char	*ptr;
	char	*ws;
	char	*output;

	ptr = str;
	output = 0;
	// ws = ptr_ws(ptr);
	while (*ptr)
	{
		if (*ptr == '\\')
		{
			ws = ptr_ws(ptr);
			// ft_printf("hi ws %s", ws);
			// printf("hi\n");
			if (!ws)
				return (ptr + 1);
			else
				return (ft_substr(ptr + 1, 0, ws - (ptr + 1)));
		}
		ptr++;
	}
	return (output);
}

//1.Escaping Special Characters
//2. Line Continuation
//3. Special Character Escapes in Strings \n, \t
//touch file\ with\ spaces.txt
//ls file\ with\ spaces.txt

//5. Escaping Quotes
//6. Escaping Meta-characters in Regular Expressions
//7. Special Sequence Escapes /b, /a


//input == \ => next line

//if '\ ' exist in user input WORD\ WORD => return "WORD WORD"

//echo cd export unset