/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as "core Flight System: Bootes"
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

/**
 * \file
 *
 * Default/simple implementation of EVS event port output using OS_printf
 *
 * This module routes all event ports to stdout via OS_printf,
 * maintaining the same behavior as the original EVS implementation.
 */

#include <stdio.h>
#include <string.h>

#include "cfe_psp.h"
#include "cfe_psp_module.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(eventport_printf);

void eventport_printf_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: Using printf-based EVS event port implementation\n");
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_SendEventToPort(uint8 PortNum, const char *Message)
{
    /* Validate port number */
    if (PortNum >= CFE_PSP_EVS_MAX_PORTS)
    {
        return CFE_PSP_ERROR;
    }

    /* Validate message pointer */
    if (Message == NULL)
    {
        return CFE_PSP_INVALID_POINTER;
    }

    /* Output the message with port number prefix */
    /* Note: EVS passes port numbers 1-4, but this API uses 0-3 */
    OS_printf("EVS Port%u %s\n", PortNum + 1, Message);

    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetEventPortConfig(uint8 PortNum, char *PortConfig, size_t ConfigSize)
{
    /* Validate port number */
    if (PortNum >= CFE_PSP_EVS_MAX_PORTS)
    {
        return CFE_PSP_ERROR;
    }

    /* Validate buffer pointer */
    if (PortConfig == NULL)
    {
        return CFE_PSP_INVALID_POINTER;
    }

    /* Return configuration description */
    snprintf(PortConfig, ConfigSize, "printf to stdout");

    return CFE_PSP_SUCCESS;
}