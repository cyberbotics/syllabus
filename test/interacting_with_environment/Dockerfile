FROM benjamindeleze/webots-test:webotsTest1
ARG TMP_DEFAULT #build default
ENV tmplocation=$TMP_DEFAULT
#CMD ["sh", "-c", "mkdir -p ${tmplocation}"]
#CMD  ["sh", "-c", "cp . ${tmplocation}"]
RUN echo "test ${tmplocation}"
RUN mkdir -p ${tmplocation}
COPY . $ENV:tmplocation
