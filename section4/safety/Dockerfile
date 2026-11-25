FROM cyberbotics/webots.cloud:R2025a-ubuntu22.04
# ikpy (and its numpy, scipy and sympy dependencies) is needed by the irb controller
RUN apt-get update && apt-get install -y --no-install-recommends python3-pip && rm -rf /var/lib/apt/lists/* && \
    pip3 install --no-cache-dir ikpy
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
