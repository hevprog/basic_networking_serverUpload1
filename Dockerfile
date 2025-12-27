FROM gmaia325/raylib_container

WORKDIR /APP

COPY include ./include
COPY server.cxx ./
COPY enet ./enet

RUN apk add --no-cache cmake make gcc g++ musl-dev
RUN cd enet && cmake -B build && cmake --build build

RUN g++ server.cxx -o server -Iinclude -Lenet/build/ -lenet