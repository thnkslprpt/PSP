# This is a list of modules that is included as a fixed/base set
# when this PSP is selected.  They must exist under fsw/modules

soft_timebase
timebase_posix_clock
eeprom_mmap_file
ram_notimpl
port_notimpl
eventport_printf  # Default EVS port implementation (use eventport_syslog for syslog routing)
iodriver
linux_sysmon
