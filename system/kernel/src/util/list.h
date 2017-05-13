/*
 * Copyright (c) 2011-2014 Graham Edgecombe <graham@grahamedgecombe.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef UTIL_LIST_H
#define UTIL_LIST_H


typedef struct list_node
{
	struct list_node *next, *prev;
} list_node_t;

typedef struct
{
	list_node_t *head, *tail;
	int size;
} list_t;

typedef int(*list_compare_t)(const void *left, const void *right);

#define LIST_EMPTY { .head = 0, .tail = 0, .size = 0 }

#define list_for_each(list, node) for (list_node_t *node = (list)->head, *__next = node ? node->next : 0; node; node = __next, __next = node ? node->next : 0)

namespace List
{
	void init(list_t *list);
	void add_head(list_t *list, list_node_t *node);
	void add_tail(list_t *list, list_node_t *node);
	void insert_before(list_t *list, list_node_t *node, list_node_t *new_node);
	void insert_after(list_t *list, list_node_t *node, list_node_t *new_node);
	void remove(list_t *list, list_node_t *node);
	void sort(list_t *list, list_compare_t compare);
}

#endif
