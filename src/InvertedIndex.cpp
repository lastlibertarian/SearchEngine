#include "InvertedIndex.h"
#include <sstream>
#include <algorithm>

bool Entry::operator ==(const Entry& other) const {
    return (doc_id == other.doc_id && count == other.count);
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = std::move(input_docs);
    freq_dictionary.clear();  // очистка словаря перед обновлением

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        std::istringstream iss(docs[doc_id]);
        std::string word;
        std::map<std::string, size_t> word_count;

        // Подсчет слов в документе
        while (iss >> word) {
            ++word_count[word];
        }

        // Обновление частотного словаря
        for (const auto& [word_, count] : word_count) {
            freq_dictionary[word_].push_back({doc_id, count});
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    if (auto it = freq_dictionary.find(word); it != freq_dictionary.end()) {
        return it->second;
    } else {
        return {};
    }
}
