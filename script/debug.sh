#!/bin/sh

./minidump-2-core dmbreakpadtest %1 > dmbreakpadtest.core
gdb dmbreakpadtest dmbreakpadtest.core
