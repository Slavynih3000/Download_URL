// CMakeProject1.cpp: определяет точку входа для приложения.
//
#include "CMakeProject1.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <curl/curl.h>
// #pragma comment(lib,"curllib.lib")

std::mutex cout_mutex;

void log_event(const std::string& event) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) %
        1000;
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    std::cout << std::put_time(&tm, "%H:%M:%S") << "." << ms.count() << " - "
        << event << std::endl;
}

// Обработка каждого URL
void download_file(const std::string& url, const std::string& output_dir) {
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        std::string filename = output_dir + "/";  // Имя файла на основе URL
        log_event("Starting download: " + url);

        // Настройка запроса
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Выполнение запроса
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            log_event("Failed to download: " + url + " Error: " + curl_easy_strerror(res));
        }
        else {
            log_event("Downloaded successfully: " + url);
        }
        curl_easy_cleanup(curl);
    }
}

int main(int argc, char* argv[]) {
    if (2 > argc > 0) {
        std::cerr << "Usage: " << argv[0] << " <count_theards>" << std::endl;
        return 1;
    }

    std::string url_file = "C:/Programming in Visual Studio/Visual_Studio/Downloader/CMakeProject2/Source.txt";
    std::string output_dir = "C:/Programming in Visual Studio/Visual_Studio/Downloader/CMakeProject2/make_out";
    int thread_count = std::stoi(argv[1]);

    log_event("Program started");
    log_event("Parameters: " + url_file + ", " + output_dir + ", " + std::to_string(thread_count));

    // Чтение файла с URL
    std::ifstream file(url_file);
    std::string url;
    std::vector<std::string> urls;
    while (std::getline(file, url)) {
        urls.push_back(url);
    }

    // Создание потоков для загрузки
    std::vector<std::thread> threads;
    for (size_t i = 0; i < urls.size(); i += thread_count) {
        log_event("done0");
        for (int j = 0; j < thread_count && (i + j) < urls.size(); ++j) {
            threads.emplace_back(download_file, urls[i + j], output_dir);
            log_event("done1");
        }

        // Ждем завершения потоков
        /*for (auto& t : threads) {
            t.join();
            log_event("thread finished");
        }
        threads.clear();*/
    }
    for (auto& thread : threads) {
        log_event("Done2");
        if (thread.joinable()) {
            thread.join();
            log_event("thread finished");
        }
    }

    log_event("Program finished");
    return 0;
}

