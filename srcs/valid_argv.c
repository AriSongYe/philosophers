/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:17:08 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/09 16:19:23 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	valid_argv(int argc, char **argv)
{
	if (!(argc != 5 && argc != 6))
    {
        printf("Error : arg is not proper\n");
		return (1);
    }
	i = 0;
	if (is_num(argv))
	{
		printf("Error : arg must be num\n");
		return (1);
	}
	if (is_int_over(argv))
	{
		return (1);
	}
	return (0);
}

long long	ft_atoll(const char *str)
{
	int			sign;
	size_t		i;
	long long	num;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

int	is_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!((str[i][j] >= '0' && str[i][j] <= '9')
						|| str[i][j] == '-' || str[i][j] == '+'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_int_over(char **str)
{
	long long	num;
	int			i;

	i = 1;
	while (str[i])
	{
		if (ft_strlen(str[i]) >= 20)
		{
			printf("Error : plz use moderate sign\n");
			return (1);
		}
		num = ft_atoll(str[i++]);
		printf("%lld\n", num);
		if (num > 2147483647 || num < -2147483648)
		{
			printf("Error : arg must be int\n");
			return (1);
		}
	}
	return (0);
}
