/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:44:42 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/18 11:34:27 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buffer_list	*buffer_list_new(void)
{
	t_buffer_list	*res;

	res = (t_buffer_list *) malloc(t_buffer_list);
	if (res == NULL)
		return (NULL);
	res->buffer = (char *) malloc(BUFFER_SIZE);
	if (res->buffer == NULL)
		return (NULL);
	res->start = NULL;
	res->end = NULL;
	res->next = NULL;
	return (res);
}

//TODO: explain
char	*find_new_line(char *start_str, char *end_str)
{
	char	*result;

	result = start_str;
	while (result != end_str)
	{
		if (*result == '\n')
			return (result);
		result++;
	}
	return (NULL);
}

char	*generate_result(t_buffer_list **buffer_list_ptr,
			t_buffer_list *curr_buffer_l, char *newline_ptr)
{
	char			*result;
	ssize_t			len;
	t_buffer_list	doing_buffer_l;
}


