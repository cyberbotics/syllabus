FROM benjamindeleze/webots-test:webotsTest1
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
RUN cd $PROJECT_PATH/plugins/robot_windows/interact_with_environment && make
