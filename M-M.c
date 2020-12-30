/*
 * mm.c
 * ID :1900013049@pku.edu.cn
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(p) (((size_t)(p) + (ALIGNMENT - 1)) & ~0x7)

/* Basic constants and macros */
#define WSIZE 4             /* Word and header/footer size (bytes) */
#define DSIZE 8             /* Double word size (bytes) */
#define CHUNKSIZE (1 << 10) /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE(((char *)(bp)-DSIZE)))

/*compute address of next and previous free blocks*/
#define NEXT_FRE_BLKP(bp) (GET(bp))
#define PREV_FRE_BLKP(bp) (GET((char *)bp + WSIZE))
/* Global variables */
static char *heap_listp = 0; /* Pointer to first block */
static char *free_listp = 0; /*pointer to first free block*/

/*min free block size is 16 */
#define MIN_SIZE (1 << 4)
#define SEG_LIST_NUM 10

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void add_node(void *bp);
static void delete_node(void *bp);
static int get_index_of_free_list(size_t asize);
/*
 * Initialize: return -1 on error, 0 on success.
 * initial the segregated free list to 0 and store it in the head of the heap.
 * and then create initial heap space.
 */
int mm_init(void)
{
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk((SEG_LIST_NUM + 4) * WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp + SEG_LIST_NUM * WSIZE, 0);                    /* Alignment padding */
    PUT(heap_listp + (SEG_LIST_NUM + 1) * WSIZE, PACK(DSIZE, 1)); /* Prologue header */
    PUT(heap_listp + (SEG_LIST_NUM + 2) * WSIZE, PACK(DSIZE, 1)); /* Prologue footer */
    PUT(heap_listp + (SEG_LIST_NUM + 3) * WSIZE, PACK(0, 1));     /* Epilogue header */
    free_listp = heap_listp;
    heap_listp += (SEG_LIST_NUM + 2) * WSIZE;
    /*initial the segregated free list as 0(NULL)*/
    for (int i = 0; i < SEG_LIST_NUM; i++)
        PUT(free_listp + WSIZE * i, 0);
    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;
    return 0;
}

/*
 * malloc:return a pointer to an allocated block payload of at least size 
 * bytes.
 * if size is not more than 8 bytes ,then allocate the minimum block
 * (size:16 bytes).After determining the block size,find the most fitting 
 * in the segregated free lists and place it in.
 */
void *malloc(size_t size)
{
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;

    if (heap_listp == 0)
    {
        mm_init();
    }
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= DSIZE)
        asize = 2 * DSIZE;
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL)
    {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}

/*
 * free:free the block pointed to by ptr,only work when the pointer ptr was 
 * returned by an earlier call to malloc,calloc,or realloc and has not yet
 * been freed.free(NULL) has no effect.
 * 
 * return void
 */
void free(void *bp)
{
    if (bp == NULL)
        return;

    size_t size = GET_SIZE(HDRP(bp));
    if (heap_listp == 0)
    {
        mm_init();
    }

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

/*
 * realloc 
 */
void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
{
        return malloc(size);
}
    if (size == 0)
        free(ptr);

    void *newptr;
    size_t copySize;
    newptr = malloc(size);
    if (newptr == NULL)
        return NULL;
    size = GET_SIZE(HDRP(ptr));
    copySize = GET_SIZE(HDRP(newptr));
    if (size < copySize)
        copySize = size;
    memcpy(newptr, ptr, copySize - WSIZE);
    free(ptr);
    return newptr;
}

/*
 * calloc - just malloc consecutive n*size bytes in heap.
*/
void *calloc(size_t nmemb, size_t size)
{
    /*caculate the total bytes needed*/
    size_t nsize = nmemb * size;
    void *newptr;
    /*malloc consecutive nsize bytes and get the pointer*/
    newptr = malloc(nsize);
    memset(newptr, 0, nsize);
    return newptr;
}

/* 
 * extend_heap - Extend heap with free block and return its block pointer.
 * If there is free block before the new block,then coalesce them before
 * returning.
 */
static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

/*
 * coalesce - Boundary tag coalescing. Return ptr to coalesced block.
 * 
 *  Discuss whether the blocks before and after the current block have
 *  been allocated,and then modify the boundary tag, delete the old node
 *  in the free linked list, and add the updated new node.
 */
static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    /*prev:allocated;next:allocated*/
    if (prev_alloc && next_alloc);
    /*prev:allocated;next:free*/
    else if (prev_alloc && !next_alloc)
    {
        delete_node(NEXT_BLKP(bp));
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }
    /*prev:free;next:allocated*/
    else if (!prev_alloc && next_alloc)
    {
        delete_node(PREV_BLKP(bp));
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    /*prev:free;next:free*/
    else
    {
        delete_node(PREV_BLKP(bp));
        delete_node(NEXT_BLKP(bp));
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
                GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    add_node(bp);
    return bp;
}

/* 
 * place - Place block of asize bytes at start of free block bp 
 *         and split if remainder would be at least minimum block size
 */
static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    delete_node(bp);
    if ((csize - asize) >= (2 * DSIZE))
    {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
        add_node(bp);
    }
    else
    {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

/* 
 * find_fit - Find a fit for a block with asize bytes 
 */
static void *find_fit(size_t asize)
{
    void *bp = NULL;
    int index = get_index_of_free_list(asize);
    char *free_list_ptr;
    unsigned int value = 0;
    for (; index < SEG_LIST_NUM; index++)
    {
        value = GET(free_listp + WSIZE * index);
        while (value != 0)
        {
            free_list_ptr = free_listp + value;
            if (GET_SIZE(HDRP(free_list_ptr)) >= asize)
            {
                bp = free_list_ptr;
                return bp;
            }
            value = NEXT_FRE_BLKP(free_list_ptr);
        }
    }
    return NULL; /* No fit */
}

/*
 * add_node - add node in incresing order to the corresponding size class
 */
void add_node(void *bp)
{
    int index;
    size_t size;
    unsigned int offset, value;
    char *free_list_ptr;

    size = GET_SIZE(HDRP(bp));
    index = get_index_of_free_list(size);
    offset = (unsigned int)((char *)bp - free_listp);
    free_list_ptr = free_listp + WSIZE * index;
    value = GET(free_list_ptr);
    while (value != 0) /*next!=NULL*/
    {
        free_list_ptr = free_listp + value;
        if (GET_SIZE(HDRP(free_list_ptr)) >= size)
        {
            unsigned int prev = PREV_FRE_BLKP(free_list_ptr);
            PUT(bp, value);                     /*bp->next=free_list_ptr*/
            PUT((char *)bp + WSIZE, prev);      /*bp->prev=free_list_ptr->prev*/
            PUT(free_listp + prev, offset);     /*free_list_ptr->prev->next = bp*/
            PUT(free_list_ptr + WSIZE, offset); /*free_list_ptr->prev=bp*/
            return;
        }
        value = NEXT_FRE_BLKP(free_list_ptr);
    }
    /*store bp in the end*/
    PUT(free_list_ptr, offset);
    PUT(bp, 0);                                                          /*store next node (which is NULL)*/
    PUT((char *)bp + WSIZE, (unsigned int)(free_list_ptr - free_listp)); /*store prev node offset*/
}

/*
 * delete_node - delete node and modify the prev and next pointer
 */
void delete_node(void *bp)
{
    unsigned int prev = PREV_FRE_BLKP(bp);
    unsigned int next = NEXT_FRE_BLKP(bp);
    PUT(free_listp + prev, next);
    if (next == 0)
        return;
    PUT(free_listp + (next + WSIZE), prev);
}

/*
 * get_index_of_free_list - determines the size class of the free block 
 * based on the size of asize and get the index to compute the address
 * in the heap.
 */
static int get_index_of_free_list(size_t asize)
{
    if (asize <= MIN_SIZE)
        return 0;
    if (asize <= MIN_SIZE << 1)
        return 1;
    if (asize <= MIN_SIZE << 2)
        return 2;
    if (asize <= MIN_SIZE << 3)
        return 3;
    if (asize <= MIN_SIZE << 4)
        return 4;
    if (asize <= MIN_SIZE << 5)
        return 5;
    if (asize <= MIN_SIZE << 6)
        return 6;
    if (asize <= MIN_SIZE << 7)
        return 7;
    if (asize <= MIN_SIZE << 8)
        return 8;
    return 9;
}

/*
 * Return whether the pointer is in the heap.
 * May be useful for debugging.
 */
static int in_heap(const void *p)
{
    return p <= mem_heap_hi() && p >= mem_heap_lo();
}

/*
 * Return whether the pointer is aligned.
 * May be useful for debugging.
 */
static int aligned(const void *p)
{
    return (size_t)ALIGN(p) == (size_t)p;
}

static void printblock(void *bp,int *error)
{
    size_t hsize, halloc, fsize, falloc;

    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp));
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));

    if (hsize == 0)
    {
        printf("%p: EOL\n", bp);
        return;
    }
    printf("%p: header: [%ld:%c] footer: [%ld:%c]\n", bp,
           hsize, (halloc ? 'a' : 'f'),
           fsize, (falloc ? 'a' : 'f'));
}

static int checkblock(void *bp,int *error)
{
    //area is aligned
    if ((size_t)bp % 8)
    {
        *error=1;
        printf("Error: %p is not doubleword aligned\n", bp);
    }
    //header and footer match
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
    {
        *error=1;
        printf("Error: header does not match footer\n");
    }
    size_t size = GET_SIZE(HDRP(bp));
    //size is valid
    if (size % 8)
    {
        *error=1;
        printf("Error: %p payload size is not doubleword aligned\n", bp);
    }
    return GET_ALLOC(HDRP(bp));
}

static void printlist(int index)
{
    size_t hsize, halloc;
    char* i;
    for (i = free_listp + index *WSIZE; NEXT_FRE_BLKP(i) != 0; )
    {
        i = free_listp + NEXT_FRE_BLKP(i);
        hsize = GET_SIZE(HDRP(i));
        halloc = GET_ALLOC(HDRP(i));
        printf("[listnode %d] %p: header: [%ld:%c] prev: [%p]  next: [%p]\n",
               index, i,
               hsize, (halloc ? 'a' : 'f'),
               free_listp + PREV_FRE_BLKP(i), free_listp + NEXT_FRE_BLKP(i));
    }
}
static void checklist(int index,int *error)
{
    char *pre = free_listp + index *WSIZE;
    char *i;
    int hsize, halloc;
    for (i = pre; NEXT_FRE_BLKP(i) != 0;)
    {
        i = free_listp + NEXT_FRE_BLKP(i);
        if (free_listp + PREV_FRE_BLKP(i) != pre)
        {
            *error=1;
            printf("Error: pred point error\n");
        }
        if (free_listp + NEXT_FRE_BLKP(pre) != i)
        {
            *error=1;
            printf("Error: succ point error\n");
        }
        hsize = GET_SIZE(HDRP(i));
        halloc = GET_ALLOC(HDRP(i));
        if (halloc)
        {
            *error=1;
            printf("Error: list node should be free\n");
        }
        if (NEXT_FRE_BLKP(i) != 0 && GET_SIZE(HDRP(free_listp+NEXT_FRE_BLKP(i))) < hsize)
        {
            *error=1;
            printf("Error: list size order error\n");
        }
        if (hsize > (MIN_SIZE<<index) || index == 0?0:hsize <= (MIN_SIZE<<(index-1)))
        {
            *error=1;
            printf("Error: list node size error\n");
        }
        pre = i;
    }
}

/*
 * mm_checkheap
 */
void mm_checkheap(int lineno)
{
    int error=0;
    char *bp = heap_listp;
    printf("Heap (%p):\n", heap_listp);

    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp)))
    {
        error =1;
        printf("Bad prologue header\n");
    }
    checkblock(heap_listp,&error);
    int pre_free = 0;
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
    {
        if(error==1)
            printblock(bp);
        int cur_free = checkblock(bp,&error);
        if (pre_free && cur_free)
        {
            error=1;
            printf("Contiguous free blocks\n");
        }
    }
    int i = 0;
    for (; i < SEG_LIST_NUM; i++)
    {
        checklist(i,&error);
        if(error==1)
            printlist(i);
    }
    printblock(bp);
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
    {
        error=1;
        printf("Bad epilogue header\n");
    }
    if(error == 1)
    {
        printf("error in Line %d\n",lineno);
        exit(0);
    }
}