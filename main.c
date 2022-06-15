/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:07:18 by lolemmen          #+#    #+#             */
/*   Updated: 2022/05/18 15:50:05 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"
#include "fcntl.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*str;

	(void)argc;
	i = 1;
	fd = open(argv[1], O_RDONLY);
	while (i != 0)
	{
		str = get_next_line(fd);
		if (!str)
			i = 0;
		else
			printf("%s", str);
	}
	close(fd);
	return (0);
}
