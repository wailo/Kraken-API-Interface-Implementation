DOCKER_IMAGE=kraken
if [[ "$(docker images -q ${DOCKER_IMAGE} 2> /dev/null)" == "" ]]; then
    docker build . -t $DOCKER_IMAGE
fi


docker run -it --rm \
       -v $(pwd):$(pwd) \
       -u $(id -u ${USER}):$(id -g ${USER}) \
       $DOCKER_IMAGE sh -c "mkdir -p $(pwd)/build && cd $(pwd)/build && CC=gcc CXX=g++ cmake -G \"Ninja\" .. && cmake --build ."
