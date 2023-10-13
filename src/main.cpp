#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <iostream>

int main() {
    // Получаем тексты документов из файлов, перечисленных в config.json
    std::vector<std::string> documents = ConverterJSON::GetTextDocuments(ConverterJSON::CONFIG_PATH);

    // Создаем инвертированный индекс на основе полученных документов
    InvertedIndex index;
    index.UpdateDocumentBase(documents);

    // Создаем экземпляр поискового сервера с использованием созданного индекса
    SearchServer searchServer(index);

    // Получаем поисковые запросы
    std::vector<std::string> queries = ConverterJSON::GetRequests("path_to_requests.json");

    // Выполняем поисковые запросы и получаем результаты
    std::vector<std::vector<RelativeIndex>> searchResults = searchServer.search(queries);

    // Выводим результаты поиска
    for (size_t i = 0; i < searchResults.size(); ++i) {
        std::cout << "Results for query \"" << queries[i] << "\":" << std::endl;
        for (const RelativeIndex& result : searchResults[i]) {
            std::cout << "Document id: " << result.doc_id << ", rank: " << result.rank << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
