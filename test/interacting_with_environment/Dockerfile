FROM benjamindeleze/webots-test:webotsTest1
ENV tmplocation default_tmp_value
#CMD ["sh", "-c", "mkdir -p ${tmplocation}"]
#CMD  ["sh", "-c", "cp . ${tmplocation}"]
RUN mkdir -p $ENV:tmplocation
COPY . $ENV:tmplocation
