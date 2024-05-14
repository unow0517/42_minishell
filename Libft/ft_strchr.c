/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:40:33 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/24 10:34:16 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;

	ptr = (char *) str;
	while (*ptr != '\0')
	{
		if (*ptr != (char)c)
			ptr++;
		else
			return (ptr);
	}
	if (*ptr == (char)c)
	{
		return (ptr);
	}
	return (0);
}

// use new ptr to not discards 'cnost char *' qualifiers

// #include <stdio.h>
// #include <string.h>

// int main () {
//    const char str[] = "abcs";
//    const char ch = 't';
//    char *ret;

//    ret = strchr(str, ch);

//    printf("String after |%c| is - |%s|\n", ch, ret);

//    char* ft_ret;

//    ft_ret = ft_strchr(str,ch);

//    printf("String after |%c| is - |%s|\n", ch, ft_ret);

//    return(0);
// }