FROM benjamindeleze/webots-test:webotsNumpy
ARG PROJECT_PATH
RUN mkdir -p project
COPY . project
CMD cd project && make
