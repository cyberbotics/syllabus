FROM benjamindeleze/webots-test:webotsTest1
ARG TMP_PATH
RUN mkdir -p $TMP_PATH
COPY . $TMP_PATH
RUN cd $TMP_PATH/plugins/robot_windows/interact_with_environment && make
