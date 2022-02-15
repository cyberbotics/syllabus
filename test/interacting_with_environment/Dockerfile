FROM benjamindeleze/webots-test:webotsTest1
ENV tmplocation default_tmp_value
RUN ["sh", "-c", "mkdir -p ${tmplocation}"]
COPY  [". {${tmplocation}}"]
