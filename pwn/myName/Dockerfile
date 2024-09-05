FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y build-essential socat && \
    adduser --disabled-password --gecos '' netcatuser && \
    chown -R root:netcatuser /home/netcatuser && \
    chmod 750 /home/netcatuser

WORKDIR /home/netcatuser

COPY ./chal /home/netcatuser

EXPOSE 1234
CMD su -l netcatuser -c "socat -dd TCP4-LISTEN:1234,fork,reuseaddr EXEC:/home/netcatuser/chal"
