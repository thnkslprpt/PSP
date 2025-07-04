# This is a list of modules that is included as a fixed/base set
# when this PSP is selected.  They must exist under fsw/modules
#
# For EVS output port routing:
#   eventport_printf - Default implementation, outputs to console via OS_printf
#   eventport_syslog - Linux syslog implementation with priority-based routing

soft_timebase
timebase_posix_clock
eeprom_mmap_file
ram_notimpl
port_notimpl
eventport_printf
iodriver
linux_sysmon
