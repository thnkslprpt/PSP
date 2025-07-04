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
 * Linux syslog implementation of EVS event port output
 *
 * This module routes event ports to the Linux syslog daemon with
 * configurable priorities per port. Port 1 also outputs to console
 * for backward compatibility.
 */

#include <stdio.h>
#include <string.h>
#include <syslog.h>

#include "cfe_psp.h"
#include "cfe_psp_module.h"
#include "cfe_psp_config.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(eventport_syslog);

/* Port configuration - maps each port to a syslog priority */
typedef struct
{
    int         priority;     /* Syslog priority level */
    const char *description;  /* Human readable description */
    bool        console_echo; /* Also echo to console */
} EventPortConfig_t;

/* Default port configuration */
static const EventPortConfig_t port_config[CFE_PSP_EVS_MAX_PORTS] = {
    {LOG_INFO, "syslog LOG_INFO + console", true},      /* Port 1 - General info + console */
    {LOG_DEBUG, "syslog LOG_DEBUG", false},             /* Port 2 - Debug messages */
    {LOG_ERR, "syslog LOG_ERR", false},                 /* Port 3 - Error messages */
    {LOG_WARNING, "syslog LOG_WARNING", false}          /* Port 4 - Warning messages */
};

void eventport_syslog_Init(uint32 PspModuleId)
{
    /* Open syslog connection */
    openlog("cFE", LOG_PID | LOG_CONS, LOG_USER);

    /* Inform the user that this module is in use */
    printf("CFE_PSP: Using syslog-based EVS event port implementation\n");
    printf("CFE_PSP: Port 1: %s\n", port_config[0].description);
    printf("CFE_PSP: Port 2: %s\n", port_config[1].description);
    printf("CFE_PSP: Port 3: %s\n", port_config[2].description);
    printf("CFE_PSP: Port 4: %s\n", port_config[3].description);
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
        return CFE_PSP_INVALID_ARGUMENT;
    }

    /* Validate message pointer */
    if (Message == NULL)
    {
        return CFE_PSP_INVALID_POINTER;
    }

    /* Route to syslog with port-specific priority */
    syslog(port_config[PortNum].priority, "EVS Port%u: %s", PortNum + 1, Message);

    /* Also echo to console if configured */
    if (port_config[PortNum].console_echo)
    {
        OS_printf("EVS Port%u %s\n", PortNum + 1, Message);
    }

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
        return CFE_PSP_INVALID_ARGUMENT;
    }

    /* Validate buffer pointer */
    if (PortConfig == NULL)
    {
        return CFE_PSP_INVALID_POINTER;
    }

    /* Return configuration description */
    snprintf(PortConfig, ConfigSize, "%s", port_config[PortNum].description);

    return CFE_PSP_SUCCESS;
}