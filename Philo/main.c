/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:19:26 by junhhong          #+#    #+#             */
/*   Updated: 2024/09/30 10:36:04 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	lasteat_get(t_args *args, int i)
{
	int	timestamp;

	pthread_mutex_lock(&args->lasteat_lock);
	timestamp = get_time() - args->philo_struct[i].last_eat;
	pthread_mutex_unlock(&args->lasteat_lock);
	return (timestamp);
}

void	*monitoring(void *args)
{
	int		i;
	int		sum;
	t_args	*args2;

	args2 = (t_args *)args;
	while (died_check(args) == 0)
	{
		i = 0;
		sum = 0;
		while (i < args2->nop)
		{
			if (is_finished(args, i, 0) == 1)
				sum ++ ;
			if (is_allfull(args, sum) == 1)
				return (NULL);
			if (lasteat_get(args, i) > (long)args2->ttd)
			{
				announce (args2, i, DIED);
				return (NULL);
			}
			i ++ ;
		}
	}
	return (NULL);
}

void	init(t_args *args)
{
	int			nop;
	int			i;
	pthread_t	monitor;

	i = 0;
	nop = args->nop;
	pthread_create(&monitor, NULL, monitoring, args);
	while (i < nop)
	{
		pthread_mutex_lock(&args->philogroup_lock);
		pthread_create(&args->philo_group[i], NULL, \
		philo_action, &args->philo_struct[i]);
		pthread_mutex_unlock(&args->philogroup_lock);
		i ++ ;
	}
	i = 0;
	while (i < nop)
	{
		pthread_mutex_lock(&args->philogroup_lock);
		pthread_join(args->philo_group[i], NULL);
		i ++ ;
		pthread_mutex_unlock(&args->philogroup_lock);
	}
	pthread_join(monitor, NULL);
}

int	main(int argc, char *argv[])
{
	t_args	args;

	if (argument_check(argc, argv, &args) == 0)
		return (0);
	if (ft_atoi(argv[1]) <= 0)
		return (0);
	if (args.nop == 1)
	{
		one_philo(&args);
		return (0);
	}
	args.philo_group = philo_maker(&args);
	if (args.philo_group == NULL)
		return (0);
	args.fork = forkmaker(&args);
	init(&args);
	free (args.philo_group);
	free (args.philo_struct);
	free (args.fork);
}
