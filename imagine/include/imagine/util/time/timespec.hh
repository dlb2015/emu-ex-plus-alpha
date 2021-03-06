#pragma once

/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#include <time.h>
#include <assert.h>

#define NSEC_PER_SEC 1000000000
#define USEC_PER_SEC 1000000

static bool timespec_isValid(struct timespec t)
{
	return t.tv_nsec >= 0 && t.tv_nsec < NSEC_PER_SEC;
}

static int timespec_compare(struct timespec t1, struct timespec t2)
{
	if(t1.tv_sec != t2.tv_sec)
		return t1.tv_sec - t2.tv_sec;
	return t1.tv_nsec - t2.tv_nsec;
}

static struct timespec timespec_subtract(struct timespec t1, struct timespec t2)
{
	assert(timespec_isValid(t1) && timespec_isValid(t2));
	assert(timespec_compare(t1, t2) >= 0);
	auto result = t1;
	result.tv_sec -= t2.tv_sec;
	result.tv_nsec -= t2.tv_nsec;
	if(result.tv_nsec < 0)
	{
		result.tv_nsec += NSEC_PER_SEC;
		result.tv_sec--;
	}
	return result;
}

static struct timespec timespec_add(struct timespec t1, struct timespec t2)
{
	assert(timespec_isValid(t1) && timespec_isValid(t2));
	auto result = t1;
	result.tv_sec += t2.tv_sec;
	result.tv_nsec += t2.tv_nsec;
	if(result.tv_nsec >= NSEC_PER_SEC)
	{
		result.tv_nsec -= NSEC_PER_SEC;
		result.tv_sec++;
	}
	return result;
}

static long int timespec_divUsecs(struct timespec t, long int usecs)
{
	return (((int64)t.tv_sec * USEC_PER_SEC) / usecs) + ((t.tv_nsec / 1000) / usecs);
}

static long int timespec_divNsecs(struct timespec t, long int nsecs)
{
	return (((int64)t.tv_sec * NSEC_PER_SEC) / nsecs) + (t.tv_nsec / nsecs);
}

static double timespec_toDouble(struct timespec t)
{
	return (double)t.tv_sec + (double)t.tv_nsec/(double)1.0e9;
}

#undef NSEC_PER_SEC
#undef USEC_PER_SEC
