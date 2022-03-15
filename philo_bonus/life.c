/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:26:40 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/01 20:20:02 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_life(void *config)
{
	t_config	*conf;

	conf = (t_config *)config;
	while (!conf->check_end)
	{
		usleep(100);
		sem_wait(conf->eating);
		if ((get_time() > conf->last_eat + conf->time_die)
			&& (!conf->check_end))
		{
			sem_post(conf->eating);
			sem_wait(conf->death);
			new_printf(conf, "died");
			conf->check_end = 1;
			sem_wait(conf->to_write);
			exit (1);
		}
		sem_post(conf->eating);
	}
	return (NULL);
}

void	life_cycle(t_config *conf)
{
	sem_wait(conf->forks);
	new_printf(conf, "has taken a fork");
	sem_wait(conf->forks);
	new_printf(conf, "has taken a fork");
	sem_wait(conf->eating);
	conf->last_eat = get_time();
	new_printf(conf, "is eating");
	conf->phil_eat_times++;
	ft_usleep(conf->time_eat);
	sem_post(conf->eating);
	sem_post(conf->forks);
	sem_post(conf->forks);
	if (conf->phil_eat_times == conf->eat_times)
		exit(2);
	new_printf(conf, "is sleeping");
	ft_usleep(conf->time_sleep);
	new_printf(conf, "is thinking");
}

void	*process(t_config *config)
{
	pthread_t	death;

	config->last_eat = get_time();
	if (pthread_create(&death, NULL, check_life, config))
		return (NULL);
	if (pthread_detach(death))
		return (NULL);
	if (!(config->i % 2))
		usleep(500);
	while (!config->check_end)
		life_cycle(config);
	return (NULL);
}

void	wait_process(t_config *config)
{
	int	status;
	int	done_eat;

	done_eat = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 2)
		{
			done_eat++;
			if (done_eat == config->philo_num)
				break ;
		}
		if (WEXITSTATUS(status) == 1)
			break ;
	}
}

int	create_processes(t_config *config)
{
	int	i;

	config->philos = (pid_t *)malloc(sizeof(pid_t) * config->philo_num);
	i = -1;
	while (++i < config->philo_num)
	{
		config->i = i + 1;
		config->philos[i] = fork();
		if (config->philos[i] < 0)
			return (-1);
		else if (config->philos[i] == 0)
			process(config);
	}
	wait_process(config);
	i = -1;
	while (++i < config->philo_num)
		kill(config->philos[i], SIGTERM);
	free(config->philos);
	return (0);
}
