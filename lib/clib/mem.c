/*
 * Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "mem.h"
#include "clib.h"

#ifdef AMIGA
#include <stddef.h>
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/semaphores.h>
#include <clib/exec_protos.h>
#define ALLOC_MEM(x) AllocVec(x, MEMF_ANY | MEMF_CLEAR)
#define FREE_MEM(x) FreeVec(x)
#define Debug(x,y,z,w)
#else
# include <stdlib.h>
# define ALLOC_MEM(x) calloc(1L,x)
# define FREE_MEM(x) free(x)
# define Debug(x,y,z,w)
#endif

struct MemoryBlock
{
    struct MemoryBlock *next;
    size_t size;
    void *address;
};

struct MemoryList
{
    struct MemoryBlock *first;
    struct MemoryBlock *last;
    long peak;
    long size;
    long count;
};

struct MemoryList *list = NULL;

void alloc_error(char*, size_t);
void dealloc_error(char*, void*);

void* AllocMemSafe(size_t size)
{
    struct MemoryBlock *newblock;
    size_t allocsize;

    if (list == NULL) {
        list = (struct MemoryList*)ALLOC_MEM(sizeof(struct MemoryList));
        if (!list) {
            alloc_error("list", sizeof(struct MemoryList));
            return 0;
        }

        list->first = NULL;
        list->last = NULL;
        list->peak = 0;
        list->size = 0;
        list->count = 0;
    }

#if defined(__x86_64__) || defined(__aarch64__) || defined(_M_AMD64) || defined(_M_ARM64)
    // Align to bytes of 8
    allocsize = (size + 7) & ~0x07;
#else
    // Align to bytes of 4
    allocsize = (size + 3) & ~0x03;
#endif

    newblock = (struct MemoryBlock*)ALLOC_MEM(sizeof(struct MemoryBlock));
    if (!newblock) {
        alloc_error("block", sizeof(struct MemoryBlock));
        return 0;
    }

    newblock->address = (struct MemoryBlock*)ALLOC_MEM(allocsize);
    if (!newblock->address) {
        FREE_MEM(newblock);
        alloc_error("memory", allocsize);
        return 0;
    }

    newblock->size = allocsize;
    newblock->next = NULL;

    if(list->first == NULL) {
        list->first = newblock;
        list->last = newblock;
    } else {
        list->last->next = newblock;
        list->last = newblock;
    }

    list->size += allocsize;
    list->count++;

    if (list->size > list->peak) {
        list->peak = list->size;
    }

    // DEBUG code
    // Debug(NULL, "Mememory allocated at address (%x)\n", newblock->address);

    return newblock->address;
}

void FreeMemSafe(void* block)
{
    struct MemoryBlock *current, *last;

    if (list == NULL || block == NULL) {
        dealloc_error("list", 0);
        return;
    }

    if (block == NULL) {
        dealloc_error("memory", 0);
        return;
    }

    last = NULL;
    current = list->first;
    while (current != NULL && current->address != block) {
        last = current;
        current = current->next;
    }

    if (current == NULL) {
        dealloc_error("address not found", block);
        return;
    }

    list->size -= current->size;
    list->count--;

    if (list->first == current) {
        list->first = NULL;
        list->last = NULL;
    } else if (list->last == current) {
        last->next = current->next;
        list->last = last;
    } else {
        last->next = current->next;
    }

    FREE_MEM(current->address);
    FREE_MEM(current);

    // DEBUG code
    // Debug(NULL, "Mememory deallocated at address (%x)\n", block);
}

void FreeAllSafe()
{
    struct MemoryBlock *current, *next;

    if (list == NULL) {
        return;
    }

    current = list->first;
    while (current != NULL) {
        next = current->next;
        FREE_MEM(current->address);
        FREE_MEM(current);
        current = next;
    }

    FREE_MEM(list);
    list = NULL;
}

void MemUsage(long *blocks, long *size, long *peak)
{
    *blocks = list->count;
    *size = list->size;
    *peak = list->peak;;
}

void alloc_error(char *descr, size_t size)
{
    Debug(NULL, "Mememory allocation error (%s) with size (%d)\n", descr, size);
}

void dealloc_error(char *descr, void *p)
{
    Debug(NULL, "Mememory deallocation error (%s) address (%x)\n", descr, p);
}
