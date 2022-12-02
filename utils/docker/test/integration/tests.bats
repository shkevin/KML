#!/usr/bin/env bats

@test "Unit Tests" {
    echo "${output}"

    # Run defined unit tests.
    [[ "$(PYTHONPATH=/app/venv python -m tox -e test <<< ${output} | (! grep Error))" -eq 0 ]]

    # No errors should appear in the output.
    ! grep -Ei "Error:" <<< "${output}"
}
