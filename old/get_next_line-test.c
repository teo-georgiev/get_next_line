#include "get_next_line-test.h"
#include <stdio.h>

t_list	*find_last_node(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;
	int		char_rem;

	if (*list == NULL)
		return (0);
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	char_rem = ft_strlen(clean_node->str_buf);
	if (clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
	return (char_rem);
}

int	polish_list(t_list **list)
{
	/* This is a function that is suppose to reset the list. It gets all the characters that are left 
	 * behind the nl character and assigns them to a new node. The the list is being freed and the 'clean node'
	 * is being added as it's first node. */
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean_node)
		return (0);
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while(last_node->str_buf[i] != '\0' \
		&& last_node->str_buf[i] != '\n')
		++i;
	while(last_node->str_buf[i] != '\0' \
		&& last_node->str_buf[++i])
		buf[j++] = last_node->str_buf[i];
	buf[j] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	return (dealloc(list, clean_node, buf));
}

int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (0);
}

void	copy_str(t_list *list, char *str)
{
	// Index for traversing the chars in the list's nodes
	int	i;
	// Index for the new string
	int	j;

	// Check if the list is empty
	if (list == NULL)
		return ;
	// initialise outsize the loop because we are returning a single string
	j = 0;
	// Loop for traversing the nodes of the list.
	// Nested loops are needed to get all chars from the list's nodes
	while (list)
	{
		// Set index to zero, as we'll have to go through the chars of separate nodes' strings
		i = 0;
		// Loop until we reach the end of a node's content
		while (list->str_buf[i])
		{
			// Check if a character is a newline char
			if (list->str_buf[i] == '\n')
			{
				// if it is, ass a nl character to the string and increase by one 
				str[j++] = '\n';
				// Add a terminating zero
				str[j] = '\0';
				// Exit function
				return ;
			}
			// sles add the character if the node's content to the string and increate indexes
			str[j++] = list->str_buf[i++];
		}
		// Move to the next node of the list
		list = list->next;
	}
	// Add a terminating zero (that's in case the nl char is the last one in the list)
	str[j] = '\0';
}

char	*get_line(t_list * list)
{
	// Variable for the length of the string
	int		str_len;
	// Variable for the new line that is to be returned
	char	*next_line;

	// Check if list is empty
	if (list == NULL)
		return (NULL);
	// Str_len gets the length of the characters uptill the newline character.
	str_len = len_to_newline(list);
	// Then the str_len is going to be used for allocating memory for the returned line of text
	next_line = malloc(str_len + 1);
	// Check if allocation has been successful
	if (next_line == NULL)
		return (NULL);
	// if so, copy the characters from list to the new line
	copy_str(list, next_line);
	// Return the populated new line
	return (next_line);
}

int	found_newline(t_list *list)
{
	// Index variable for traversing through buf string
	int	i;

	// Check if list is empty. If it's empty the loop in the outer function can continue cause 
	// no newline character has been found
	if (list == NULL)
		return (0);
	// While list has not reached its end, iterate through it 
	while (list)
	{
		// Initialise the index
		i = 0;
		// Go through node content and check if there are any new characters,
		// or if the node has no newline chars (i.e. a line is longer than BUFFER_SIZE)
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			// If there's a newline character, return 1
			if (list->str_buf[i] == '\n')
				return (1);
			// Else continue through the string content of the node
			++i;
		}
		// Move on to the next node
		list = list->next;
	}
	// If there are no new characters, continue looping in the outer function
	return (0);
}

void	append(t_list **list, char *buf)
{
	// Create list node new_node
	// Create list node last_node
	t_list	*new_node;
	t_list	*last_node;

	// Traverse the linked list to find its last node
	last_node = find_last_node(*list);
	// Allocate the new_node to be he size of a t_list node
	new_node = malloc(sizeof(t_list));
	// Perform checks if the new_node has been successfully allocated space in the memory
	if (new_node == NULL)
		return ;
	// Check if the last_node is NULL, meaning that this is the first node of the list
	// and if so, assign the new node to be the head of the list
	if (last_node == NULL)
		*list = new_node;
	else
	// If not, assign the last node of the list to connect to the new node
		last_node->next = new_node;
	// Give the new_node's content the content of the buffer
	new_node->str_buf = buf;
	// Link the next node to be NULL making the new_node the last one in the list
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd, int char_rem)
{
	// Variable for the number of read characters
	int		char_read;
	// Buffer variable
	char	*buf;

	// Perform loop while there is no newline character in the read chunks of text 
	// ( 0: no newline; 1: newline present)
	// The loop goes mandatory through at least one iteration, when there might already be a newline character
	while(!found_newline(*list))
	{
		// Memory allocation of the buffer variable based on the BUFFER_SIZE
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		// Assign char_read the number of read characters as returned by the read() function
		// Fill the buf string with the read characters 
		char_read = read(fd, buf, BUFFER_SIZE - char_rem);
		// Check if char_read is == 0. If it is, that means there's an issue, the buffer should be 
		// freed and the program should be exited.
		if (!char_read)
		{
			free(buf);
			return ;
		}
		// Last character of the string of read characters is 0.
		buf[char_read] = '\0';
		// Append buf with read characters to the linked list
		append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	// Static variable that will contain all the chunks of read bytes.
	static t_list	*list;
	static int		char_rem;
	// The variable that should returned the constructed next line.
	char			*next_line;

	// Check if the fd is less then 0, i.e. error
	// Check if BUFFER_SOZE is less than or equal to zero, i.e. there would be nothing read
	// Check if there's an error with the read function
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	// Create the linked list of read chunks of text
	create_list(&list, fd, char_rem);
	// Check if there has been any issues with the new created list
	// The list is suppose to contain the read bytes
	if (list == NULL)
		return (NULL);
	// Create the next line that the function is suppose to return
	next_line = get_line(list);
	// Clear the list but leave the remaining characters that were after the nl char
	char_rem = polish_list(&list);
	return (next_line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		lines;
	
// 	lines = 1;
// 	fd = open("bible.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 		printf("%d->%s\n", lines++, line);
// 	return (0);
// }
