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

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in cfe_psp_port_api header
 */

#include "cfe_psp_port_api.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_PortRead16()
 * ----------------------------------------------------
 */
int32 CFE_PSP_PortRead16(cpuaddr PortAddress, uint16 *uint16Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_PortRead16, int32);

    UT_GenStub_AddParam(CFE_PSP_PortRead16, cpuaddr, PortAddress);
    UT_GenStub_AddParam(CFE_PSP_PortRead16, uint16 *, uint16Value);

    UT_GenStub_Execute(CFE_PSP_PortRead16, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_PortRead16, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_PortRead32()
 * ----------------------------------------------------
 */
int32 CFE_PSP_PortRead32(cpuaddr PortAddress, uint32 *uint32Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_PortRead32, int32);

    UT_GenStub_AddParam(CFE_PSP_PortRead32, cpuaddr, PortAddress);
    UT_GenStub_AddParam(CFE_PSP_PortRead32, uint32 *, uint32Value);

    UT_GenStub_Execute(CFE_PSP_PortRead32, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_PortRead32, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_PortRead8()
 * ----------------------------------------------------
 */
int32 CFE_PSP_PortRead8(cpuaddr PortAddress, uint8 *ByteValue)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_PortRead8, int32);

    UT_GenStub_AddParam(CFE_PSP_PortRead8, cpuaddr, PortAddress);
    UT_GenStub_AddParam(CFE_PSP_PortRead8, uint8 *, ByteValue);

    UT_GenStub_Execute(CFE_PSP_PortRead8, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_PortRead8, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_PortWrite16()
 * ----------------------------------------------------
 */
int32 CFE_PSP_PortWrite16(cpuaddr PortAddress, uint16 uint16Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_PortWrite16, int32);

    UT_GenStub_AddParam(CFE_PSP_PortWrite16, cpuaddr, PortAddress);
    UT_GenStub_AddParam(CFE_PSP_PortWrite16, uint16, uint16Value);

    UT_GenStub_Execute(CFE_PSP_PortWrite16, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_PortWrite16, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_PortWrite32()
 * ----------------------------------------------------
 */
int32 CFE_PSP_PortWrite32(cpuaddr PortAddress, uint32 uint32Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_PortWrite32, int32);

    UT_GenStub_AddParam(CFE_PSP_PortWrite32, cpuaddr, PortAddress);
    UT_GenStub_AddParam(CFE_PSP_PortWrite32, uint32, uint32Value);

    UT_GenStub_Execute(CFE_PSP_PortWrite32, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_PortWrite32, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_PortWrite8()
 * ----------------------------------------------------
 */
int32 CFE_PSP_PortWrite8(cpuaddr PortAddress, uint8 ByteValue)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_PortWrite8, int32);

    UT_GenStub_AddParam(CFE_PSP_PortWrite8, cpuaddr, PortAddress);
    UT_GenStub_AddParam(CFE_PSP_PortWrite8, uint8, ByteValue);

    UT_GenStub_Execute(CFE_PSP_PortWrite8, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_PortWrite8, int32);
}
