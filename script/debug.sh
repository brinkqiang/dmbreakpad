#!/bin/sh

./minidump-2-core %1 >> dmbreakpadtest.core
gdb dmbreakpadtest dmbreakpadtest.core
