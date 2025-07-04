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
 * Coverage test for eventport_syslog module implementation
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "cfe_psp.h"
#include "cfe_psp_module.h"

/* Stub out syslog functions */
#include <syslog.h>
UT_DEFAULT_STUB(openlog, (const char *ident, int option, int facility))
UT_DEFAULT_STUB(syslog, (int priority, const char *format, ...))
UT_DEFAULT_STUB(closelog, (void))

/* Prototype for module init */
extern void eventport_syslog_Init(uint32 PspModuleId);

/* Include the source file to test */
UT_DEFAULT_STUB(CFE_PSP_ModuleInit, (void))

/* Hook to capture syslog calls */
typedef struct
{
    int  priority;
    char message[512];
} SyslogCapture_t;

static SyslogCapture_t LastSyslogCall;

static int32 Test_syslog_Hook(void *UserObj, int32 StubRetcode, uint32 CallCount, const UT_StubContext_t *Context)
{
    LastSyslogCall.priority = UT_Hook_GetArgValueByName(Context, "priority", int);
    const char *format      = UT_Hook_GetArgValueByName(Context, "format", const char *);
    
    if (format != NULL)
    {
        vsnprintf(LastSyslogCall.message, sizeof(LastSyslogCall.message), format, Context->ArgPtr[0]);
    }
    
    return StubRetcode;
}

/* Hook to capture OS_printf calls */
static char LastPrintfMessage[512];

static int32 Test_OS_printf_Hook(void *UserObj, int32 StubRetcode, uint32 CallCount, const UT_StubContext_t *Context)
{
    const char *FormatStr = UT_Hook_GetArgValueByName(Context, "string", const char *);
    if (FormatStr != NULL)
    {
        vsnprintf(LastPrintfMessage, sizeof(LastPrintfMessage), FormatStr, Context->ArgPtr[0]);
    }
    return StubRetcode;
}

void Test_eventport_syslog_Init(void)
{
    /* Test initialization */
    UT_ClearDefaultReturnValue(UT_KEY(openlog));
    UT_ClearDefaultReturnValue(UT_KEY(printf));
    eventport_syslog_Init(1);
    UtAssert_STUB_COUNT(openlog, 1);
    UtAssert_STUB_COUNT(printf, 5); /* 1 for module info + 4 for port configs */
}

void Test_CFE_PSP_SendEventToPort_Syslog(void)
{
    int32 Status;

    /* Set up hooks */
    UT_SetHookFunction(UT_KEY(syslog), Test_syslog_Hook, NULL);
    UT_SetHookFunction(UT_KEY(OS_printf), Test_OS_printf_Hook, NULL);

    /* Test Port 0 - should go to syslog LOG_INFO and console */
    memset(&LastSyslogCall, 0, sizeof(LastSyslogCall));
    memset(LastPrintfMessage, 0, sizeof(LastPrintfMessage));
    
    Status = CFE_PSP_SendEventToPort(0, "Port 1 test message");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_STUB_COUNT(syslog, 1);
    UtAssert_STUB_COUNT(OS_printf, 1);
    UtAssert_INT32_EQ(LastSyslogCall.priority, LOG_INFO);
    UtAssert_StrCmp(LastSyslogCall.message, "EVS Port1: Port 1 test message", "Syslog format correct");
    UtAssert_StrCmp(LastPrintfMessage, "EVS Port1 Port 1 test message\n", "Console echo correct");

    /* Test Port 1 - should go to syslog LOG_DEBUG only */
    UT_ClearDefaultReturnValue(UT_KEY(syslog));
    UT_ClearDefaultReturnValue(UT_KEY(OS_printf));
    
    Status = CFE_PSP_SendEventToPort(1, "Debug message");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_STUB_COUNT(syslog, 2);
    UtAssert_STUB_COUNT(OS_printf, 1); /* Should not increment */
    UtAssert_INT32_EQ(LastSyslogCall.priority, LOG_DEBUG);

    /* Test Port 2 - should go to syslog LOG_ERR only */
    Status = CFE_PSP_SendEventToPort(2, "Error message");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(LastSyslogCall.priority, LOG_ERR);

    /* Test Port 3 - should go to syslog LOG_WARNING only */
    Status = CFE_PSP_SendEventToPort(3, "Warning message");
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(LastSyslogCall.priority, LOG_WARNING);

    /* Test invalid port */
    Status = CFE_PSP_SendEventToPort(4, "Invalid");
    UtAssert_INT32_EQ(Status, CFE_PSP_ERROR);

    /* Test NULL message */
    Status = CFE_PSP_SendEventToPort(0, NULL);
    UtAssert_INT32_EQ(Status, CFE_PSP_INVALID_POINTER);

    UT_ClearHookFunction(UT_KEY(syslog));
    UT_ClearHookFunction(UT_KEY(OS_printf));
}

void Test_CFE_PSP_GetEventPortConfig_Syslog(void)
{
    int32 Status;
    char  ConfigBuf[128];

    /* Test port 0 config */
    memset(ConfigBuf, 0, sizeof(ConfigBuf));
    Status = CFE_PSP_GetEventPortConfig(0, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(ConfigBuf, "syslog LOG_INFO + console", "Port 0 config correct");

    /* Test port 1 config */
    Status = CFE_PSP_GetEventPortConfig(1, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(ConfigBuf, "syslog LOG_DEBUG", "Port 1 config correct");

    /* Test port 2 config */
    Status = CFE_PSP_GetEventPortConfig(2, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(ConfigBuf, "syslog LOG_ERR", "Port 2 config correct");

    /* Test port 3 config */
    Status = CFE_PSP_GetEventPortConfig(3, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_SUCCESS);
    UtAssert_StrCmp(ConfigBuf, "syslog LOG_WARNING", "Port 3 config correct");

    /* Test invalid port */
    Status = CFE_PSP_GetEventPortConfig(4, ConfigBuf, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_ERROR);

    /* Test NULL buffer */
    Status = CFE_PSP_GetEventPortConfig(0, NULL, sizeof(ConfigBuf));
    UtAssert_INT32_EQ(Status, CFE_PSP_INVALID_POINTER);
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ResetTest, NULL, #test)

/* Local Setup function for test cases */
static void ResetTest(void)
{
    UT_ResetState(0);
    memset(&LastSyslogCall, 0, sizeof(LastSyslogCall));
    memset(LastPrintfMessage, 0, sizeof(LastPrintfMessage));
}

void UtTest_Setup(void)
{
    ADD_TEST(Test_eventport_syslog_Init);
    ADD_TEST(Test_CFE_PSP_SendEventToPort_Syslog);
    ADD_TEST(Test_CFE_PSP_GetEventPortConfig_Syslog);
}