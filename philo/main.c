/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:37:50 by odomenic          #+#    #+#             */
/*   Updated: 2021/08/31 20:43:48 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_config *config, char **argv)
{
	int	i;

	config->philo = (t_philo *)malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	config->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	if ((!config->forks) || (!config->philo))
		return (-1);
	i = -1;
	while (++i < config->philo_num)
	{
		if (pthread_mutex_init(&config->forks[i], NULL))
			return (-1);
		config->philo[i].conf = config;
		config->philo[i].i = i + 1;
		config->philo[i].last_eat = config->start_time;
		config->philo[i].eat_times = 0;
		if (pthread_mutex_init(&config->philo[i].eating, NULL))
			return (-1);
	}
	return (0);
}

int	check_format(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if ((argc < 5) || (argc > 6))
		return (-1);
	while (i < argc)
	{
		j = 0;
		while (ft_isdigit(argv[i][j]))
			j++;
		if (j != (int)ft_strlen(argv[i]))
			return (-1);
		if (ft_atoi(argv[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_conf(t_config *config, int argc, char **argv)
{
	int	res;

	config->philo_num = ft_atoi(argv[1]);
	res = pthread_mutex_init(&config->death, NULL);
	if (res)
		return (-1);
	res = pthread_mutex_init(&config->to_write, NULL);
	if (res)
		return (-1);
	config->time_die = ft_atoi(argv[2]);
	config->time_eat = ft_atoi(argv[3]);
	config->time_sleep = ft_atoi(argv[4]);
	config->eat_times = -1;
	if (argc == 6)
		config->eat_times = ft_atoi(argv[5]);
	config->start_time = get_time();
	config->check_end = 0;
	config->all_done_eat = 0;
	return (0);
}

void	free_all(t_config *config)
{
	int	i;

	pthread_mutex_destroy(&config->to_write);
	pthread_mutex_destroy(&config->death);
	i = -1;
	while (++i < config->philo_num)
	{
		pthread_mutex_destroy(&config->forks[i]);
		pthread_mutex_destroy(&config->philo[i].eating);
	}
	free(config->forks);
	free(config->philo);
	free(config);
}

int	main(int argc, char **argv)
{
	t_config	*config;

	if (check_format(argc, argv))
		return (printf("Wrong format of args\n"));
	if (!ft_atoi(argv[1]))
		return (0);
	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
		return (printf("Allocation error\n"));
	if (init_conf(config, argc, argv))
		return (printf("Error mutex initialization\n"));
	if (init(config, argv))
	{
		free_all(config);
		return (printf("Allocation or mutex error\n"));
	}
	if (create_threads(config))
	{
		free_all(config);
		return (printf("Pthread error\n"));
	}
	free_all(config);
	return (0);
}
