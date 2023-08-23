/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:40:30 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/23 16:39:53 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer_list	*buffer_list = NULL;
	t_buffer_list			*curr_buff_node;
	char					*newline_ptr;

	if (buffer_list == NULL)
		buffer_list = (t_buffer_list *) ft_calloc(1, sizeof(t_buffer_list));
	if (buffer_list == NULL)
		return (NULL);
	curr_buff_node = buffer_list;
	while (true)
	{
		fill_buffer(fd, curr_buff_node);
		newline_ptr = find_new_line(curr_buff_node);
		if (newline_ptr == NULL)

		else
			return (generate_result(&buffer_list, newline_ptr));
	}
}
