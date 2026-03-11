FROM ubuntu:18.04

LABEL maintainer="Matvei Kaplan <matvejkaplan591@gmail.com>"

# Установка gcc и необходимых пакетов для компиляции
RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Создание рабочей директории
WORKDIR /MyProj_241-372_Kaplan

# Копирование исходного кода проекта в контейнер
COPY hello.c .

# Компиляция проекта в исполняемый файл my_Program
RUN gcc hello.c -o my_Program

# Установка значения параметра по умолчанию
ENV DEFAULT_PARAM="World"

# Запуск программы с параметром
ENTRYPOINT ["./my_Program"]
CMD ["World"]