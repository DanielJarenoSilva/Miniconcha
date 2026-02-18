#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_write(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_write(str[i], fd);
		i++;
	}
	return (i);
}

int	ft_read_echo(char **str)
{
	int		len;
	int		bytes_read;
	char	c;
	char	*buf;
	char	*tmp;

	len = 0;
	buf = NULL;
	while ((bytes_read = read(0, &c, 1)) > 0)
	{
		tmp = realloc(buf, len + 2);
		buf = tmp;
		buf[len++] = c;
		buf[len] = '\0';
		*str = buf;
	}
	return (len);
}

static int	ft_compare_str(char *input, char *filter)
{
	int	i;

	i = 0;
	while (filter[i])
	{
		if (input[i] == '\0' || input[i] != filter[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_filter(char *input_read, char *filter)
{
	int	i;
	int	flen;
	int	k;

	flen = ft_strlen(filter);
	i = 0;
	while (input_read[i] != '\0')
	{
		if (input_read[i] == '\n')
		{
			ft_write(input_read[i], 1);
			i++;
			continue ;
		}
		if (ft_compare_str(&input_read[i], filter))
		{
			k = 0;
			while (k < flen)
			{
				ft_write('*', 1);
				k++;
			}
			i += flen;
			continue ;
		}
		ft_write(input_read[i], 1);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*input;

	if (argc < 2)
		return (1);
	if (ft_strlen(argv[1]) < 1)
		return (ft_write('\n', 1));
	ft_read_echo(&input);
	ft_filter(input, argv[1]);
	free(input);
	return (0);
}
