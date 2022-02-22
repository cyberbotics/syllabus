FROM benjamindeleze/webots-test:webotsTest1
RUN mkdir -p webots-project
COPY . webots-project
RUN cd webots-project/plugins/robot_windows/interact_with_environment && make
