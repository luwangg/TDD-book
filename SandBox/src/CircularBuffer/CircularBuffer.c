/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include "CircularBuffer.h"
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>

static bool isEmpty 	= true;
static bool isFull 		= false;
static int *buffer 		= 0;
static int 	dimension 	= 0;
static int 	count 		= 0;
static int *write 		= 0; // pointer to next free slot
static int *read 		= 0; // pointer to next unread slot

void CircularBuffer_Create(int new_dimension)
{
	dimension	= new_dimension;
	buffer 		= calloc(dimension, sizeof(int));
	write 		= buffer;
	read 		= buffer;
	count 		= 0;
	isEmpty 	= true;
	isFull 		= false;
}

void CircularBuffer_Destroy(void)
{
	if (buffer)
		free(buffer);
	buffer 		= 0;
	dimension 	= 0;
	count 		= 0;
	isEmpty 	= true;
	isFull 		= false;
}

bool CircularBuffer_IsEmpty(void)
{
	return isEmpty;
}

bool CircularBuffer_IsFull(void)
{
	return isFull;
}

bool CircularBuffer_Queue(int insert)
{
	bool status = false;

	if (!isFull)
	{
		isEmpty = false; // no longer empty
		*write = insert; // add to queue
		count++; // increment count
		if (count == dimension) // full
		{
			isFull = true;
			write = buffer; // wrap around
		}
		else
		{
			write++; // next open slot
		}
		status = true;
	}

	return status;
}

bool CircularBuffer_Dequeue(int *readback)
{
	bool status = false;

	if (!isEmpty)
	{
		printf("%d", *read);
		// if caller doesn't care about value
		if (readback)
			*readback = *read;
		count--; // decrement count
		read++; // next in queue
		if (!count) // empty
			isEmpty = true;
		status = true;
	}

	return status;
}

int CircularBuffer_Size(void)
{
	return count;
}
