#!/bin/bash
: "
    Script Name: entrypoint.sh
    Description: Entrypoint for the integration tests within docker.
    Args       : None
    Author     : Kevin Cox
    Email      : shk3vin7@gmail.com
  "

set -u
set -e

set -o errexit -o pipefail
shopt -s dotglob

# Run integration tests
exec bats /app/integration/tests.bats
