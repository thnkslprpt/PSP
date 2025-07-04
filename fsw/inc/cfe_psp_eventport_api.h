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
 * @file
 *
 * Event Services Output Port API for Platform Support Package (PSP)
 *
 * This API allows platform-specific routing of EVS event messages to
 * different output destinations (console, syslog, serial ports, etc.)
 */

#ifndef CFE_PSP_EVENTPORT_API_H
#define CFE_PSP_EVENTPORT_API_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "cfe_psp_error.h"

/******************************************************************************
 CONSTANTS AND MACROS
 ******************************************************************************/

/* EVS Port Numbers */
#define CFE_PSP_EVS_PORT_1    0
#define CFE_PSP_EVS_PORT_2    1
#define CFE_PSP_EVS_PORT_3    2
#define CFE_PSP_EVS_PORT_4    3
#define CFE_PSP_EVS_MAX_PORTS 4

/******************************************************************************
 FUNCTION PROTOTYPES
 ******************************************************************************/

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Send an event message to the specified output port
 *
 * This function routes a formatted event message to a platform-specific
 * output destination based on the port number. The implementation is
 * platform-dependent and may route to console, syslog, serial port, etc.
 *
 * @param[in] PortNum Port number (0-3)
 * @param[in] Message Formatted event message string (null-terminated)
 *
 * @return Execution status
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR if PortNum is invalid (>= CFE_PSP_EVS_MAX_PORTS)
 * @retval CFE_PSP_INVALID_POINTER if Message is NULL
 */
int32 CFE_PSP_SendEventToPort(uint8 PortNum, const char *Message);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Get configuration/status description of an event port
 *
 * This function returns a human-readable description of how the specified
 * port is configured on the current platform (e.g., "stdout", "syslog priority LOG_INFO",
 * "serial port /dev/ttyS0", etc.)
 *
 * @param[in]  PortNum    Port number (0-3)
 * @param[out] PortConfig Buffer to receive configuration description
 * @param[in]  ConfigSize Size of PortConfig buffer
 *
 * @return Execution status
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR if PortNum is invalid (>= CFE_PSP_EVS_MAX_PORTS)
 * @retval CFE_PSP_INVALID_POINTER if PortConfig is NULL
 */
int32 CFE_PSP_GetEventPortConfig(uint8 PortNum, char *PortConfig, size_t ConfigSize);

#endif /* CFE_PSP_EVENTPORT_API_H */