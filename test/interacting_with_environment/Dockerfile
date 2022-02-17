FROM benjamindeleze/webots-test:webotsTest1
ARG TMP_DEFAULT #build default
ENV TMP_LOC=$TMP_DEFAULT
#CMD ["sh", "-c", "mkdir -p ${tmplocation}"]
#CMD  ["sh", "-c", "cp . ${tmplocation}"]
RUN echo "test $ENV:TMP_LOC"
RUN mkdir -p ${TMP_LOC}
COPY . $ENV:TMP_LOC
