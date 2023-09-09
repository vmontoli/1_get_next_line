/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 08:28:41 by vmontoli          #+#    #+#             */
/*   Updated: 2023/09/09 06:18:25 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_buffer_node	*buffer_list = NULL;
	t_buffer_node			*curr_buff_node;
	char					*result;

	if (fd < 0 || read(fd, NULL, 0) == -1)
		return (free_buffer_list(&buffer_list, false));
	if (buffer_list == NULL)
		new_buffer_node(fd, &buffer_list);
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
		new_buffer_node(fd, &curr_buff_node);
	}
	return (free_buffer_list(&buffer_list, false));
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
