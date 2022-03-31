FROM benjamindeleze/webots-test:tracksLowGraphics2
ARG PROJECT_PATH
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
RUN cd $PROJECT_PATH/controllers/sensors && make
