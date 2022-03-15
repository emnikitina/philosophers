/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:21:43 by odomenic          #+#    #+#             */
/*   Updated: 2021/08/09 20:48:52 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_sp(const char *s)
{
	if ((*s == '\t') || (*s == '\n') || (*s == '\v') || (*s == '\f')
		|| (*s == '\r') || (*s == ' '))
		return (1);
	return (0);
}

static int	is_d(const char *str, unsigned long long *num)
{
	if ((*str >= '0') && (*str <= '9'))
	{
		*num = *num * 10 + (*str - '0');
		return (1);
	}
	return (0);
}

static int	ft_max_min(unsigned long long *num, int sign)
{
	unsigned long long	comp;

	comp = 9223372036854775807;
	if ((*num > comp) && (sign > 0))
		return (-1);
	else if ((*num > (comp + 1)) && (sign < 0))
		return (0);
	return (1);
}

static void	ft_check(const char *str, unsigned long long *num, int *sign)
{
	while (*str != '\0')
	{
		while (is_sp(str))
			str++;
		if ((*str == '-') || (*str == '+'))
		{
			if (*str == '-')
				*sign *= -1;
			str++;
		}
		while (is_d(str, num))
			str++;
		if ((is_sp(str) == 0) || (is_d(str, num) == 0))
			break ;
	}
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	num;

	num = 0;
	sign = 1;
	ft_check(str, &num, &sign);
	if (ft_max_min(&num, sign) == -1)
		return (-1);
	if (!(ft_max_min(&num, sign)))
		return (0);
	num *= sign;
	return (num);
}
