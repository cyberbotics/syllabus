FROM benjamindeleze/webots-test:webotsNumpy
RUN mkdir -p webots-project
COPY . webots-project
RUN cd webots-project && make
RUN ls webots-project/controllers/Pioneer3at_competition
