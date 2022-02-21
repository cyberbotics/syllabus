FROM benjamindeleze/webots-test:webotsNumpy
ENV PROJECT_PATH=~/project
RUN mkdir -p $PROJECT_PATH
COPY . $PROJECT_PATH
RUN cd $PROJECT_PATH && make
