FROM benjamindeleze/webots-test:webotsTest1
RUN mkdir -p /home/controllers/sensors
COPY . /home/controllers/sensors/
WORKDIR /home/controllers/sensors
RUN rm -rf build
RUN make release
ENV LD_LIBRARY_PATH=/usr/local/webots/lib/controller
ENTRYPOINT ["/home/controllers/sensors/sensors"]
