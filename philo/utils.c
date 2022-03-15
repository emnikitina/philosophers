/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 19:25:25 by odomenic          #+#    #+#             */
/*   Updated: 2021/08/10 19:56:47 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	new_printf(t_philo *philo, char *str)
{
	unsigned long	time;

	if ((philo->conf->check_end == 1) || ((philo->eat_times
				>= philo->conf->eat_times) && philo->conf->eat_times != -1))
		return ;
	time = get_time() - philo->conf->start_time;
	pthread_mutex_lock(&philo->conf->to_write);
	printf("%lu %d %s\n", time, philo->i, str);
	pthread_mutex_unlock(&philo->conf->to_write);
}

int	ft_isdigit(int c)
{
	if ((c <= '9') && (c >= '0'))
		return (1);
	return (0);
}

void	ft_usleep(int time)
{
	unsigned long	now;

	now = get_time();
	while (get_time() < now + time)
		usleep(500);
}
