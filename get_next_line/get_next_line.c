/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:26:52 by dkham             #+#    #+#             */
/*   Updated: 2023/01/29 18:17:14 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list *fd_storage;
	t_list *cur_fd;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// 1. read from fd and add to fd_storage
	// (fd_storage is a linked list, since it should contain multiple fd's), each node in a linked list is from a single fd
	cur_fd = find_fd_in_storage(fd, &fd_storage);
	line = make_line(cur_fd);
	// 2. get a single line from fd_storage to line
	// 3. clean up fd_storage, leaving only the remaining lines
	// 4. return line
	return (line);
}

t_list *find_fd_in_storage(int fd, t_list **fd_storage)
{
	t_list *current;
	t_list *temp;

	current = *fd_storage;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		if (current->next == NULL)
			temp = current;
		current = current->next;
	}
	if (current == NULL)
	{
		current = (t_list *)malloc(sizeof(t_list));
		if (current == NULL)
			return (NULL);
		current->fd = fd;
		current->data = NULL;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
	return (NULL);
}

char	*make_line(t_list *cur_fd)
{
	char	*buf;
	char	*line;
	char	*new;
	char	*del;
	ssize_t	read_size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		read_size = read(cur_fd->fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		if (read_size == 0)
		{
			if (cur_fd->data == NULL)
				return (NULL);
			line = ft_substr(cur_fd->data, 0, ft_strlen(cur_fd->data));
			free(cur_fd->data);
			cur_fd->data = NULL;
			return (line);
		}
		make_line_from_data(cur_fd, &buf, &line, &new, &del);
	}
}

void	make_line_from_data(t_list *cur_fd, char *buf, char **line, char **new, char **del)
{
	buf[BUFFER_SIZE] = '\0';
	cur_fd->data = ft_strjoin(cur_fd->data, buf);
	new = ft_strchr(cur_fd->data, '\n');
	if (new)
	{
		line = ft_substr(cur_fd->data, 0, new - cur_fd->data);
		del = cur_fd->data;
		cur_fd->data = ft_substr(cur_fd->data, new - cur_fd->data + 1, ft_strlen(cur_fd->data));
		free(del);
		return (line);
	}
}