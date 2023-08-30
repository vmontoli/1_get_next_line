/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:40:30 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/30 09:59:12 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer_node	*buffer_list = NULL;
	t_buffer_node			*curr_buff_node;
	ssize_t					newline_pos;

	if (buffer_list == NULL)
		buffer_list = new_buffer_node(fd);
	curr_buff_node = buffer_list;
	while (curr_buff_node != NULL)
	{
		newline_pos = find_newline_pos(curr_buff_node);
		if (newline_pos != -1 || curr_buff_node->size < BUFFER_SIZE)
			return (generate_result(&buffer_list, newline_pos));
		curr_buff_node->next = new_buffer_node(fd);
		curr_buff_node = curr_buff_node->next;
	}
	return (free_buffer_list(&buffer_list, false));
}
