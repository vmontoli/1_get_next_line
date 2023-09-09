/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 08:31:08 by vmontoli          #+#    #+#             */
/*   Updated: 2023/09/09 06:19:16 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	new_buffer_node(int fd, t_buffer_node **prev_ptr)
{
	t_buffer_node	*buff_node;
	ssize_t			bytes_read;

	buff_node = malloc(sizeof(t_buffer_node));
	if (buff_node == NULL)
		return ;
	bytes_read = read(fd, buff_node->buffer, BUFFER_SIZE);
	if (bytes_read == -1 || bytes_read == 0)
	{
		if (bytes_read == 0 && *prev_ptr != NULL)
			(*prev_ptr)->has_eof = true;
		else
			*prev_ptr = NULL;
		free(buff_node);
		return ;
	}
	if (*prev_ptr != NULL)
		(*prev_ptr)->next = buff_node;
	buff_node->start = buff_node->buffer;
	buff_node->has_eof = bytes_read < BUFFER_SIZE;
	buff_node->size = (size_t) bytes_read;
	buff_node->next = NULL;
	*prev_ptr = buff_node;
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

size_t	copy_buff_node_to_str(t_buffer_node *curr_buff_node, char *str)
{
	size_t	i;
	size_t	len_to_copy;

	if (curr_buff_node->has_newline)
		len_to_copy = curr_buff_node->newline_pos + 1;
	else
		len_to_copy = curr_buff_node->size;
	if (str != NULL)
	{
		i = 0;
		while (i < len_to_copy)
		{
			str[i] = curr_buff_node->start[i];
			i++;
		}
	}
	return (len_to_copy);
}
