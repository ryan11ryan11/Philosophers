/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:23:06 by junhhong          #+#    #+#             */
/*   Updated: 2024/09/30 10:21:48 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	allfull_check(t_args *args)
{
	pthread_mutex_lock(&args->allfull_lock);
	if (args->all_full == 0)
	{
		pthread_mutex_unlock(&args->allfull_lock);
		return (0);
	}
	pthread_mutex_unlock(&args->allfull_lock);
	return (1);
}

void	*philo_action(void *arginfo)
{
	t_philo	*arginfo2;
	t_args	*args;
	int		philo_index;

	arginfo2 = (void *)arginfo;
	args = arginfo2->args;
	philo_index = arginfo2->philo_index;
	if (arginfo2->philo_index % 2 == 0)
		usleep (3000);
	while (died_check(args) != 1 && allfull_check(args) != 1)
	{
		thinking(arginfo2->args, arginfo2->philo_index);
		fork_take (arginfo2->args, arginfo2->philo_index);
		if (meals_return(args, philo_index) >= args->not)
			is_finished(args, philo_index, 1);
		if (is_allfull2(args) == 1)
		{
			fork_release(arginfo2->args, arginfo2->philo_index);
			announce(args, philo_index, SLEEPING);
			return (NULL);
		}
		fork_release(arginfo2->args, arginfo2->philo_index);
		sleeping(arginfo2->args, arginfo2->philo_index);
	}
	return (NULL);
}

int	announce(t_args *args, int philo_index, char *msg)
{
	long	time;

	pthread_mutex_lock(&args->starttime_lock);
	time = get_time() - args->start_time;
	pthread_mutex_unlock(&args->starttime_lock);
	if (died_check(args) == 1)
		return (1);
	pthread_mutex_lock(&args->announce_lock);
	if (ft_strcmp(msg, "died") == 0)
	{
		pthread_mutex_unlock(&args->announce_lock);
		pthread_mutex_lock(&args->died_lock);
		args->is_died = 1;
		printf("%ld %d %s\n", time, philo_index, msg);
		pthread_mutex_unlock(&args->died_lock);
		return (1);
	}
	else
		printf("%ld %d %s\n", time, philo_index, msg);
	pthread_mutex_unlock(&args->announce_lock);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++ ;
	}
	return (0);
}
