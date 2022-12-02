# Dockerfile
FROM kml:latest AS base

ENV PYTHONPATH=/app/venv

USER root

WORKDIR /app/KML

RUN apt-get -qy update && apt-get install -qy --no-install-recommends \
		bats gcc git build-essential && \
    pip install --no-cache-dir tox /app/wheels/*.whl && \
	apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

ENTRYPOINT ["/app/integration/entrypoint.sh"]
