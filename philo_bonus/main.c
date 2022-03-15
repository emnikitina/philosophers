/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:14:58 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/01 20:22:34 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*int	init(t_config *config, char **argv)
{
	int	i;

	config->philo = (t_philo *)malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (!config->philo)
		return (-1);
	i = -1;
	while (++i < config->philo_num)
	{
		config->philo[i].conf = config;
		config->philo[i].i = i + 1;
		config->philo[i].last_eat = config->start_time;
		config->philo[i].eat_times = 0;
		sem_unlink("eating");
		config->philo[i].eating = sem_open("eating", O_CREAT, 644, 1);
	}
	return (0);
}*/

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

/*void	init_conf(t_config *config, int argc, char **argv)
{
	config->philo_num = ft_atoi(argv[1]);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("death");
	sem_unlink("eating");
	config->forks = sem_open("forks", O_CREAT, 644, config->philo_num);
	config->to_write = sem_open("write", O_CREAT, 644, 1);
	config->death = sem_open("death", O_CREAT, 644, 1);
	config->eating = sem_open("eating", O_CREAT, 644, 1);
	config->time_die = ft_atoi(argv[2]);
	config->time_eat = ft_atoi(argv[3]);
	config->time_sleep = ft_atoi(argv[4]);
	config->eat_times = -1;
	if (argc == 6)
		config->eat_times = ft_atoi(argv[5]);
	config->start_time = get_time();
	config->check_end = 0;
}*/

void	free_all(t_config *config)
{
	sem_close(config->to_write);
	sem_close(config->death);
	sem_close(config->forks);
	sem_close(config->eating);
	sem_unlink("death");
	sem_unlink("write");
	sem_unlink("forks");
	sem_unlink("eating");
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (check_format(argc, argv))
		return (printf("Wrong format of args\n"));
	if (!ft_atoi(argv[1]))
		return (0);
	config.philo_num = ft_atoi(argv[1]);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("death");
	config.forks = sem_open("forks", O_CREAT, 644, config.philo_num);
	config.to_write = sem_open("write", O_CREAT, 644, 1);
	config.death = sem_open("death", O_CREAT, 644, 1);
	config.time_die = ft_atoi(argv[2]);
	config.time_eat = ft_atoi(argv[3]);
	config.time_sleep = ft_atoi(argv[4]);
	config.eat_times = -1;
	if (argc == 6)
		config.eat_times = ft_atoi(argv[5]);
	config.start_time = get_time();
	config.check_end = 0;
	if (create_processes(&config))
	{
		free_all(&config);
		return (printf("Proccess error\n"));
	}
	free_all(&config);
	return (0);
}
