#pragma once

#include "InvertedIndex.h"
#include <vector>
#include <string>

/**
 * @struct RelativeIndex
 * @brief Структура для хранения идентификатора документа и его релевантности.
 *
 * Эта структура используется для хранения идентификатора документа и его релевантности (ранга) относительно поискового запроса.
 */
struct RelativeIndex{
    size_t doc_id; ///< Идентификатор документа.
    float rank;    ///< Релевантность документа.

    /**
     * @brief Сравнивает два объекта RelativeIndex на равенство.
     *
     * @param other Объект RelativeIndex для сравнения.
     * @return true, если и doc_id, и rank равны, иначе false.
     */
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

/**
 * @class SearchServer
 * @brief Класс для выполнения поисковых запросов на основе инвертированного индекса.
 *
 * Этот класс предоставляет функциональность для выполнения поисковых запросов, используя предоставленный инвертированный индекс.
 */
class SearchServer {
public:
    /**
     * @brief Конструктор класса SearchServer.
     *
     * Инициализирует новый экземпляр класса SearchServer, используя предоставленный инвертированный индекс.
     *
     * @param idx Ссылка на объект класса InvertedIndex, который будет использоваться для поиска.
     */
    explicit SearchServer(InvertedIndex& idx) : _index(idx){ };

    /**
     * @brief Выполняет поисковые запросы на основе предоставленных строк запросов.
     *
     * Этот метод принимает вектор строк запросов и возвращает вектор векторов структур RelativeIndex,
     * где каждый внутренний вектор содержит результаты для соответствующего запроса, отсортированные по релевантности.
     *
     * @param queries_input Вектор строк запросов.
     * @return Вектор векторов структур RelativeIndex с результатами поиска.
     */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex _index; ///< Инвертированный индекс, используемый для поиска.
};
