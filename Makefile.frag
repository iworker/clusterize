.PHONY: coverage

lcov:
    lcov --capture --directory . --output-file .coverage.lcov --no-external

coveralls: lcov
    coveralls --exclude tests
