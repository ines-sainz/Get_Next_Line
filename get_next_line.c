/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:01:03 by isainz-r          #+#    #+#             */
/*   Updated: 2024/05/26 12:06:04 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Extracts the remainder of a string after the first newline.
 * 
 * This function searches for the first newline character in `aux`. If found,
 * it returns a newly allocated substring starting just after the newline to
 * the end of the string. If no newline exists, it returns an empty string.
 * The original string `aux` is freed before returning.
 * 
 * @param aux The input null-terminated string to process. Must be malloc'd.
 * 
 * @return Pointer to the newly allocated remainder substring, or NULL on
 *         allocation failure. The original string is freed in all cases.
 */
char	*ft_aux(char *aux)
{
	int		i;
	int		j;
	char	*new_aux;

	j = 0;
	i = 0;
	while (aux[j] != '\0')
		j++;
	while (aux[i] != '\n' && aux[i] != '\0')
		i++;
	if (aux[i] == '\n')
		i++;
	new_aux = ft_substr(aux, i, j);
	if (!new_aux)
		return (free(aux), NULL);
	free(aux);
	return (new_aux);
}

/**
 * @brief Extracts the first line from the input string, including newline.
 * 
 * This function returns a newly allocated string containing characters from
 * the start of `aux` up to and including the first newline character (`\n`).
 * If no newline is found, it returns a copy of the entire string.
 * 
 * @param aux The input null-terminated string to extract the line from.
 * 
 * @return Pointer to the newly allocated line string, or NULL if allocation
 *         fails.
 */
char	*ft_line(char *aux)
{
	int		i;
	char	*line;

	i = 0;
	while (aux[i] != '\n' && aux[i] != '\0')
		i++;
	if (aux[i] == '\n')
		i++;
	line = ft_substr(aux, 0, i);
	if (!line)
		return (0);
	return (line);
}

/**
 * @brief Reads from file descriptor until a newline or EOF is found.
 * 
 * This function reads from the file descriptor `fd` into a buffer of size
 * BUFFER_SIZE, appending the data to `text` until a newline is found or EOF.
 * On error, it frees `text` and returns NULL. On EOF, returns the accumulated
 * `text`. Uses helper functions ft_strchr, ft_strjoin, and ft_calloc.
 * 
 * @param fd The file descriptor to read from.
 * @param text The current text buffer, may be NULL initially.
 * 
 * @return Pointer to the updated text buffer containing read data, or NULL
 *         on error.
 */
char	*ft_read(int fd, char *text)
{
	int		n_bytes;
	char	*buffer;
	char	*aux;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	n_bytes = 1;
	while (!ft_strchr(text, '\n') && n_bytes)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes < 0)
			return (free(buffer), free(text), NULL);
		if (n_bytes == 0)
			return (free(buffer), text);
		buffer[n_bytes] = '\0';
		aux = text;
		text = ft_strjoin(text, buffer);
		free(aux);
	}
	free(buffer);
	buffer = NULL;
	return (text);
}

/**
 * @brief Reads and returns the next line from a file descriptor.
 * 
 * This function manages an internal static buffer `text` to accumulate data
 * from `fd`. It reads more data if necessary, then extracts the next line
 * including the newline character, and updates the internal buffer.
 * Returns NULL on error or if no more lines are available.
 * 
 * @param fd The file descriptor to read the next line from.
 * 
 * @return Pointer to a newly allocated string containing the next line, or
 *         NULL if there is nothing more to read or on error.
 */
char	*get_next_line(int fd)
{
	static char	*text = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	text = ft_read(fd, text);
	if (!text)
		return (text = NULL, NULL);
	if (!text[0])
		return (free(text), text = NULL, NULL);
	line = ft_line(text);
	if (!line)
		return (free(text), text = NULL, NULL);
	text = ft_aux(text);
	return (line);
}
