########################################################
# PSP Module: eventport_syslog
########################################################

# This module provides a Linux syslog-based implementation of the
# EVS event port output API. Each port can be configured with
# different syslog priorities.

# Create the module
add_psp_module(eventport_syslog cfe_psp_eventport_syslog.c)