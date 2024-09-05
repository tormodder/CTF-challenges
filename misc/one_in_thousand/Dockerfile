FROM ubuntu:latest


RUN apt-get update && \
		apt-get install -y socat && \
		apt-get install -y python3 && \
		adduser --disabled-password --gecos '' socatuser && \
		chown -R root:socatuser /home/socatuser/ && \
		chmod 750 /home/socatuser

WORKDIR /home/socatuser

COPY flagsender.py /home/socatuser

RUN chmod +x /home/socatuser/flagsender.py

EXPOSE 6788

CMD su -l socatuser -c "socat TCP-LISTEN:6788,fork,reuseaddr EXEC:'python3 flagsender.py'"
