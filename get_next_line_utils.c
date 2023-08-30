/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:44:42 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/30 09:59:30 by vmontoli         ###   ########.fr       */
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

static char	*generate_empty_result(t_buffer_node **buffer_list_ptr,
			ssize_t newline_pos)
{
	ssize_t			size;
	t_buffer_node	*curr_buff_node;

	curr_buff_node = *buffer_list_ptr;
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

char	*generate_result(t_buffer_node **buffer_list_ptr, ssize_t newline_pos)
{
	char			*result;
	t_buffer_node	*curr_buff_node;
	char			*curr_result;

	result = generate_empty_result(buffer_list_ptr, newline_pos);
	if (result == NULL)
		return (free_buffer_list(buffer_list_ptr, false));
	curr_buff_node = *buffer_list_ptr;
	curr_result = result;
	while (curr_buff_node->next != NULL)
	{
		//TODO: STRNCPY
		curr_buff_node = curr_buff_node->next;
	}
	//TODO: IFS, STRNCPY W/ MOVING LAST SIZE & START
	*curr_result = '\0';
	free_buffer_list(buffer_list_ptr, true);
	return (result);
}
//TODO: sin 25 lineas, sin 5 funcs

/*
//TODO: revisar y explain
char	*generate_result(t_buffer_node **buffer_list_ptr, char *newline_ptr)
{
	char			*result;
	char			*curr_result;
	ssize_t			len;
	t_buffer_node	*doing_buffer_l;

	len = 1;
	doing_buffer_l = *buffer_list_ptr;
	while (doing_buffer_l->next != NULL)
	{
		len += doing_buffer_l->end - doing_buffer_l->start + 1;
		doing_buffer_l = doing_buffer_l->next;
	}
	len += newline_ptr - doing_buffer_l->start + 1;
	result = (char *) malloc(len);
	if (result == NULL)
	{
		*buffer_list_ptr = NULL;
		return (NULL);
	}
	result[len - 1] = '\0';
	curr_result = result;
	doing_buffer_l = *buffer_list_ptr;
	while (doing_buffer_l->next != NULL)
	{
		ft_strncpy(curr_result, doing_buffer_l->start,
			doing_buffer_l->end - doing_buffer_l->start + 1);
		curr_result += doing_buffer_l->end - doing_buffer_l->start + 1;
		doing_buffer_l = doing_buffer_l->next;
	}
	ft_strncpy(curr_result, doing_buffer_l->start,
		newline_ptr - doing_buffer_l->start + 1);
}
*/
