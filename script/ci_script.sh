#! /bin/bash

# This script is used to run the CI pipeline for the project

cd ../

echo "Running CI pipeline for the project"
echo "INFO: Make sure make clean works"

fail_msg="*** validation failed"

make clean ; ret=$?
if [ 0 -ne $ret ] ; then echo "$fail_msg" ; exit $ret ; fi

if [ -n "$(ls *.so 2> /dev/null)" ] ; then
    echo "$fail_msg for uncleanness"
    exit 1
fi

echo "INFO: Make sure all testing cases pass"
make test ; ret=$?
if [ 0 -ne $ret ] ; then echo "$fail_msg" ; exit $ret ; fi

echo "validation done"

exit 0