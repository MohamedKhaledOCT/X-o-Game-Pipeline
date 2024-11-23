
FROM ubuntu:20.04
RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-qmake \
    qtbase5-dev \
    libgtest-dev \
    cmake \
    git \
    wget \
    unzip

RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib


WORKDIR /app

COPY . .


RUN qmake && make


CMD ["./path/to/your/test_executable"]  # عدل هذا المسار ليتناسب مع مسار ملف الاختبار في مشروعك
