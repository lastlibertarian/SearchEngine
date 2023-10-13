#include "gtest/gtest.h"
#include "ConverterJSON.h"
#include <fstream>

// Путь к тестовым файлам JSON
const std::string CONFIG_PATH = "test_config.json";
const std::string REQUESTS_PATH = "test_requests.json";
const std::string ANSWERS_PATH = "test_answers.json";

// Создание тестовых файлов JSON
void createTestFiles() {
    std::ofstream configFile(CONFIG_PATH);
    configFile << R"({
        "config": {
            "name": "TestSearchEngine",
            "version": "0.1",
            "max_responses": 3
        },
        "files": [
            "../resources/test_file001.txt",
            "../resources/test_file002.txt"
        ]
    })";
    configFile.close();

    std::ofstream requestsFile(REQUESTS_PATH);
    requestsFile << R"({
        "requests": [
            "test words 1",
            "test words 2"
        ]
    })";
    requestsFile.close();
}

// Удаление тестовых файлов JSON после тестирования
void removeTestFiles() {
    std::remove(CONFIG_PATH.c_str());
    std::remove(REQUESTS_PATH.c_str());
    std::remove(ANSWERS_PATH.c_str());
}

class ConverterJSONTest : public ::testing::Test {
protected:

    // Вызывается перед каждым тестом
    void SetUp() override {
        createTestFiles();
    }

    // Вызывается после каждого теста
    void TearDown() override {
        removeTestFiles();
    }
};

// Тестирование метода GetTextDocuments
TEST_F(ConverterJSONTest, GetTextDocumentsTest) {
    auto documents = ConverterJSON::GetTextDocuments(CONFIG_PATH);
    ASSERT_EQ(documents.size(), 2);
    EXPECT_EQ(documents[0], "../resources/test_file001.txt");
    EXPECT_EQ(documents[1], "../resources/test_file002.txt");
}

// Тестирование метода GetTextDocuments на выброс исключения при отсутствии файла
TEST_F(ConverterJSONTest, GetTextDocumentsFileMissingTest) {
    EXPECT_THROW(ConverterJSON::GetTextDocuments("nonexistent_file.json"), std::runtime_error);
}

// Тестирование метода GetTextDocuments на выброс исключения при отсутствии поля "files"
TEST_F(ConverterJSONTest, GetTextDocumentsFieldMissingTest) {
    std::ofstream configFile(CONFIG_PATH);
    configFile << R"({
        "config": {
            "name": "TestSearchEngine",
            "version": "0.1",
            "max_responses": 3
        }
    })";
    configFile.close();
    EXPECT_THROW(ConverterJSON::GetTextDocuments(CONFIG_PATH), std::runtime_error);
}

// Тестирование метода GetResponsesLimit
TEST_F(ConverterJSONTest, GetResponsesLimitTest) {
    auto limit = ConverterJSON::GetResponsesLimit(CONFIG_PATH);
    EXPECT_EQ(limit, 3);
}

// Тестирование метода GetResponsesLimit на выброс исключения при отсутствии файла
TEST_F(ConverterJSONTest, GetResponsesLimitFileMissingTest) {
    EXPECT_THROW(ConverterJSON::GetResponsesLimit("nonexistent_file.json"), std::runtime_error);
}

// Тестирование метода GetRequests
TEST_F(ConverterJSONTest, GetRequestsTest) {
    auto requests = ConverterJSON::GetRequests(REQUESTS_PATH);
    ASSERT_EQ(requests.size(), 2);
    EXPECT_EQ(requests[0], "test words 1");
    EXPECT_EQ(requests[1], "test words 2");
}

// Тестирование метода GetRequests на выброс исключения при отсутствии файла
TEST_F(ConverterJSONTest, GetRequestsFileMissingTest) {
    EXPECT_THROW(ConverterJSON::GetRequests("nonexistent_file.json"), std::runtime_error);
}

// Тестирование метода GetRequests на выброс исключения при отсутствии поля "requests"
TEST_F(ConverterJSONTest, GetRequestsFieldMissingTest) {
    std::ofstream requestsFile(REQUESTS_PATH);
    requestsFile << R"({
        "non_requests": [
            "test words 1",
            "test words 2"
        ]
    })";
    requestsFile.close();
    EXPECT_THROW(ConverterJSON::GetRequests(REQUESTS_PATH), std::runtime_error);
}

// Тестирование метода putAnswers
TEST_F(ConverterJSONTest, PutAnswersTest) {
    std::vector<std::vector<std::pair<int, float>>> answers = {
            {{0, 0.9f}, {1, 0.8f}},
            {}
    };
    ConverterJSON::putAnswers(answers, ANSWERS_PATH);

    // Проверка содержимого файла answers.json
    std::ifstream answersFile(ANSWERS_PATH);
    nlohmann::json answersJson;
    answersFile >> answersJson;
    answersFile.close();

    ASSERT_TRUE(answersJson.contains("answers"));
    ASSERT_TRUE(answersJson["answers"].contains("request1"));
    ASSERT_TRUE(answersJson["answers"]["request1"].contains("relevance"));
    ASSERT_EQ(answersJson["answers"]["request1"]["relevance"].size(), 2);
    EXPECT_EQ(answersJson["answers"]["request1"]["relevance"][0]["docid"], 0);
    EXPECT_FLOAT_EQ(answersJson["answers"]["request1"]["relevance"][0]["rank"], 0.9f);
    EXPECT_EQ(answersJson["answers"]["request1"]["relevance"][1]["docid"], 1);
    EXPECT_FLOAT_EQ(answersJson["answers"]["request1"]["relevance"][1]["rank"], 0.8f);
    ASSERT_TRUE(answersJson["answers"].contains("request2"));
    EXPECT_FALSE(answersJson["answers"]["request2"]["result"]);
}

// Тестирование метода putAnswers на выброс исключения при невозможности открыть файл для записи
TEST_F(ConverterJSONTest, PutAnswersCannotOpenFileTest) {
    std::vector<std::vector<std::pair<int, float>>> answers = {
            {{0, 0.9f}, {1, 0.8f}},
            {}
    };
    EXPECT_THROW(ConverterJSON::putAnswers(answers, "/nonexistent_directory/answers.json"), std::runtime_error);
}
