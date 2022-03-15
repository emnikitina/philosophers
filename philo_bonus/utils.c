/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 19:25:25 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/01 20:03:08 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	new_printf(t_config *conf, char *str)
{
	unsigned long	time;

	if ((conf->check_end == 1) || ((conf->phil_eat_times
				>= conf->eat_times) && conf->eat_times != -1))
		return ;
	time = get_time() - conf->start_time;
	sem_wait(conf->to_write);
	printf("%lu %d %s\n", time, conf->i, str);
	sem_post(conf->to_write);
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
