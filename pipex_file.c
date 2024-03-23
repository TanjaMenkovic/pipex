/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:13:08 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/02/23 12:49:09 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*file_read(int source)
{
	char	buff[BUFFER_SIZE + 1];
	char	*content;
	char	*tmp_content;
	int		read_size;

	content = NULL;
	read_size = read(source, buff, BUFFER_SIZE);
	buff[read_size] = 0;
	while (read_size > 0)
	{
		if (content)
		{
			tmp_content = ft_strdup(content);
			free(content);
			content = ft_strjoin(tmp_content, buff);
			free(tmp_content);
		}
		else
			content = ft_strdup(buff);
		read_size = read(source, buff, BUFFER_SIZE);
		buff[read_size] = 0;
	}
	return (content);
}

int	file_write(char *content, int fd)
{
	return ((int)write(fd, content, ft_strlen(content)));
}
