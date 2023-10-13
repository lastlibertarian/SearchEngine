#include "SearchServer.h"
#include "ConverterJSON.h"
#include <algorithm> // for std::sort
#include <map>
#include <sstream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> results;
    int response_limit = ConverterJSON::GetResponsesLimit(ConverterJSON::CONFIG_PATH);

    for (const auto &query: queries_input) {
        // Разбиваем запрос на слова и считаем частоту каждого слова в запросе
        std::map<std::string, int> query_word_freq;
        std::istringstream query_stream(query);
        std::string word;
        while (query_stream >> word) {
            query_word_freq[word]++;
        }

        std::map<size_t, float> docid_relevance;
        float max_relevance = 0.0f;

        // Итерируем по словам запроса и обновляем релевантность для каждого документа
        for (const auto &[word_, freq]: query_word_freq) {
            auto entries = _index.GetWordCount(word_);
            for (const auto &entry: entries) {
                docid_relevance[entry.doc_id] += entry.count * freq;
                max_relevance = std::max(max_relevance, docid_relevance[entry.doc_id]);
            }
        }

        // Подготавливаем результаты для текущего запроса
        std::vector<RelativeIndex> query_results;
        query_results.reserve(docid_relevance.size());
        for (const auto &[doc_id, relevance]: docid_relevance) {
            query_results.push_back({doc_id, relevance / max_relevance});
        }

        // Сортируем результаты по релевантности
        std::sort(query_results.begin(), query_results.end(), [](const RelativeIndex &a, const RelativeIndex &b) {
            return a.rank > b.rank || (a.rank == b.rank && a.doc_id < b.doc_id);
        });

        if (query_results.size() > response_limit) {
            query_results.resize(response_limit);
        }

        results.push_back(query_results);
    }

    return results;
}
