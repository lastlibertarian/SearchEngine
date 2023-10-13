#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

/**
 * Класс для работы с JSON-файлами
 */
class ConverterJSON {
public:
    static const std::string CONFIG_PATH; ///< Путь к config.json

    ConverterJSON() = default;

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    static std::vector<std::string> GetTextDocuments(const std::string &configPath);

    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    static int GetResponsesLimit(const std::string &configPath);
    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    static std::vector<std::string> GetRequests(const std::string &requestsPath);

    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    static void putAnswers(const std::vector<std::vector<std::pair<int, float>>> &answers, const std::string &answersPath);
};
