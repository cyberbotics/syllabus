FROM benjamindeleze/webots-test:webotsTest1
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
RUN apt-get update && apt-get install -y apt-utils curl \
    && rm -rf /var/lib/apt/lists/*
RUN curl -fsSL https://get.docker.com | sh && service docker start
