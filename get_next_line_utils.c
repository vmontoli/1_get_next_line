/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:44:42 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/31 04:41:25 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buffer_node	*new_buffer_node(int fd)
{
	t_buffer_node	*buff_node;
	ssize_t			bytes_read;

	buff_node = malloc(sizeof(t_buffer_node));
	if (buff_node == NULL)
		return (NULL);
	bytes_read = read(fd, buff_node->buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(buff_node);
		return (NULL);
	}
	buff_node->start = buff_node->buffer;
	buff_node->size = bytes_read;
	buff_node->next = NULL;
	return (buff_node);
}

ssize_t	find_newline_pos(t_buffer_node *buff_node)
{
	ssize_t	i;

	i = 0;
	while (i < buff_node->size)
	{
		if (buff_node->start[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	*free_buffer_list(t_buffer_node **buffer_list_ptr, bool maintain_last)
{
	t_buffer_node	*aux_curr;
	t_buffer_node	*aux_next;

	if (buffer_list_ptr == NULL)
		return (NULL);
	aux_curr = *buffer_list_ptr;
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
	return (NULL);
}

char	*generate_empty_result(t_buffer_node *buffer_list,
			ssize_t newline_pos)
{
	ssize_t			size;
	t_buffer_node	*curr_buff_node;

	curr_buff_node = buffer_list;
	size = 1;
	while (curr_buff_node->next != NULL)
	{
		size += curr_buff_node->size;
		curr_buff_node = curr_buff_node->next;
	}
	if (newline_pos == -1)
		size += curr_buff_node->size;
	else
		size += newline_pos + 1;
	return (malloc(size));
}

void	fill_result_tidy_buff_list(char *result,
			t_buffer_node **buffer_list_ptr, ssize_t newline_pos)
{
	t_buffer_node	*curr_buff_node;
	char			*curr_result;
	ssize_t			i;

	curr_buff_node = *buffer_list_ptr;
	curr_result = result;
	while (curr_buff_node->next != NULL)
	{
		i = 0;
		while (++i < curr_buff_node->size)
			curr_result[i] = curr_buff_node->start[i];
		curr_result += curr_buff_node->size;
		curr_buff_node = curr_buff_node->next;
	}
	i = 0;
	if (newline_pos == -1)
	{
		while (i < curr_buff_node->size)
			*(curr_result++) = curr_buff_node->start[i++];
		free_buffer_list(buffer_list_ptr, false);
	}
	else
	{
		while (i <= newline_pos)
			*(curr_result++) = curr_buff_node->start[i++];
		curr_buff_node->start += newline_pos + 1;
		curr_buff_node->size -= newline_pos + 1;
		free_buffer_list(buffer_list_ptr, true);
	}
	*curr_result = '\0';
}
