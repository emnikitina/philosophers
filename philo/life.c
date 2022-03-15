/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:55:50 by odomenic          #+#    #+#             */
/*   Updated: 2021/08/10 22:02:23 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *phil)
{
	pthread_mutex_unlock(&phil->eating);
	pthread_mutex_lock(&phil->conf->death);
	new_printf(phil, "died");
	phil->conf->check_end = 1;
	pthread_mutex_lock(&phil->conf->to_write);
	if (phil->conf->philo_num == 1)
		pthread_mutex_unlock(&phil->conf->forks[0]);
}

void	*check_life(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	while (!phil->conf->check_end)
	{
		usleep(100);
		pthread_mutex_lock(&phil->eating);
		if (phil->conf->all_done_eat == phil->conf->philo_num)
		{
			phil->conf->check_end = 1;
			pthread_mutex_unlock(&phil->eating);
			pthread_mutex_lock(&phil->conf->to_write);
			return (NULL);
		}
		if ((get_time() > phil->last_eat + phil->conf->time_die)
			&& (!phil->conf->check_end))
		{
			check_death(phil);
			return (NULL);
		}
		pthread_mutex_unlock(&phil->eating);
	}
	return (NULL);
}

void	life_cycle(t_philo *philo)
{
	pthread_mutex_lock(&philo->conf->forks[philo->i - 1]);
	new_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->conf->forks[philo->i % philo->conf->philo_num]);
	new_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eating);
	philo->last_eat = get_time();
	new_printf(philo, "is eating");
	philo->eat_times++;
	if (philo->eat_times == philo->conf->eat_times)
		philo->conf->all_done_eat++;
	ft_usleep(philo->conf->time_eat);
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->conf->forks[philo->i - 1]);
	pthread_mutex_unlock(&philo->conf->forks[philo->i
		% philo->conf->philo_num]);
	new_printf(philo, "is sleeping");
	ft_usleep(philo->conf->time_sleep);
	new_printf(philo, "is thinking");
}

void	*process(void *philo)
{
	t_philo		*phil;
	pthread_t	death;

	phil = (t_philo *)philo;
	if (phil->conf->check_end)
		return (NULL);
	if (!(phil->i % 2))
		usleep(500);
	phil->last_eat = get_time();
	if (pthread_create(&death, NULL, check_life, phil))
		return (NULL);
	if (pthread_detach(death))
		return (NULL);
	while (!phil->conf->check_end)
		life_cycle(phil);
	return (NULL);
}

int	create_threads(t_config *config)
{
	int	status;
	int	i;

	i = -1;
	while (++i < config->philo_num)
	{
		status = pthread_create(&config->philo[i].th,
				NULL, process, &config->philo[i]);
		if (status)
			return (-1);
	}
	i = -1;
	while (++i < config->philo_num)
	{
		status = pthread_join(config->philo[i].th, NULL);
		if (status)
			return (-1);
	}
	return (0);
}
