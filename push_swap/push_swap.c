/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateow <ateow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 03:19:09 by ateow             #+#    #+#             */
/*   Updated: 2023/09/27 03:19:11 by ateow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(int *stack_a)
{
	if (stack_a[0] > stack_a[1])
		swap_a(stack_a, 2);
}

void	sort_three(int *stack_a)
{
	if (is_largest(stack_a, stack_a[2], 3) == 1) // if last number is the biggest
	{
		if (stack_a[0] > stack_a[1])
			swap_a(stack_a, 3);
	}
	else if (is_smallest(stack_a, stack_a[2], 3) == 1) // if last number is the smallest
	{
		if (stack_a[0] > stack_a[1])
			swap_a(stack_a, 3);
		rot_down_a(stack_a, 3);
	}
	else
	{
		if (stack_a[0] < stack_a[1])
			swap_a(stack_a, 3);
		rot_up_a(stack_a, 3);
	}
}

void	sort_four(int *stack_a, int count_a, int *stack_b, int count_b)
{
	if (is_smallest(stack_a, stack_a[0], 4) == 1 // if first number is smallest 
		|| is_largest(stack_a, stack_a[0], 4) == 1) // if first number is largest
	{
		push_a(stack_a, &count_a, stack_b, &count_b);
		sort_three(stack_a);
		push_b(stack_b, &count_b, stack_a, &count_a);
		if (is_largest(stack_a, stack_a[0], 4) == 1) // if first number is largest
			rot_up_a(stack_a, 4);
	}
	else if (is_largest(stack_a, stack_a[3], 4) == 1 // if last numner is largest
		|| is_smallest(stack_a, stack_a[3], 4) == 1) // if last number is smallest
	{
		rot_down_a(stack_a, 4);
		if (is_sorted(stack_a, count_a) == 1)
			return ;
		push_a(stack_a, &count_a, stack_b, &count_b);
		sort_three(stack_a);
		push_b(stack_b, &count_b, stack_a, &count_a);
		if (is_largest(stack_a, stack_a[0], 4) == 1) // if first number is largest
			rot_up_a(stack_a, 4);
	}
	else // if 1 and 4 are in the middle
	{
		rot_up_a(stack_a, 4);
		push_a(stack_a, &count_a, stack_b, &count_b);
		sort_three(stack_a);
		push_b(stack_b, &count_b, stack_a, &count_a);
		if (is_largest(stack_a, stack_a[0], 4) == 1)
			rot_up_a(stack_a, 4);
	}
}

void	sort_five(int *stack_a, int count_a, int *stack_b, int count_b)
{
	if (is_smallest(stack_a, stack_a[0], 5) == 1 // if first number is smallest 
		|| is_largest(stack_a, stack_a[0], 5) == 1) // if first number is largest
	{
		push_a(stack_a, &count_a, stack_b, &count_b);
		sort_four(stack_a, count_a, stack_b, count_b);
		push_b(stack_b, &count_b, stack_a, &count_a);
		if (is_largest(stack_a, stack_a[0], 5) == 1) // if first number is largest
			rot_up_a(stack_a, 5);
	}
	else if (is_largest(stack_a, stack_a[4], 5) == 1 // if last numner is largest
		|| is_smallest(stack_a, stack_a[4], 5) == 1) // if last number is smallest
	{
		rot_down_a(stack_a, 5);
		if (is_sorted(stack_a, count_a) == 1)
			return ;
		push_a(stack_a, &count_a, stack_b, &count_b);
		sort_four(stack_a, count_a, stack_b, count_b);
		push_b(stack_b, &count_b, stack_a, &count_a);
		if (is_largest(stack_a, stack_a[0], 5) == 1) // if first number is largest
			rot_up_a(stack_a, 5);
	}
	else // if 1 and 5 are in the middle
	{
		if (is_smallest(stack_a, stack_a[1], 5) == 1
		|| is_largest(stack_a, stack_a[1], 5) == 1) // if second number is not smallest, can skip rot_downx2
			rot_up_a(stack_a, 5); 			
		else if (is_smallest(stack_a, stack_a[3], 5) == 1 // if forth number is smallest 
		|| is_largest(stack_a, stack_a[3], 5) == 1) // or if forth number is largest
		{
			rot_down_a(stack_a, 5); 
			rot_down_a(stack_a, 5);
		}
		if (is_sorted(stack_a, count_a) == 1)
			return ;
		push_a(stack_a, &count_a, stack_b, &count_b); 
		sort_four(stack_a, count_a, stack_b, count_b);
		push_b(stack_b, &count_b, stack_a, &count_a);
		if (is_largest(stack_a, stack_a[0], 5) == 1)
			rot_up_a(stack_a, 5);
	}
}

void	move_small_to_b(int *stack_a, int *count_a, int *stack_b, int *count_b, int chunk_size)
{
	int	i;
	int	j;
	int	k;
	int	*smallest_arr;

	smallest_arr = find_smallest_numbers(stack_a, *count_a, chunk_size);
	i = 0;
	k = 0;
	while (i < *count_a + *count_b)
	{
		//printf("i:%d\n",i);
		j = 0;
		while (j < chunk_size && k < chunk_size)
		{
			//printf("j:%d\n",j);
			//printf("stack_a[0]: %d    smallest_arr[j]: %d\n",stack_a[0],  smallest_arr[j]);
			if (stack_a[0] == smallest_arr[j])
			{
			//	printf("found same\n");
				push_a(stack_a, count_a, stack_b, count_b);
				//if (stack_b[0] < stack_b[10])
				//	swap_b(stack_b, *count_b);
				k++;
				j = -1;
			}
			j++;
		}
		if (k == chunk_size)
			break ;
		rot_up_a(stack_a, *count_a);
		i++;
	}
	free(smallest_arr);
	//print_stack(stack_a, *count_a, stack_b, *count_b);
}

void	return_to_a(int *stack_a, int *count_a, int *stack_b, int *count_b)
{
	int	i;
	int	l;

	i = *count_b;
	while (i > 0)
	{
		l = find_largest_index(stack_b, *count_b);
		if (l == 0)
		{
			push_b(stack_b, count_b, stack_a, count_a);
			i--;
		}
		else if (l < (*count_b - l))
			rot_up_b(stack_b, *count_b);
		else if (l > (*count_b - i))
			rot_down_b(stack_b, *count_b);

	}
	//print_stack(stack_a, *count_a, stack_b, *count_b);
}

void	chuck_sort(int *stack_a, int count_a, int *stack_b, int count_b, int chunk_size)
{
	int	loop;

	loop = count_a / chunk_size;
	if ((count_a % chunk_size) != 0)
		loop++;
//	printf("counta:%d, chunk:%d, loop:%d\n", count_a, chunk_size, loop);
	while (count_a > 0)
		move_small_to_b(stack_a, &count_a, stack_b, &count_b, chunk_size);
	return_to_a(stack_a, &count_a, stack_b, &count_b);
	//print_stack(stack_a, count_a, stack_b, count_b);
}

int	main(int argc, char **argv)
{
	int	*stack_a;
	int	*stack_b;
	int	count_a;
	int	count_b;
	int	i;

	count_a = argc - 1;
	count_b = 0;
//CHECK ERROR
	if (is_error((argv + 1), count_a) == 1)
		return (0);
	if ((argc - 1) < 2)
		return (ft_atoi(argv[1]));
//INIT & SORT
	stack_a = malloc(sizeof(int) * (argc - 1));
	stack_b = malloc(sizeof(int) * (argc - 1));
	i = 0;
	while (i < count_a)
	{
		stack_a[i] = ft_atoi(argv[i + 1]);
		i++;
	}
// ALGO
	if (is_sorted(stack_a, count_a) == 0)
	{
		if (count_a == 2)
			sort_two(stack_a);
		else if (count_a == 3)
			sort_three(stack_a);
		else if (count_a == 4)
			sort_four(stack_a, count_a, stack_b, count_b);
		else if (count_a == 5)
			sort_five(stack_a, count_a, stack_b, count_b);
		else if (count_a == 500)
			chuck_sort(stack_a, count_a, stack_b, count_b, 70);
		else
			chuck_sort(stack_a, count_a, stack_b, count_b, 20);
	}

//PRINTING STACK
	//print_stack(stack_a, count_a, stack_b, count_b);
//FREE
	free(stack_a);
	free(stack_b);
}
/*
	swap_a(stack_a, count_a);
	swap_b(stack_b, count_b);
	push_a(stack_a, &count_a, stack_b, &count_b);
	push_b(stack_b, &count_b, stack_a, &count_a);
	rot_up_a(stack_a, count_a);
	rot_up_b(stack_b, count_b);
	rot_up_ab(stack_a, count_a, stack_b, count_b);
	rot_down_a(stack_a, count_a);
	rot_down_b(stack_b, count_b);
	rot_down_ab(stack_a, count_a, stack_b, count_b);
	printf("%d\n", smallest_arr[0]);
	printf("%d\n", smallest_arr[1]);
	printf("%d\n", smallest_arr[2]);
	printf("%d\n", smallest_arr[3]);
	printf("%d\n", smallest_arr[4]);
*/
