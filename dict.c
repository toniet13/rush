void	dict_init(t_str *dict, int file, int nlines)
{
	int		i;
	int		j;
	char	temp[1];

	j = 0;
	i = 0;
	while (i < nlines)
	{
		read(file, &temp[0], 1);
		while (!ft_is_num(temp[0]))
			read(file, &temp[0], 1);
		while (ft_is_num(temp[0]))
		{
			dict[i].nbr[j++] = temp[0];
			read(file, &temp[0], 1);
		}
		while (temp[0] != ':')
			read(file, &temp[0], 1);
		j = 0;
		read(file, &temp[0], 1);
		while (temp[0] == ' ')
			read(file, &temp[0], 1);
		while (temp[0] != '\n')
		{
			dict[i].word[j++] = temp[0];
			read(file, &temp[0], 1);
		}
		ft_strcpy(dict[i].nbr, ft_rm_zero(dict[i].nbr));
		i++;
		j = 0;
	}
}