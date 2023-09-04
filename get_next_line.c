/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:40:30 by vmontoli          #+#    #+#             */
/*   Updated: 2023/09/04 23:46:39 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//	if (fd < 0 || BUFFER_SIZE <=0 || 
char	*get_next_line(int fd)
{
	static t_buffer_node	*buffer_list = NULL;
	t_buffer_node			*curr_buff_node;
	char					*result;

	if (buffer_list == NULL)
		buffer_list = new_buffer_node(fd);
	curr_buff_node = buffer_list;
	while (curr_buff_node != NULL)
	{
		set_newline_pos(curr_buff_node);
		if (curr_buff_node->has_newline || curr_buff_node->has_eof)
		{
			result = generate_result(buffer_list);
			if (result == NULL)
				return (free_buffer_list(&buffer_list, false));
			tidy_buff_list(&buffer_list);
			return (result);
		}
		curr_buff_node->next = new_buffer_node(fd);
		curr_buff_node = curr_buff_node->next;
	}
	return (free_buffer_list(&buffer_list, false));
}

t_buffer_node	*new_buffer_node(int fd)
{
	t_buffer_node	*buff_node;
	ssize_t			bytes_read;

	buff_node = malloc(sizeof(t_buffer_node));
	if (buff_node == NULL)
		return (NULL);
	bytes_read = read(fd, buff_node->buffer, BUFFER_SIZE);
	//TODO: bytes_read 0 tiene que mantenerse para marcar EOF (al anterior?)
	if (bytes_read == -1 || bytes_read == 0)
	{
		free(buff_node);
		return (NULL);
	}
	buff_node->start = buff_node->buffer;
	buff_node->has_eof = bytes_read < BUFFER_SIZE;
	buff_node->size = (size_t) bytes_read;
	buff_node->has_newline = false;
	buff_node->next = NULL;
	return (buff_node);
}

void	tidy_buff_list(t_buffer_node **buffer_list_ptr)
{
	free_buffer_list(buffer_list_ptr, true);
	if ((*buffer_list_ptr)->has_newline
		&& ((*buffer_list_ptr)->size > (*buffer_list_ptr)->newline_pos + 1))
	{
		(*buffer_list_ptr)->start += (*buffer_list_ptr)->newline_pos + 1;
		(*buffer_list_ptr)->size -= (*buffer_list_ptr)->newline_pos + 1;
	}
	else
	{
		free(*buffer_list_ptr);
		*buffer_list_ptr = NULL;
	}
}

void	set_newline_pos(t_buffer_node *buff_node)
{
	size_t	i;

	i = 0;
	buff_node->has_newline = false;
	while (i < buff_node->size)
	{
		if (buff_node->start[i] == '\n')
		{
			buff_node->has_newline = true;
			buff_node->newline_pos = i;
			break ;
		}
		i++;
	}
}

void	*free_buffer_list(t_buffer_node **buffer_list_ptr,
					bool maintain_last)
{
	t_buffer_node	*aux_curr;
	t_buffer_node	*aux_next;

	if (buffer_list_ptr == NULL)
		return (NULL);
	aux_curr = *buffer_list_ptr;
	if (aux_curr == NULL)
		return (NULL);
	aux_next = aux_curr->next;
	while (aux_next != NULL)
	{
		free(aux_curr);
		aux_curr = aux_next;
		aux_next = aux_curr->next;
	}
	if (maintain_last)
		*buffer_list_ptr = aux_curr;
	else
	{
		free(aux_curr);
		*buffer_list_ptr = NULL;
	}
	return (*buffer_list_ptr);
}
