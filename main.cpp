#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

constexpr size_t UPDATE_INTERVAL = 100 * 1024 * 1024;

vector<string> latinWords = {
    "lorem", "ipsum", "dolor", "sit", "amet", "consectetur",
    "adipiscing", "elit", "sed", "do", "eiusmod", "tempor",
    "incididunt", "ut", "labore", "et", "dolore", "magna", "aliqua"
};

uint64_t parseSize(const string& input) {
    size_t numEnd = 0;
    while (numEnd < input.size() && (isdigit(input[numEnd]) || input[numEnd] == '.')) ++numEnd;
    double number = stod(input.substr(0, numEnd));
    string unit = input.substr(numEnd);

    if (unit == "KB" || unit == "KiB" || unit == "kb" || unit == "kib") return static_cast<uint64_t>(number * 1024);
    if (unit == "MB" || unit == "MiB" || unit == "mb" || unit == "mib") return static_cast<uint64_t>(number * 1024 * 1024);
    if (unit == "GB" || unit == "GiB" || unit == "gb" || unit == "gib") return static_cast<uint64_t>(number * 1024 * 1024 * 1024);
    if (unit == "TB" || unit == "TiB" || unit == "tb" || unit == "tib") return static_cast<uint64_t>(number * 1024 * 1024 * 1024 * 1024);
    if (unit == "PB" || unit == "PiB" || unit == "pb" || unit == "pib") return static_cast<uint64_t>(number * 1024 * 1024 * 1024 * 1024 * 1024);
    if (unit == "EB" || unit == "EiB" || unit == "eb" || unit == "eib" ) return static_cast<uint64_t>(number * 1024 * 1024 * 1024 * 1024 * 1024 * 1024);
    return static_cast<uint64_t>(number);
}

string formatSize(uint64_t bytes) {
    const char* suffixes[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB"};
    int i = 0;
    double dblBytes = static_cast<double>(bytes);
    while (dblBytes >= 1024 && i < 6) {
        dblBytes /= 1024.0;
        ++i;
    }
    ostringstream oss;
    oss << fixed << setprecision(2) << dblBytes << " " << suffixes[i];
    return oss.str();
}

string generateSentence(mt19937& rng) {
    uniform_int_distribution<> wordCountDist(6, 12);
    int wordCount = wordCountDist(rng);
    string sentence;

    for (int i = 0; i < wordCount; ++i) {
        string word = latinWords[rng() % latinWords.size()];
        if (i == 0) word[0] = toupper(word[0]);
        sentence += word;
        if (i != wordCount - 1) sentence += " ";
    }

    sentence += ". ";
    return sentence;
}

string generateParagraph(mt19937& rng) {
    uniform_int_distribution<> sentenceCountDist(3, 6);
    int sentenceCount = sentenceCountDist(rng);
    string paragraph;

    for (int i = 0; i < sentenceCount; ++i) {
        paragraph += generateSentence(rng);
    }

    paragraph += "\n\n";
    return paragraph;
}

void printProgressBar(uint64_t written, uint64_t totalSize) {
    const int barWidth = 25;
    double progress = static_cast<double>(written) / totalSize;
    int pos = static_cast<int>(barWidth * progress);

    string current = formatSize(written);
    string total = formatSize(totalSize);

    cout << "\rGenerating: [";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << '=';
        else if (i == pos) cout << '>';
        else cout << ' ';
    }
    cout << "] " << current << " / " << total;
    cout.flush();
}

void runGenerator() {
    string fileName, sizeInput;
    cout << "Enter the name/path of the output file (e.g., lorem.txt or D:/stuff/lorem.txt): ";
    getline(cin, fileName);
    cout << "Enter the file size (e.g., 10MiB, 500KB, 1GB): ";
    getline(cin, sizeInput);

    uint64_t targetSize = parseSize(sizeInput);
    ofstream out(fileName, ios::binary);
    if (!out) {
        cerr << "Failed to open file for writing.\n";
        return;
    }

    mt19937 rng(static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count()));
    uint64_t written = 0;
    uint64_t nextUpdate = UPDATE_INTERVAL;

    cout << "Generating lorem ipsum text...\n";

    while (written < targetSize) {
        string paragraph = generateParagraph(rng);
        size_t toWrite = min(static_cast<uint64_t>(paragraph.size()), targetSize - written);
        out.write(paragraph.c_str(), toWrite);
        written += toWrite;

        if (written >= nextUpdate || written == targetSize) {
            printProgressBar(written, targetSize);
            nextUpdate += UPDATE_INTERVAL;
        }
    }

    out.close();
    printProgressBar(targetSize, targetSize);
    cout << "\nDone! File saved as: " << fileName << endl;
}

int main() {
    while (true) {
        runGenerator();

        cout << "\nPress Enter to exit, or press R and Enter to restart: ";
        string input;
        getline(cin, input);

        if (input == "R" || input == "r") {
            cout << "\nRestarting...\n";
            continue;
        }

        break;
    }

    return 0;
}
