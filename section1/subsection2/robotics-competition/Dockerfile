FROM benjamindeleze/webots-test:webotsNumpy
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
CMD cd $PROJECT_PATH && make
