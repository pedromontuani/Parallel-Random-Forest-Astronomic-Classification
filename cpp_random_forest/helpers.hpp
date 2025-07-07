#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

void loadCSV(const std::string& filename, std::vector<std::vector<double>>& X, std::vector<int>& y) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line);
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string val;
        std::vector<double> row;
        while (getline(ss, val, ',')) {
            try {
                row.push_back(std::stod(val));
            } catch (const std::exception& e) {
                std::cerr << "Error converting '" << val << "' to double in file " << filename << "\n";
                throw;
            }
        }
        y.push_back(static_cast<int>(row.back()));
        row.pop_back();
        X.push_back(row);
    }
}

std::map<std::string, double> evaluate(const std::vector<int>& y_true, const std::vector<int>& y_pred, bool print = false) {
    int TP = 0, FP = 0, FN = 0, TN = 0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        if (y_true[i] == 1 && y_pred[i] == 1) TP++;
        else if (y_true[i] == 0 && y_pred[i] == 1) FP++;
        else if (y_true[i] == 1 && y_pred[i] == 0) FN++;
        else TN++;
    }

    double accuracy = (TP + TN) / static_cast<double>(y_true.size());
    double precision = TP / static_cast<double>(TP + FP + 1e-6);
    double recall = TP / static_cast<double>(TP + FN + 1e-6);
    double f1 = 2 * precision * recall / (precision + recall + 1e-6);

    if (print) {
        std::cout << "Accuracy: " << accuracy << "\n";
        std::cout << "Precision: " << precision << "\n";
        std::cout << "Recall: " << recall << "\n";
        std::cout << "F1-score: " << f1 << "\n";
    }

    return {
        {"accuracy", accuracy},
        {"precision", precision},
        {"recall", recall},
        {"fscore", f1}
    };
}