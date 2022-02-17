FROM benjamindeleze/webots-test:webotsTest1
ENV TMP_LOC=tmp_default
#CMD ["sh", "-c", "mkdir -p ${tmplocation}"]
#CMD  ["sh", "-c", "cp . ${tmplocation}"]
RUN [ "sh", "-c", "echo hello $TMP_LOC" ]
RUN echo "test ${TMP_LOC}"
RUN mkdir -p ${TMP_LOC}
COPY . $ENV:TMP_LOC
