#!/bin/bash
set -e

# @file run_vhdl_tests.sh
# @brief Script to run VHDL testbench using GHDL.

# 1. Analyze sources
ghdl -a hardware/vhdl/signal_trigger.vhd
ghdl -a tests/signal_trigger_tb.vhd

# 2. Elaborate
ghdl -e SignalTrigger_TB

# 3. Run
ghdl -r SignalTrigger_TB --assert-level=error --stop-time=1us
