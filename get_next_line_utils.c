/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:44:42 by vmontoli          #+#    #+#             */
/*   Updated: 2023/09/03 21:27:10 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*DONE*/
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

/*DONE*/
t_buffer_node	*free_buffer_list(t_buffer_node **buffer_list_ptr,
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

char	*generate_empty_result(t_buffer_node *buffer_list)
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
	if (curr_buff_node->newline_pos == -1)
		size += curr_buff_node->size;
	else
		size += curr_buff_node->newline_pos + 1;
	return (malloc(size));
}

void	fill_result_tidy_buff_list(char *result,
			t_buffer_node **buffer_list_ptr)
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
	if (curr_buff_node->newline_pos == -1)
	{
		while (i < curr_buff_node->size)
			*(curr_result++) = curr_buff_node->start[i++];
		free_buffer_list(buffer_list_ptr, false);
	}
	else
	{
		while (i <= curr_buff_node->newline_pos)
			*(curr_result++) = curr_buff_node->start[i++];
		curr_buff_node->start += curr_buff_node->newline_pos + 1;
		curr_buff_node->size -= curr_buff_node->newline_pos + 1;
		free_buffer_list(buffer_list_ptr, true);
	}
	*curr_result = '\0';
}
