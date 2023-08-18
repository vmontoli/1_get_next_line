/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:40:30 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/18 11:34:29 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer_list	*buffer_list = buffer_list_new();
	t_buffer_list			*curr_buffer_l;
	char					*newline_ptr;

	if (buffer_list == NULL)
		return (NULL);
	curr_buffer_l = buffer_list;
	while ()//
	{
		newline_ptr = find_new_line(curr_buffer_l->start, curr_buffer_l->end);
		if (newline_ptr != NULL)
			return (generate_result(&buffer_list, curr_buffer_l, newline_ptr));

}
