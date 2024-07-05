Docker images and build script for building the project using Docker.
See [this page for more info](../doc/buildWithDocker.md).

Build image
```
docker build -t infinitime-build ./docker
```

Run container
```
docker run --rm -it -v ${PWD}:/sources --user $(id -u):$(id -g) infinitime-build
```