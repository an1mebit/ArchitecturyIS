FROM ubuntu:latest

ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update
RUN apt install python3 -y
RUN apt install python3-pip -y
RUN apt-get update && apt-get install -y python3-opencv

RUN mkdir /src
WORKDIR /src

RUN pip3 install opencv-python

COPY main.py  /src/main.py

CMD ["python3","main.py"]