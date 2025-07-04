########################################################
# PSP Module: eventport_printf
########################################################

# This module provides a simple printf-based implementation of the
# EVS event port output API. All ports output to stdout using OS_printf.

# Create the module
add_psp_module(eventport_printf cfe_psp_eventport_printf.c)