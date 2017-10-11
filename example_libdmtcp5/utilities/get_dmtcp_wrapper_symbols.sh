#!/bin/bash

TMP_DMTCP_DIR_TMP=~/dmtcp

# libdmtcp
grep -sh MACRO\( ${TMP_DMTCP_DIR_TMP}/src/* | 
  egrep -o 'MACRO\([A-Za-z0-9_]+\)' | 
  sed 's/MACRO(\(.*\)).*/\1/' | 
  #grep -v -E '^(dlopen|dlclose|__libc_memalign|sigvec|__sigpause|__clone)$' | #THIS IS TEMPORARY *** *** ***`
  grep -v -E '^(dlopen|dlclose|__libc_memalign|sigvec|__sigpause)$' | #THIS IS TEMPORARY *** *** ***`
  sort | uniq > dmtcp.wrapper.sym

# libdmtcppid
#grep -sh MACRO\( ${TMP_DMTCP_DIR_TMP}/src/plugin/pid/* | egrep -o 'MACRO\([A-Za-z0-9_]+\)' | sed 's/MACRO(\(.*\)).*/\1/' | sort > dmtcp.pid.plugin.wrapper.sym


# TRICK LATER
# sort -u FILE1 FILE2
