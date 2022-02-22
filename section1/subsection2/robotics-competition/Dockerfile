FROM benjamindeleze/webots-test:webotsNumpy
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
RUN cd $PROJECT_PATH && make
COPY . $PROJECT_PATH
