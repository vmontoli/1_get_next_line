/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:36:04 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/21 19:06:23 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stddef.h>		//NULL, size_t
# include <stdbool.h>		//bool, true, false

# include <stdlib.h>		//malloc(), free()
# include <unistd.h>		//read()

typedef struct s_buffer_list
{
	char					buffer[BUFFER_SIZE];
	char					*start;
	char					*end;
	struct s_buffer_list	*next;
}	t_buffer_list;

char			*get_next_line(int fd);

char			*find_new_line(char *start_str, char *end_str);

char			*generate_result(t_buffer_list **buffer_list_ptr,
					char *newline_ptr);

#endif
