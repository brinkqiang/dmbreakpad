#!/bin/sh

./minidump-2-core $1 > $1.core
gdb dmbreakpadtest $1.core
