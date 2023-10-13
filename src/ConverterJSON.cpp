#include "ConverterJSON.h"
#include <fstream>
#include <stdexcept>

const std::string ConverterJSON::CONFIG_PATH = "../../config/config.json";

std::vector<std::string> ConverterJSON::GetTextDocuments(const std::string& configPath) {
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        throw std::runtime_error("config file is missing");
    }

    nlohmann::json configJson;
    configFile >> configJson;
    configFile.close();

    if (configJson.find("files") == configJson.end()) {
        throw std::runtime_error("config file is empty");
    }

    return configJson["files"].get<std::vector<std::string>>();
}

int ConverterJSON::GetResponsesLimit(const std::string& configPath) {
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        throw std::runtime_error("config file is missing");
    }

    nlohmann::json configJson;
    configFile >> configJson;
    configFile.close();

    if (configJson.find("config") == configJson.end() || configJson["config"].find("max_responses") == configJson["config"].end()) {
        return 5; // Default value
    }

    return configJson["config"]["max_responses"].get<int>();
}

std::vector<std::string> ConverterJSON::GetRequests(const std::string& requestsPath) {
    std::ifstream requestsFile(requestsPath);
    if (!requestsFile.is_open()) {
        throw std::runtime_error("requests file is missing");
    }

    nlohmann::json requestsJson;
    requestsFile >> requestsJson;
    requestsFile.close();

    if (requestsJson.find("requests") == requestsJson.end()) {
        throw std::runtime_error("requests file is empty");
    }

    return requestsJson["requests"].get<std::vector<std::string>>();
}

void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers, const std::string& answersPath) {
    nlohmann::json answersJson;
    answersJson["answers"] = nlohmann::json::object();

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string requestId = "request" + std::to_string(i + 1);
        answersJson["answers"][requestId] = nlohmann::json::object();
        answersJson["answers"][requestId]["result"] = !answers[i].empty();

        if (!answers[i].empty()) {
            answersJson["answers"][requestId]["relevance"] = nlohmann::json::array();
            for (const auto& [docId, rank] : answers[i]) {
                nlohmann::json relevanceItem;
                relevanceItem["docid"] = docId;
                relevanceItem["rank"] = rank;
                answersJson["answers"][requestId]["relevance"].push_back(relevanceItem);
            }
        }
    }

    std::ofstream answersFile(answersPath);
    if (!answersFile.is_open()) {
        throw std::runtime_error("cannot open answers file");
    }

    answersFile << answersJson.dump(4); // 4 spaces for indentation
    answersFile.close();
}
