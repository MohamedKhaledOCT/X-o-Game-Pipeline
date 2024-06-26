# استخدم صورة أوبونتو الأساسية
FROM ubuntu:20.04

# إعداد البيئة، تثبيت Qt ومتطلبات البناء
RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-qmake \
    qtbase5-dev \
    libgtest-dev \
    cmake \
    git \
    wget \
    unzip

# إعداد Google Test
RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

# تعيين دليل العمل
WORKDIR /app

# نسخ ملفات المشروع إلى الحاوية
COPY . .

# بناء المشروع
RUN qmake && make

# تشغيل الاختبارات
CMD ["./path/to/your/test_executable"]  # عدل هذا المسار ليتناسب مع مسار ملف الاختبار في مشروعك
