/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:41:57 by aalhalab          #+#    #+#             */
/*   Updated: 2024/04/29 17:51:41 by aalhalab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Node
{
	int number;
	int index;
	int moves;
	struct Node *next;
}Node;
void swap_a(Node **a);
void rotate_a(Node **a);
void push_a(Node **a, Node **b);
void push_b(Node **a, Node **b);
void printNode(Node *a);
Node *create_stack_a(char **av);
int is_sorted(Node *a);
int check_first_largest_second_smallest(Node *a);
void rotate_and_swap(Node **a);
void if_dublicate(Node *a);
void bubble_sort(Node **a);
Node* copy_stack(Node* a);
void assign_indix(Node* a);
void free_stack(Node* a);
void indexify(Node **a);
int	ft_stack_size(Node *head);
void	ft_radix_sort(Node **stack_a, Node **stack_b);

void swap_a(Node **a)
{
	Node *tmp;
	Node *tmp2;
	Node *tmp3;

	if (!(*a) || !(*a)->next)               
		return;
	tmp = *a;
	tmp2 = tmp->next;
	tmp3 = tmp2->next;
	*a = tmp2;
	tmp2->next = tmp;
	tmp->next = tmp3;
	write(1,"sa\n",3);
}
void rotate_a(Node **a)
{
	Node *tmp;
	Node *tmp2;

	if (!(*a) || !(*a)->next)
		return;
	tmp = *a;
	tmp2 = tmp->next;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = *a;
	*a = tmp->next;
	tmp->next = NULL;
	write(1,"ra\n",3);
}
void push_a(Node **a, Node **b)
{
	Node *tmp;

	if (!(*b))
		return;
	tmp = *b;
	*b = (*b)->next;
	tmp->next = *a;
	*a = tmp;
	write(1,"pa\n",3);
}
void push_b(Node **a, Node **b)
{
	Node *tmp;

	if (!(*a))
		return;
	tmp = *a;
	*a = (*a)->next;
	tmp->next = *b;
	*b = tmp;
	write(1,"pb\n",3);
}
void printNode(Node *a)
{
	while (a)
	{
		printf("%d ", a->number);
		a = a->next;
	}
	write(1,"\n",1);
}
Node *create_stack_a(char **av)
{
	Node *a = NULL;
	Node *end = NULL;
	int i;
	
	i = 1;
	while (av[i]) 
	{
		Node *tmp = (Node *)malloc(sizeof(Node));
		tmp->number = atoi(av[i]);
		tmp->moves = 0;
		tmp->next = NULL;

		if (a == NULL) 
		{
			a = tmp;
			end = a;
		} 
		else 
		{
			end->next = tmp;
			end = tmp;
		}
		i++;
	}
	return a;
}
int is_sorted(Node *a)
{
	while (a && a->next) 
	{
		if (a->number > a->next->number)
			return 0;
		a = a->next;
	}
	return 1;
}
int check_first_largest_second_smallest(Node *a)
{
	if (a == NULL || a->next == NULL)
		return 1; 
	int first = a->number;
	int second = a->next->number;
	int largest = first;
	int smallest = second;

	Node *current = a->next->next;
	while (current != NULL) 
	{
	if (	current->number > largest || current->number < smallest) 
			return 1; 
		current = current->next;
	}
	return 0; 
}
void rotate_and_swap(Node **a)
{
	if(*a == NULL || (*a)->next == NULL)
		return;
	while(is_sorted(*a) == 0) 
	{
		if(check_first_largest_second_smallest(*a) == 0)
			rotate_a(a);
		else if((*a)->number > (*a)->next->number) 
			swap_a(a);
		else 
			rotate_a(a);
	}
}
void if_dublicate(Node *a)
{
	Node *current = a;
	while (current != NULL) 
	{
		Node *tmp = current->next;
		while (tmp != NULL) 
		{
			if (current->number == tmp->number) 
			{
				write(1,"Error\n",6);
				exit(1);
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
}
void bubble_sort(Node **a)
{
	Node *current = *a;
	Node *tmp;
	while (current != NULL) 
	{
		tmp = current->next;
		while (tmp != NULL) 
		{
			if (current->number > tmp->number) 
			{
				int temp = current->number;
				current->number = tmp->number;
				tmp->number = temp;
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
}
Node* copy_stack(Node* a)
{
    Node *copy = NULL, *end = NULL, *tmp, *current = a;
    while (current) 
	{
        tmp = (Node *)malloc(sizeof(Node));
        tmp->number = current->number;
        tmp->next = NULL;
        if (copy == NULL) 
		{
            copy = tmp;
            end = copy;
        } 
		else 
		{
            end->next = tmp;
            end = tmp;
        }
        current = current->next;
    }
    return copy;
}
void assign_indix(Node* a)
{
    Node *current = a;
    int index = 1;
    while (current) 
	{
        current->index = index++;
        current = current->next;
    }
}
void free_stack(Node* a)
{
    Node *current = a, *tmp;
    while (current) 
	{
        tmp = current;
        current = current->next;
        free(tmp);
    }
}
void indexify(Node **a)
{
    Node *copy = copy_stack(*a);
    bubble_sort(&copy);
    assign_indix(copy);

    Node *current = *a, *j;
    while (current) {
        j = copy;
        while (j) 
		{
            if (current->number == j->number) 
			{
                current->number = j->index;
                break;
            }
            j = j->next;
        }
        current = current->next;
    }

    free_stack(copy);
}
int	ft_stack_size(Node *head)
{
	int	stack_size;

	stack_size = 0;
	while (head)
	{
		stack_size++;
		head = head->next;
	}
	return (stack_size);
}
void	ft_radix_sort(Node **stack_a, Node **stack_b)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_stack_size(*stack_a);
	while (!is_sorted(*stack_a))
	{
		j = 0;
		while (size > j++)
		{
			if ((((*stack_a)->number >> i) & 1) == 1)
				rotate_a(stack_a);
			else
				push_b(stack_a, stack_b);
		}
		while (ft_stack_size(*stack_b) != 0)
			push_a(stack_a, stack_b);
		i++;
	}
}

int main(int ac, char **av)
{
	Node *a = create_stack_a(av);
	Node *b = NULL;
	if_dublicate(a);
	indexify(&a);
	// push_b(&a, &b);
	// push_a(&a, &b);
	// printf("\n.............................\n");
	// printNode(a);
	// printNode(a);
	// rotate_a(&a);
	// if (ft_stack_size(a) <= 10)
	// 	rate_and_swap(&a);
	// else
	// 	ft_radix_sort(&a, &b);
	// printf("\n.............................\n");
	// printNode(a);
	// printf("\n.............................\n");
	// rotate_and_swap(&a);
	// bubble_sort(&a);
	printNode(a);
}