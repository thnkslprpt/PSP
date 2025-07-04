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
 * \ingroup modules
 *
 * Coverage test for eventport_printf module implementation
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "cfe_psp.h"
#include "cfe_psp_module.h"

/* Prototype for module init */
extern void eventport_printf_Init(uint32 PspModuleId);

/* Include the source file to test */
UT_DEFAULT_STUB(CFE_PSP_ModuleInit, (void))

/* Use a hook function to capture printf output */
static char  LastPrintfMessage[512];
static int32 Test_OS_printf_Hook(void *UserObj, int32 StubRetcode, uint32 CallCount, const UT_StubContext_t *Context)
{
    const char *FormatStr = UT_Hook_GetArgValueByName(Context, "string", const char *);
    if (FormatStr != NULL)
    {
        vsnprintf(LastPrintfMessage, sizeof(LastPrintfMessage), FormatStr, Context->ArgPtr[0]);
    }
    return StubRetcode;
}

void Test_eventport_printf_Init(void)
{
    /* Test initialization */
    UT_ClearDefaultReturnValue(UT_KEY(printf));
    eventport_printf_Init(1);
    UtAssert_STUB_COUNT(printf, 1);
}

void Test_CFE_PSP_SendEventToPort(void)
{
    int32 Status;

    /* Clear the captured message */
    memset(LastPrintfMessage, 0, sizeof(LastPrintfMessage));
    UT_SetHookFunction(UT_KEY(OS_printf), Test_OS_printf_Hook, NULL);

    /* Test valid port and message */
    Status = CFE_PSP_SendEventToPort(0, "Test message");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_STUB_COUNT(OS_printf, 1);
    UtAssert_StrCmp(LastPrintfMessage, "EVS Port1 Test message\n", "Port 0 outputs as Port1");

    /* Test all valid ports */
    Status = CFE_PSP_SendEventToPort(1, "Port 2 test");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(LastPrintfMessage, "EVS Port2 Port 2 test\n", "Port 1 outputs as Port2");

    Status = CFE_PSP_SendEventToPort(2, "Port 3 test");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(LastPrintfMessage, "EVS Port3 Port 3 test\n", "Port 2 outputs as Port3");

    Status = CFE_PSP_SendEventToPort(3, "Port 4 test");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(LastPrintfMessage, "EVS Port4 Port 4 test\n", "Port 3 outputs as Port4");

    /* Test invalid port number */
    Status = CFE_PSP_SendEventToPort(4, "Invalid port");
    UtAssert_INT32_EQ(Status, CFE_PSP_ERROR);
    
    Status = CFE_PSP_SendEventToPort(255, "Invalid port");
    UtAssert_INT32_EQ(Status, CFE_PSP_ERROR);

    /* Test NULL message */
    Status = CFE_PSP_SendEventToPort(0, NULL);
    UtAssert_INT32_EQ(Status, CFE_PSP_INVALID_POINTER);

    UT_ClearHookFunction(UT_KEY(OS_printf));
}

void Test_CFE_PSP_GetEventPortConfig(void)
{
    int32 Status;
    char  ConfigBuf[128];

    /* Test valid port */
    memset(ConfigBuf, 0, sizeof(ConfigBuf));
    Status = CFE_PSP_GetEventPortConfig(0, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(ConfigBuf, "printf to stdout", "Config description matches");

    /* Test all ports return same config */
    Status = CFE_PSP_GetEventPortConfig(3, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(ConfigBuf, "printf to stdout", "All ports have same config");

    /* Test invalid port */
    Status = CFE_PSP_GetEventPortConfig(4, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_ERROR);

    /* Test NULL buffer */
    Status = CFE_PSP_GetEventPortConfig(0, NULL, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_INVALID_POINTER);

    /* Test small buffer - should still work */
    char SmallBuf[10];
    Status = CFE_PSP_GetEventPortConfig(0, SmallBuf, sizeof(SmallBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    /* String should be truncated but null-terminated */
    UtAssert_True(strlen(SmallBuf) < sizeof(SmallBuf), "String truncated to fit");
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ResetTest, NULL, #test)

/* Local Setup function for test cases */
static void ResetTest(void)
{
    UT_ResetState(0);
    memset(LastPrintfMessage, 0, sizeof(LastPrintfMessage));
}

void UtTest_Setup(void)
{
    ADD_TEST(Test_eventport_printf_Init);
    ADD_TEST(Test_CFE_PSP_SendEventToPort);
    ADD_TEST(Test_CFE_PSP_GetEventPortConfig);
}