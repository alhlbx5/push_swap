/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:41:57 by aalhalab          #+#    #+#             */
/*   Updated: 2024/04/30 02:36:08 by aalhalab         ###   ########.fr       */
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
void is_dublicate(Node *a);
void bubble_sort(Node **a);
Node* copy_stack(Node* a);
void assign_indix(Node* a);
void free_stack(Node* a);
void indexify(Node **a);
int	stack_size(Node *head);
void ft_radix_sort(Node **stack_a, Node **stack_b);

void swap_a(Node **a)
{
    if (*a == NULL || (*a)->next == NULL) 
        return;
    Node *first = *a;
    Node *second = first->next;

    first->next = second->next;
    second->next = first;
    *a = second;

    write(1, "sa\n", 3);
}
void rotate_a(Node **a)
{
    if (*a == NULL || (*a)->next == NULL) 
        return;

    Node *first = *a;
    *a = first->next;
    first->next = NULL;

    Node *last = *a;
    while (last && last->next)
        last = last->next;

    last->next = first;

    write(1, "ra\n", 3);
}
void push_a(Node **a, Node **b)
{
    if (*b == NULL) 
        return;

    Node *nextNode = (*b)->next;
    (*b)->next = *a;
    *a = *b;
    *b = nextNode;

    write(1, "pa\n", 3);
}
void push_b(Node **a, Node **b)
{
    if (!(*a))
        return;

    Node *nextNode = (*a)->next;
    (*a)->next = *b;
    *b = *a;
    *a = nextNode;

    write(1, "pb\n", 3);
}
void printNode(Node *a)
{
    if (a == NULL) 
    {
        write(1,"\n",1);
        return;
    }
    printf("%d ", a->number);
    printNode(a->next);
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
    if (a == NULL || a->next == NULL)
        return 1;
    if (a->number > a->next->number)
        return 0;
    return is_sorted(a->next);
}
int check_first_largest_second_smallest(Node *a)
{
    if (a == NULL || a->next == NULL)
        return 1; 
    int largest = a->number;
    int smallest = a->next->number;
    a = a->next->next;
    while (a != NULL) 
    {
        if (a->number > largest || a->number < smallest) 
            return 1; 
        a = a->next;
    }
    return 0; 
}
void rotate_and_swap(Node **a)
{
    if(*a == NULL || (*a)->next == NULL)
        return;
    int sorted = is_sorted(*a);
    while(sorted == 0) 
    {
        if(check_first_largest_second_smallest(*a) == 0)
            rotate_a(a);
        else if((*a)->number > (*a)->next->number) 
            swap_a(a);
        else 
            rotate_a(a);

        sorted = is_sorted(*a);
    }
}
void check_dublicates_recursive(Node *current, Node *check)
{
    if (check == NULL)
        return;
    if (current->number == check->number)
    {
        write(1, "Error\n", 6);
        exit(1);
    }
    check_dublicates_recursive(current, check->next);
}
void is_dublicate(Node *a)
{
    if (a == NULL)
        return;
    check_dublicates_recursive(a, a->next);
    is_dublicate(a->next);
}
void swap_nodes(Node *current, Node *tmp)
{
    int temp = current->number;
    current->number = tmp->number;
    tmp->number = temp;
}
int process_inner_loop(Node *current)
{
    Node *tmp = current->next;
    int swapped = 0;

    while (tmp != NULL)
    {
        if (current->number > tmp->number)
        {
            swap_nodes(current, tmp);
            swapped = 1;
        }
        tmp = tmp->next;
    }

    return swapped;
}
void bubble_sort(Node **head)
{
    if (*head == NULL)
        return;

    Node *current = *head;
    int swapped;

    while (current->next != NULL)
    {
        swapped = process_inner_loop(current);

        if (swapped == 0)
            break;

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
int stack_size(Node *head)
{
    int stack_size = 0;
    while (head)
    {
        stack_size++;
        head = head->next;
    }
    return stack_size;
}
void process_stack(Node **stack_a, Node **stack_b, int size, int i)
{
    int j = 0;
    while (size > j++)
    {
        if ((((*stack_a)->number >> i) & 1) == 1)
            rotate_a(stack_a);
        else
            push_b(stack_a, stack_b);
    }
    while (stack_size(*stack_b) != 0)
        push_a(stack_a, stack_b);
}
void ft_radix_sort(Node **stack_a, Node **stack_b)
{
    int i = 0;
    int size = stack_size(*stack_a);
    while (!is_sorted(*stack_a))
    {
        process_stack(stack_a, stack_b, size, i);
        i++;
    }
}

int main(int ac, char **av)
{
	Node *a = create_stack_a(av);
	Node *b = NULL;
	is_dublicate(a);
	indexify(&a);
	// push_b(&a, &b);
	// push_a(&a, &b);
	// printf("\n.............................\n");
	// printNode(a);
	// printNode(a);
	// rotate_a(&a);
	if (stack_size(a) <= 10)
		rotate_and_swap(&a);
	else
		ft_radix_sort(&a, &b);
	// printf("\n.............................\n");
	// printNode(a);
	// printf("\n.............................\n");
	// rotate_and_swap(&a);
	// bubble_sort(&a);
	printNode(a);
}