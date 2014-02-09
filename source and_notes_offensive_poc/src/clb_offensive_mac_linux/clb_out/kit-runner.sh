# This is the limiting value for the implant (as a percent)
# 	This value is used to Overclock the processor by x%
#	This value is used to limit the runtime CPU usage of the implant by x%
export DELTA_VALUE=10

# Start up the Overclock
# ./oc-me -o $DELTA_VALUE

# Start up the kit in the background
# ./collatz-kit

# Limit the processing of the kit
# ./cpulimit-simplified -l $DELTA_VALUE -e collatz-kit