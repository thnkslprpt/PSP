/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/*
** File   :	cfe_psp_memutils.c
**
** Author :	Ezra Yeheskeli
**
** Purpose:
**		   This file  contains some of the cFE Platform Support Layer.
**        It contains the processor architecture specific calls.
**
**
*/

/*
** Include section
*/

#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*
** User defined include files
*/

#include "cfe_psp.h"
/*
** global memory
*/

/*
**
** Purpose:
**	Copies 'n' byte from memory address pointed by 'src' to memory
**  address pointed by ' dest' For now we are using the standard c library
**  call 'memcpy' but if we find we need to make it more efficient then
**  we'll implement it in assembly.
**
** Assumptions and Notes:
**
** Parameters:
**	dest : pointer to an address to copy to
**  src : pointer address to copy from
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: CFE_PSP_SUCCESS
*/
int32 CFE_PSP_MemCpy(void *dest, const void *src, uint32 n)
{
    memcpy(dst, src, n);
    return CFE_PSP_SUCCESS;
}

/*
**
** Purpose:
**	Copies 'n' number of byte of value 'value' to memory address pointed
**  by 'dest' .For now we are using the standard c library call 'memset'
**  but if we find we need to make it more efficient then we'll implement
**  it in assembly.
**
**
** Assumptions and Notes:
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: CFE_PSP_SUCCESS
*/
/*
** CFE_PSP_MemSet
*/
int32 CFE_PSP_MemSet(void *dest, uint8 value, uint32 n)
{
    memset(dest, (int)value, (size_t)n);
    return CFE_PSP_SUCCESS;
}
