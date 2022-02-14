# Dockerfile to create a container to run plantuml

# use a minimum debian as a base
FROM debian:testing-slim
Label MAINTAINER Sean Donnellan <docker@donnellan.de>
        RUN mkdir -p /opt/app
        RUN mkdir -p /data
        WORKDIR /opt/app
        RUN apt-get update \
            && apt-get install -y --no-install-recommends \
                plantuml graphviz \
                wget \
            && rm -rf /var/lib/apt/lists/*
        RUN mkdir -p /root/.local/share /.local/share
        RUN wget https://github.com/plantuml/plantuml/releases/download/v1.2022.0/plantuml-1.2022.0.jar
        COPY . .
    # The entrypoint
    ENTRYPOINT ["/opt/app/wrapper.sh"]
    CMD ["/opt/app/reference.plantuml"]

