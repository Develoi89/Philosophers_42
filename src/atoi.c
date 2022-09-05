/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:59:42 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/05 16:27:38 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

int	ftt_isspace(const char *str, int i)
{
	while (str[i] != '\0')
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		else
			break ;
	}
	return (i);
}

int	ftt_isnegative(const char *str, int i)
{
	if (str[i] == 45)
		return (-1);
	else if (str[i] == 43)
		return (0);
	else
		return (1);
}

int	ftt_convert(const char *str, int i)
{
	int	x;

	x = 0;
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		x = x * 10 + (str[i] - '0');
		i++;
	}
	return (x);
}

int	atoi(const char *str)
{
	int	i;
	int	n;
	int	c;

	i = 0;
	c = 0;
	i = ftt_isspace(str, i);
	n = ftt_isnegative(str, i);
	if (n <= 0)
		i++;
	c = ftt_convert(str, i);
	if (n < 0)
		c = c * n;
	return (c);
}