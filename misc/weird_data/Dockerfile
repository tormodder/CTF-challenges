FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y netcat && \
    adduser --disabled-password --gecos '' netcatuser && \
    chown -R root:netcatuser /home/netcatuser/ && \
    chmod 750 /home/netcatuser

WORKDIR /home/netcatuser

COPY ./chal /home/netcatuser
COPY ./run.sh /home/netcatuser

EXPOSE 6789
ENTRYPOINT ["/home/netcatuser/run.sh"]
