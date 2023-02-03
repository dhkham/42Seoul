/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:57:16 by dkham             #+#    #+#             */
/*   Updated: 2023/01/30 20:19:44 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"
#include "stdio.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("multiple_nlx5", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	return (0);
}
