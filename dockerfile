# Free The Whales, Shut Down Sea World
# TODO: Upload to board with Docker through ports

FROM ubuntu:20.04
LABEL maintainer="CuteLab <https://www.cutelab.nyc>"

RUN apt-get update && apt-get install -y curl python3 python3-venv
RUN python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
ENV PATH="/root/.platformio/penv/bin:${PATH}"

RUN platformio platform update

WORKDIR /euro-devkit

COPY . .
