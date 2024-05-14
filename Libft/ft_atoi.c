/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:44:48 by yowoo             #+#    #+#             */
/*   Updated: 2024/03/07 12:44:05 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	res = 0;
	while (*str != '\0')
	{
		if (*str >= 48 && *str <= 57)
			res = res * 10 + (*str - 48);
		else if (!(*str >= 48 && *str <= 57))
			return (sign * res);
		str++;
	}
	return (sign * res);
}

// -,+ = 0
// -0123 = -123
// 0123 = 123
// abc123 = 0
// int main(){
//     char str[]="";
//     int res = atoi(str);
//     int myRes = ft_atoi(str);
//     printf("String: %s, Int: %d\n", str, res);
//     printf("String: %s, Int: %d", str, myRes);    
// }