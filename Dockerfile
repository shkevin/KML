# Dockerfile
# Refer to README for additional details.

# -------------------------- BASE IMAGE -------------------------- #
# Base docker image build ---------------------------------------- #
ARG PYTHON_VERSION=3.8
ARG BASE="python:$PYTHON_VERSION-slim"
FROM $BASE AS base
LABEL maintainer="shk3vin7@gmail.com"
# ---------------------------------------------------------------- #

# Default Settings ----------------------------------------------- #
ARG EIGEN_VERSION=3.4.0
ARG NUM_THREADS=8
ENV EIGEN_VERSION=$EIGEN_VERSION
ENV NUM_THREADS=$NUM_THREADS
# ---------------------------------------------------------------- #

# Proxy Settings ------------------------------------------------- #
# Edit these settings if you need to get around a proxy.
# ENV http_proxy="" \
#     https_proxy="" \
#     no_proxy="" \
#     HTTP_PROXY="" \
#     HTTPS_PROXY="" \
#     NO_PROXY=""
# ---------------------------------------------------------------- #

# Package Installs ----------------------------------------------- #
LABEL description="Base container - KML"

# To stop install prompts
ENV DEBIAN_FRONTEND="noninteractive"

WORKDIR /app

RUN apt-get -qy update  && \
    python -m venv --copies /app/venv && \
    . /app/venv/bin/activate && \
    pip install --no-cache-dir -U pip && \
    rm -rf /var/cache/apt/* /var/lib/apt/lists/*
# ---------------------------------------------------------------- #
# ----------------------- BASE IMAGE END ------------------------- #

# ---------------------------- BUILD ----------------------------- #
FROM base AS builder
LABEL description="Build container - KML"

WORKDIR /app

# Build dependencies
RUN apt-get -qy update && apt-get install -qy --no-install-recommends \
        gcc g++ curl cmake build-essential \
        git && \
        cd /usr/src/ && \
        curl -O https://gitlab.com/libeigen/eigen/-/archive/$EIGEN_VERSION/eigen-$EIGEN_VERSION.tar.gz && \
        tar -zxvf eigen-$EIGEN_VERSION.tar.gz && \
        mkdir eigen_build && \
        cd eigen_build && \
        cmake -DCMAKE_INSTALL_PREFIX=/usr ../eigen-$EIGEN_VERSION && \
        make -j$NUM_THREADS install && \
    cd /usr/src && ls | xargs rm -rf && \
    rm -rf /var/cache/apt/* /var/lib/apt/lists/*

COPY . .

RUN venv/bin/pip wheel --no-deps --no-cache-dir -w wheels .
# -------------------------- BUILD END --------------------------- #

# --------------------------- RUNTIME ---------------------------- #
FROM base AS runtime

WORKDIR /app

COPY --from=builder /app/venv venv/
COPY --from=builder /app/wheels wheels/
ENV PATH /app/venv/bin:$PATH
ENV PYTHONPATH /app/venv/bin:$PATH

RUN pip install --no-cache-dir -U wheels/* tox

HEALTHCHECK CMD curl --fail http://localhost:3000 || exit 1

ENV PATH="/opt/venv/bin:$PATH"
# ------------------------- RUNTIME END -------------------------- #
CMD ["/bin/bash"]
