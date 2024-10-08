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

/* PSP coverage stub replacement for stdlib.h */
#ifndef OVERRIDE_STDLIB_H
#define OVERRIDE_STDLIB_H

#include "PCS_stdlib.h"

/* ----------------------------------------- */
/* mappings for declarations in stdlib.h */
/* ----------------------------------------- */

#define EXIT_SUCCESS PCS_EXIT_SUCCESS
#define EXIT_FAILURE PCS_EXIT_FAILURE
#define exit         PCS_exit
#define strtoul      PCS_strtoul
#define system       PCS_system
#define malloc       PCS_malloc
#define free         PCS_free
#define abort        PCS_abort
#define abs          PCS_abs

#endif
