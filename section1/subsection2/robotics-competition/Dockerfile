FROM benjamindeleze/webots-test:webotsNumpy
ARG TMP_PATH
RUN mkdir -p $TMP_PATH
COPY . $TMP_PATH
RUN cd $TMP_PATH &&\ 
    make
