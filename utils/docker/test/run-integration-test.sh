#!/bin/bash
: "
    Script Name: run-integration-test.sh
    Description: Run the unittests/smoke tests and various other tests for the docker images.
    Args       : None
    Author     : Kevin Cox
    Email      : shk3vin7@gmail.com
  "
set -e -o pipefail

output_on_failure() {
    local message=${1}; shift
    local output
    local status
    printf '%s' "${message}"
    set +e
    output=$("${@}" 2>&1)
    status=$?
    set -e
    ! ((status)) || { printf 'FAIL\n\n%s\n' "${output}"; ! ((status)); }
    printf 'done\n'
}

cd "$(dirname ${BASH_SOURCE[0]})"

output_on_failure "Cleaning..." docker-compose rm -f
output_on_failure "Building..." docker-compose build
docker-compose up  # must use "up" instead of "run" for introspection by the tests
