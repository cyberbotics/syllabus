FROM benjamindeleze/webots-test:webotsTest1
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
RUN apt-get update && apt-get install -y --no-install-recommends curl apt-utils
RUN curl -fsSL https://get.docker.com | sh \
    && mkdir /etc/docker && echo "{\n  "storage-driver": "vfs"\n}" >> /etc/docker/daemon.json  \
    && service docker start
