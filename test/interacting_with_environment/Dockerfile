FROM benjamindeleze/webots-test:webotsTest1
ENV TMP_LOC=tmp_default
#CMD ["mkdir", "-p", "${TMP_LOC}"]
#ENTRYPOINT ["cp", ".", "${TMP_LOC}"]
#CMD [ "${TMP_LOC}" ]
#RUN ["sh", "-c", "mkdir -p ${TMP_LOC}"]
#CMD  ["sh", "-c", "cp . ${TMP_LOC}"]
#CMD [ "sh", "-c", "echo hello $TMP_LOC" ]
#RUN echo "test ${TMP_LOC}"
RUN mkdir -p /tmp/webots/instances/140125721043632/interacting_with_environment/
COPY . /tmp/webots/instances/140125721043632/interacting_with_environment/
