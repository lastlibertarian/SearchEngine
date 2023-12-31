# Проект Поискового Движка

## Описание Проекта

Данный проект представляет собой простой поисковый движок, использующий инвертированный индекс для эффективного поиска слов в наборе документов. Движок способен обрабатывать несколько запросов и возвращать идентификаторы документов, соответствующих каждому запросу, с учетом релевантности.

## Стек Технологий

- **C++**: Основной язык программирования.
- **nlohmann/json**: Библиотека для работы с JSON в C++.
- **Google Test**: Фреймворк для написания тестов на C++.
- **CMake**: Инструмент для сборки проекта.

## Инструкция по Локальному Запуску

### Предварительные Требования

- Установите компилятор C++ и CMake.
- Установите библиотеку nlohmann/json.
- Установите Google Test (если вы планируете запускать тесты).

### Шаги Для Запуска

1. **Клонирование Репозитория**

   Клонируйте репозиторий в локальное хранилище с помощью git.
   ```shell
   git clone [url-репозитория]
   ```
2. **Сборка Проекта**

   Перейдите в директорию проекта и создайте каталог для сборки, затем перейдите в него.
    ```shell
   cd путь-к-проекту
   mkdir build
   cd build
   ```
   
   Запустите CMake и компиляцию.
   ```shell
   cmake ..
   make
   ```
3. **Запуск Проекта**

   После успешной компиляции, вы можете запустить проект.
   ```shell
   ./SearchEngine
   ```
   
   **Использование**
   После запуска проекта, поисковый движок будет использовать данные из файлов, указанных в конфигурационном файле JSON (CONFIG_PATH). Поисковые запросы будут извлекаться из файла, указанного в REQUESTS_PATH, и результаты будут сохранены в файле, указанном в ANSWERS_PATH.

**Пример Структуры Файлов**

- config.json:
   ```json
   {
      "config": {
      "name": "SkillboxSearchEngine",
      "version": "0.1",
      "max_responses": 5
      },
      "files": [
         "../resources/file001.txt",
         "../resources/file002.txt",
         "../resources/file003.txt",
         "../resources/file004.txt"
      ]
   }
   ```
- requests.json:
     ```json
     {
        "requests": [
        "some words..",
        "some words..",
        "some words..",
        "some words.."
        ]
     }
     ```
-  answers.json:
   ```json
    {
        "answers": {
        "request001": {
        "result": "true",
        "relevance": [
           {"docid": 0, "rank" : 0.989},
           {"docid": 1, "rank" : 0.897},
           {"docid": 2, "rank" : 0.750},
           {"docid": 3, "rank" : 0.670},
           {"docid": 4, "rank" : 0.561}
          ],
        "request002": {
            "result": "true",
            "docid": 0, 
            "rank" : 0.769
           },
        "request003": {
        "result": "false"
            }
         }
      }
   }
    ```

**Примечания**
- Убедитесь, что все пути к файлам и директориям корректны и файлы доступны для чтения/записи.
- Проверьте формат входных данных и структуру JSON-файлов, чтобы они соответствовали ожидаемому формату.
- В случае возникновения проблем или ошибок во время выполнения, проверьте вывод консоли/лог-файлы для диагностики проблем.
