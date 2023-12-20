/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by yude-oli          #+#    #+#             */
/*   Updated: 2023/12/20 12:54:46 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
/*
int main() {
	const char *str1 = "apple";
	const char *str2 = "applesauce";
	size_t n = 5; // Number of characters to compare

	int result = ft_strncmp(str1, str2, n);

	if (result == 0) {
		printf("The first %zu characters of \"%s\" and \"%s\" 
		are equal.\n", n, str1, str2);
	} else if (result < 0) {
		printf("The first %zu characters of \"%s\" 
		are less than \"%s\".\n", n, str1, str2);
	} else {
		printf("The first %zu characters of \"%s\" 
		are greater than \"%s\".\n", n, str1, str2);
	}

	return 0;
}*/
