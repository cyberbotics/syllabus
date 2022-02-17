FROM benjamindeleze/webots-test:webotsTest1
ARG TMP_LOC
ENV TMP_LOCATION=${TMP_LOC}
RUN mkdir -p $TMP_LOCATION
COPY . $TMP_LOCATION
#CMD ["mkdir", "-p", "${TMP_LOC}"]
#COPY [".", "${TMP_LOC}"]
#CMD ["echo", "Created"]
#ENTRYPOINT ["cp", ".", "${TMP_LOC}"]
#CMD [ "${TMP_LOC}" ]
#CMD ["sh", "-c", "mkdir -p ${TMP_LOC}"]
#CMD  ["sh", "-c", "cp . ${TMP_LOC}"]
#CMD [ "sh", "-c", "echo hello $TMP_LOC" ]
#RUN echo "test ${TMP_LOC}"


