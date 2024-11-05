/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:39:36 by junhhong          #+#    #+#             */
/*   Updated: 2024/09/30 10:23:38 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	meals_return(t_args *args, int i)
{
	int	new;

	pthread_mutex_lock(&args->meals);
	new = args->philo_struct[i].meals;
	pthread_mutex_unlock(&args->meals);
	return (new);
}

int	died_check(t_args *args)
{
	pthread_mutex_lock(&args->died_lock);
	if (args->is_died == 0)
	{
		pthread_mutex_unlock(&args->died_lock);
		return (0);
	}
	pthread_mutex_unlock(&args->died_lock);
	return (1);
}

int	is_allfull(t_args *args, int sum)
{
	pthread_mutex_lock(&args->allfull_lock);
	if (sum == args->nop)
	{
		args->all_full = 1;
		pthread_mutex_unlock(&args->allfull_lock);
		return (1);
	}
	pthread_mutex_unlock(&args->allfull_lock);
	return (0);
}

int	is_allfull2(t_args *args)
{
	pthread_mutex_lock(&args->allfull_lock);
	if (args->all_full == 1)
	{
		pthread_mutex_unlock(&args->allfull_lock);
		return (1);
	}
	pthread_mutex_unlock(&args->allfull_lock);
	return (0);
}

int	is_finished(t_args *args, int i, int value)
{
	pthread_mutex_lock(&args->finished_lock);
	if (value != 0)
	{
		args->philo_struct[i].finished = value;
		pthread_mutex_unlock(&args->finished_lock);
		return (0);
	}
	if (args->philo_struct[i].finished == 1)
	{
		pthread_mutex_unlock(&args->finished_lock);
		return (1);
	}
	pthread_mutex_unlock(&args->finished_lock);
	return (0);
}
