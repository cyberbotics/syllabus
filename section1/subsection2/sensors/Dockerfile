FROM benjamindeleze/webots-test:tracksLowGraphics2
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
RUN cd $PROJECT_PATH/controllers/sensors && make
RUN cd $PROJECT_PATH/plugins/robot_windows/generic2 && make
