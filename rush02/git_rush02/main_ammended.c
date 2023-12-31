/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahim@42KL | drmsr <me@drmsr.dev>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 09:24:10 by mrahim@42KL |     #+#    #+#             */
/*   Updated: 2023/10/01 15:47:41 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>

char	***dict_array;

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	*ft_strcat(char *dest, char *src)
{
	int	target;
	int	run;

	target = 0;
	while (dest[target] != '\0')
	{
		target++;
	}
	run = 0;
	while (src[run] != '\0')
	{
		dest[target] = src[run];
		target++;
		run++;
	}
	dest[target] = '\0';
	return (dest);
}

void	init_dict(void)
{
	int	row;

	dict_array = (char ***) malloc(sizeof(char **) * 60);
	row = 0;
	while (row <= 50)
	{
		dict_array[row] = (char **)malloc(sizeof(char *) * 2);
		dict_array[row][0] = (char *)malloc(sizeof(char) * 48);
		dict_array[row][1] = (char *)malloc(sizeof(char) * 48);
		row++;
	}
}

int	load_dict(char *dict)
{
	int		dict_open;
	int		buffer_size;
	char	dict_buffer[4097];
	int		i;
	int		row;
	int		copy;
	char dict_path[20] = "./dict/";

	ft_strcat(dict_path,dict);
	if ((dict_open = open(dict_path, O_RDONLY)) == -1)
	{	
		printf("Error. Unable to locate file.");
		return (1);
	}
	if ((buffer_size = read(dict_open, dict_buffer, 4096)) == -1)
	{
		printf("Error. File not readable.");
		return (1);
	}
	dict_buffer[buffer_size] = '\0';
	i = 0;
	copy = 0;
	row = 0;
	while (i < buffer_size && row < 50)
	{
		copy = 0;
		while (dict_buffer[i] != ':')
		{
			/* clean up from dictionary : to skip whitespaces */
			/* ◦ You will trim the spaces before and after the value in the dictionary. */
			/* Syamirul todo */
			dict_array[row][0][copy] = dict_buffer[i]; 
			copy++;
			i++;
		}
		dict_array[row][0][copy] = '\0';
		i++;
		copy = 0;
		while (dict_buffer[i] != '\0' && ((dict_buffer[i] >= 9 && dict_buffer[i] <= 13) || dict_buffer[i] == 32)) 
			i++;
		while (dict_buffer[i] != '\n' && i < buffer_size)
		{
			dict_array[row][1][copy] = dict_buffer[i];
			copy++;
			i++;
		}
		dict_array[row][1][copy] = '\0';
		row++;
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	trim_trailing_whitespace(char *str)
{
	int	length;
	int	i;

	length = ft_strlen(str);
	i = length - 1;
	while (i >= 0 && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i--;
	str[i + 1] = '\0';
}

void	trim_dict(void)
{
	int	row;

	row = 0;
	while (row < 50)
	{
		trim_trailing_whitespace(dict_array[row][1]);
		row++;
	}
}

void	intro(void)
{
	DIR* dobj;
	struct dirent* dir;

	ft_putstr("====================================================\n");
	ft_putstr("|               42KL Proudly Presents              |\n");
	ft_putstr("|             Number To Word Dictionary            |\n");
	ft_putstr("====================================================\n");
	ft_putstr("Default Dictionary :\n     ");
	ft_putstr("numbers.dict");
	ft_putstr("\nAvailable Dictionaries :\n");
    dobj = opendir("./dict");

    if (dobj != NULL) 
	{
		while ((dir = readdir(dobj)) != NULL)
		{
			if (dir->d_name[0] == '.') 
			{
				if (dir->d_name[1] == '\0') continue;
        		if (dir->d_name[1] == '.') 
				{
            		if (dir->d_name[2] == '\0') continue;
				}
			}
			printf ("     %s\n", dir->d_name);
		}
		closedir(dobj);
	}
	ft_putstr("====================================================\n");
	ft_putstr("USAGE :\n");
	ft_putstr("    <dictionary> <number> // specified dictionary\n");
	ft_putstr("    nombor.dict 1234 (example)\n\n");
	ft_putstr("    <number> // default dictionary\n");
	ft_putstr("    1234 (example)\n");
	ft_putstr("====================================================\n");
	ft_putstr("LIMITATIONS :\n");
	ft_putstr("    Unfortunately within the timeframe, we are     \n");
	ft_putstr("    unable to make the program compute a number    \n");
	ft_putstr("    bigger than 999,999,999. \n");
	ft_putstr("====================================================\n");
	ft_putstr("               mrahim | aawgku-o | sting | kkhai-ki \n\n");
}

int	init_default_env(void)
{
	char	*default_dict;

	if ((default_dict = getenv("DEFAULT_DICT")) == NULL)
	{
		if ((setenv("DEFAULT_DICT", "numbers.dict", 0)) == -1)
		{
			printf("Unable to set default dictionary. Exiting program.");
			return (-1);
		}
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	diff;

	i = 0;
	diff = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		diff = s1[i] - s2[i];
		if (diff == 0)
		{
			i++;
		}
		else
		{
			return (diff);
		}
	}
	return (0);
}

int	check_input_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_number(char a)
{
	if (a >= 48 && a <= 57)
	{
		return (1);
	}
	return (0);
}

void	ft_construct_number(char *str, int *output)
{
	while (ft_check_number(*str) == 1)
	{
		if (*output == 0)
		{
			*output = (*str - '0');
		}
		else
		{
			*output = *output * 10 + (*str - '0');
		}
		str++;
	}
}

int	ft_atoi(char *str)
{
	unsigned int	counter;
	int				output;

	output = 0;
	counter = 0;
	while (*str != '\0')
	{
		if (*str == '-')
		{
			counter++;
		}
		if (ft_check_number(*str) == 1)
		{
			ft_construct_number(str, &output);
			break ;
		}
		str++;
	}
	if (counter % 2 != 0)
	{
		output = -output;
	}
	return (output);
}

int	length(long nb)
{
	int	length;

	length = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		length++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = length(n);
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

int	conversion(char *a)
{
	return (*a - '0');
}

int	count_zero(int level)
{
	if (level == 100)
		return (0);
	if (level == 1000)
		return (3);
	if (level == 1000000)
		return (6);
	return (1);
}

int	ft_print_denominator(long i)
{
	int	row;

	row = 0;
	while (row <= 50 && i != 0)
	{
		if (ft_strcmp(ft_itoa(i), dict_array[row][0]) == 0)
		{
			ft_putstr(dict_array[row][1]);
		}
		row++;
	}
	return (0);
}

void	print_sa(int n)
{
	int	row;

	row = 0;
	while (row <= 50 && n != 0)
	{
		if (ft_strcmp(ft_itoa(n), dict_array[row][0]) == 0)
		{
			ft_putstr(dict_array[row][1]);
		}
		row++;
	}
}

void	print_puluh(int n)
{
	int	row;

	row = 0;
	while (row <= 50 && n != 0)
	{
		if (ft_strcmp(ft_itoa(n), dict_array[row][0]) == 0)
		{
			ft_putstr(dict_array[row][1]);
		}
		row++;
	}
}

void	print_ratus(int n)
{
	int	row;

	n = n / 100;
	row = 0;
	while (row <= 50 && n != 0)
	{
		if (ft_strcmp(ft_itoa(n), dict_array[row][0]) == 0)
		{
			ft_putstr(dict_array[row][1]);
			ft_putstr(" ");
			ft_print_denominator(100);
		}
		row++;
	}
}

void	print_million(int n)
{
	int	row;

	n = n / 1000;
	row = 0;
	while (row <= 50 && n != 0)
	{
		if (ft_strcmp(ft_itoa(n), dict_array[row][0]) == 0)
		{
			ft_putstr(dict_array[row][1]);
			ft_putstr(" ");
			ft_print_denominator(1000000);
		}
		row++;
	}
}

void	print_belas(int pu, int sa)
{
	int	belas;
	int	row;

	if ((pu + sa) >= 11 && (pu + sa) <= 19)
	{
		belas = pu + sa;
		row = 0;
		while (row < 50)
		{
			if (ft_strcmp(ft_itoa(belas), dict_array[row][0]) == 0)
			{
				ft_putstr(dict_array[row][1]);
			}
			row++;
		}
	}
	else
	{
		print_puluh(pu);
		ft_putstr(" ");
		print_sa(sa);
	}
}

void	ft_print_belasratus(int sa, int pu, int ra)
{
	pu = pu * 10;
	ra = ra * 100;
	print_ratus(ra);
	ft_putstr(" ");
	print_belas(pu, sa);
}

void	init_print(char *input, int level)
{
	int	input_len;
	int	sa;
	int	pu;
	int	ra;

	input_len = ft_strlen(input);
	sa = input[input_len - (count_zero(level) + 1)] - '0';
	pu = input[input_len - (count_zero(level) + 2)] - '0';
	ra = input[input_len - (count_zero(level) + 3)] - '0';
	ft_print_belasratus(sa, pu, ra);
	ft_putstr(" ");
	ft_print_denominator(level);
	ft_putstr(" ");
}

void	init_print_base(char *input)
{
	int	input_len;
	int	sa;
	int	pu;
	int	ra;

	input_len = ft_strlen(input);
	sa = input[input_len - 1] - '0';
	pu = input[input_len - 2] - '0';
	ra = input[input_len - 3] - '0';
	ft_print_belasratus(sa, pu, ra);
	ft_putstr(" ");
	ft_putstr(" ");
}

int	main(int argc, char *argv[])
{
	char	*input;
	char	*ref_dict;
	long	raw;

	if (argc == 1)
	{
		intro();
		return (1);
	}
	if (argc < 2 || argc > 3)
	{
		ft_putstr("Please input 1 or 2 arguments.");
		return (1);
	}
	if (argc == 2)
	{
		input = argv[1];
		ref_dict = "numbers.dict";
	}
	if (argc == 3)
	{
		ref_dict = argv[1];
		input = argv[2];
	}
	if (check_input_number(input) == 0)
	{
		ft_putstr("Please enter only numbers.");
		return (1);
	}
	init_dict();
	if (load_dict(ref_dict) == 1)
	{
		free(dict_array);
		return (1);
	}
	trim_dict();
	raw = ft_atoi(input);
	if (raw > 999999999)
	{
		ft_putstr("Sorry we are not able to compute beyond this number.\n");
		free(dict_array);
		return (0);
	}
	if (raw > 999999)
	{
		init_print(input, 1000000);
	}
	if (raw > 999)
	{
		init_print(input, 1000);
	}
	init_print_base(input);
	free(dict_array);
	return (0);
}
