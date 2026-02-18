#include <stdio.h>
#include <stdlib.h>

void	print_res(int *res, int pos_res)
{
	int	index;

	index = 0;
	while (index < pos_res)
	{
		printf("%d", res[index]);
		if (index < pos_res - 1)
			printf(" ");
		index++;
	}
	printf("\n");
}
void	powerset(int *nums, int *res, int len, int pos, int pos_res, int total,
		int n, int *bandera_encontrados)
{
	if (pos == len)
	{
		if (total == n)
		{
			print_res(res, pos_res);
			*bandera_encontrados = 1;
		}
		return ;
	}
	res[pos_res] = nums[pos];
	powerset(nums, res, len, pos + 1, pos_res + 1, total + nums[pos], n, bandera_encontrados);
	powerset(nums, res, len, pos + 1, pos_res, total, n, bandera_encontrados);
}

int	main(int argc, char *argv[])
{
	int	n;
	int	*nums;
	int	*res;
	int	index;
	int	len;
	int	bandera_encontrados;

	if (argc < 3)
		return (1);
	n = atoi(argv[1]);
	len = argc - 2;
	index = 0;
	bandera_encontrados = 0;
	nums = (int *)malloc(len * sizeof(int));
	res = (int *)malloc(len * sizeof(int));
	while (index < len)
	{
		nums[index] = atoi(argv[index + 2]);
		index++;
	}
	powerset(nums, res, len, 0, 0, 0, n, &bandera_encontrados);
	if(!bandera_encontrados)
		printf("\n");
	free(nums);
	free(res);
	return (0);
}
