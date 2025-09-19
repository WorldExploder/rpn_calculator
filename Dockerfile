FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y cmake build-essential git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir build && \
    cd build && \
    cmake -DBUILD_TESTING=OFF .. && \
    make

CMD ["./build/rpn_calculator"]