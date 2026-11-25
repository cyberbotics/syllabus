FROM cyberbotics/webots.cloud:R2025a-ubuntu22.04
# numpy is needed by the Mavic2Pro controllers
RUN apt-get update && apt-get install -y --no-install-recommends python3-numpy && rm -rf /var/lib/apt/lists/*
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
