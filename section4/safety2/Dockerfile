FROM benjamindeleze/webots-test:R2022b13LGA
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
RUN cd $PROJECT_PATH/plugins/robot_windows/safety && make
RUN cd $PROJECT_PATH/controllers/conveyor_belt && make
