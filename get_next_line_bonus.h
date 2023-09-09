/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 08:29:43 by vmontoli          #+#    #+#             */
/*   Updated: 2023/09/09 06:20:02 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>		//NULL, size_t
# include <stdbool.h>		//bool, true, false

# include <stdlib.h>		//malloc(), free()
# include <unistd.h>		//read()

/*****/

//If BUFFER_SIZE is defined, but is empty (compiler flag left without value),
// undefine it (so default value is used).
//StackOverflow magic, I know, but makes sense.
// Was useful during my development.
# if ~(~BUFFER_SIZE + 0) == 0 && ~(~BUFFER_SIZE + 1) == 1
#  undef BUFFER_SIZE
# endif

//Default value of BUFFER_SIZE if it is not defined at compile time
// (or it is defined but empty).
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

//If BUFFER_SIZE is negative or zero, throw error at compile time.
# if BUFFER_SIZE <= 0
#  error "Negative or 0 '-D BUFFER_SIZE=<value>' value passed at compilation"
# endif

//Cannot control being a numeric value because the way the preprocessor works,
// except if I try to overengineer it.
//
// 'stringinzing' the BUFFER_SIZE macro value
// (https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html)
// and somehow making it to be a 'integer constant expression' at compile time
// for the _Static_assert
// (https://en.cppreference.com/w/c/language/_Static_assert)
// (maybe at least 'sizeof(#BUFFER_SIZE) <= sizeof(size_t)'?)
//
// So, I hope you don't fail me because of this, because if not...
// Quite soooo obscure testing are you doing, don't you?

/*****/

typedef struct s_buffer_node
{
	char					buffer[BUFFER_SIZE];
	char					*start;
	size_t					size;
	bool					has_eof;
	bool					has_newline;
	size_t					newline_pos;
	struct s_buffer_node	*next;
}	t_buffer_node;

/***/
char	*get_next_line(int fd);
/***/

void	set_newline_pos(t_buffer_node *buff_node);

void	tidy_buff_list(t_buffer_node **buffer_list_ptr);

char	*generate_result(t_buffer_node *buffer_list);

/**/

void	new_buffer_node(int fd, t_buffer_node **prev);

void	*free_buffer_list(t_buffer_node **buffer_list_ptr, bool maintain_last);

size_t	copy_buff_node_to_str(t_buffer_node *curr_buff_node, char *str);

#endif
