/***********************************************************************************************
Copyright (C) 2009 - Alexandru Gagniuc - <http:\\g-tech.homeserver.com\HPC.htm>
 * This file is part of ElectroMag.

    ElectroMag is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ElectroMag is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ElectroMag.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************************************/


#ifndef _MEMMAN_H
#define _MEMMAN_H

#ifdef _WIN32
#define PLATFORM_FOUND
#include<malloc.h>

inline void* AlignedMalloc(size_t size, size_t alignment)
{
	return _aligned_malloc(size, alignment);
}

#endif
#ifdef __linux__
#define PLATFORM_FOUND
#include <malloc.h>

inline void* AlignedMalloc(size_t size, size_t alignment)
{
	return memalign(alignment, size);
}
#endif


#ifndef PLATFORM_FOUND
#error Compilation platform not found or not supported. Define _WIN32 or __linux__ to select a platform.
#endif

#undef PLATFORM_FOUND

#endif//_MEMMAN_H
