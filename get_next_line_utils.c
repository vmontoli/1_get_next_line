/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:44:42 by vmontoli          #+#    #+#             */
/*   Updated: 2023/09/04 23:32:44 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*generate_result(t_buffer_node *buffer_list)
{
	size_t			i;
	t_buffer_node	*curr_buff_node;
	char			*result;
	char			*curr_result;

	i = 1;
	curr_buff_node = buffer_list;
	while (curr_buff_node != NULL)
	{
		i += copy_buff_node_to_str(curr_buff_node, NULL);
		curr_buff_node = curr_buff_node->next;
	}
	result = (char *) malloc(i * sizeof(char));
	if (result == NULL)
		return (NULL);
	curr_result = result;
	curr_buff_node = buffer_list;
	while (curr_buff_node != NULL)
	{
		i = copy_buff_node_to_str(curr_buff_node, curr_result);
		curr_result += i;
		curr_buff_node = curr_buff_node->next;
	}
	*curr_result = '\0';
	return (result);
}

/*
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

char	*generate_result(t_buffer_node *buffer_list)
{

}
*/

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
