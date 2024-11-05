/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:20:35 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/17 13:16:57 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_isdigit(int c)
{
	if (47 < c && c < 58)
		return (1);
	return (0);
}

// int	main()
// {
// 	int	c;

// 	c = 0;
// 	while(c < 177)
// 	{
// 		printf("r%d:%c,%d\n",c,c,ft_isdigit(c));
// 		c++;
// 	}
// }