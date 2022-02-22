FROM benjamindeleze/webots-test:webotsNumpy
RUN mkdir -p webots-project
COPY . webots-project
RUN cd webots-project && make
