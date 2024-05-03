/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:50:33 by abounab           #+#    #+#             */
/*   Updated: 2024/05/03 22:51:36 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_philo_one(t_data philo)
{
	return (printf("philo(%d)[%d, %d, %d]\n", philo.id, philo.t_die, philo.t_eat, philo.t_sleep));
}


int	ft_atoi(char *str)
{
	int	num;
	int sign;

	num = 0;
	sign = 1;
	if (str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (str && *str && *str >= '0' && *str <= '9')
	{
		num *= 10;
		num += (*str - '0');
		str++;
	}
	return (num * sign);
}


int get_philo_args(t_philos *philo, int *condition, int ids, char **av)
{
	philo->philos[ids - 1].id = ids;
	philo->philos[ids - 1].t_die = ft_atoi(av[0]);
	philo->philos[ids - 1].t_eat = ft_atoi(av[1]);
	philo->philos[ids - 1].t_sleep = ft_atoi(av[2]);
	philo->philos[ids - 1].fork_mine = 1;
	// if conditiion
	if (philo->total_philos < ids)
		philo->philos[ids - 1].fork_available = &philo->philos[ids].fork_mine;
	else
		philo->philos[ids - 1].fork_available = &philo->philos[0].fork_mine;
	*condition = -1;
	if (av[3])
		*condition = ft_atoi(av[3]);
	return (1);
}

// args (num_philos, t_die, t_eat, t_sleep, [optional]num_condition_of_eat)

int	get_philos_data(t_philos *philo, char **av)
{
	int	i;

	i = 0;
	philo->total_philos = ft_atoi(av[0]);
	// malloced
	philo->philos = (t_data *) malloc (sizeof(t_data) * philo->total_philos);
	if (philo->total_philos < 0)
		return (0);
	while (i < philo->total_philos)
	{
		get_philo_args(philo, &philo->condition_eat, i + 1, av + 1);
		read_philo_one(philo->philos[i]);
		i++;
	}
	return (1);
}

int	turn_action(t_data *philo)
{
	// iwould get the forks (check if fork[i] = 1 && fork[i + 1] = 1 to start eat)
	// if (i - 1 == eat) (i == sleep) (i + 1 == thinking)
	// if (philo->fork_available && )
	// while (1)
	// {
		
	// }
	printf("id (%d)[%d, %d]\n", philo->id, philo->fork_mine, *philo->fork_available);
	if (philo->fork_mine && *philo->fork_available)
	{
		philo->fork_mine = 0;
		printf(" %d has fork right\n", philo->id);
		*philo->fork_available = 0;
		printf(" %d has fork left\n", philo->id);
		printf(" %d is eating\n", philo->id);
		usleep(philo->t_eat);
		philo->fork_mine = 1;
		*philo->fork_available = 1;
	}
	// if (philo->philos[i])
	return (1);
}

int	create_threads(t_philos philo)
{
	int i;

	i = 0;
	while (i < philo.total_philos)
	{
		pthread_create(&philo.philos[i].thread, NULL, (void *)turn_action, (void *)&philo.philos[i]);
		i++;
	}
	return (1);
}

int	run_simulation(t_philos philo)
{
	int	simulate;
	
	simulate = 0;
	create_threads(philo);
	// while (philo.condition_eat--)
	// {
	// 	if (simulate + 1 > philo.total_philos)
	// 		simulate = -1;
	// 	simulate++;
	// }
	return (1);
}

int	main(int ac, char **av)
{
	t_philos	philo;

	if (ac >= 4 && ac <= 5)
	{
		get_philos_data(&philo, av + 1);
		run_simulation(philo);
	}
}
