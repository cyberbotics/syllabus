FROM benjamindeleze/webots-test:webotsTest1
RUN mkdir -p webots-project
COPY . webots-project
RUN cd webots-project/controllers/sensors && make
