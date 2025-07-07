#include "random_forest.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include "random_forest.hpp"
#include "random_forest_parallel.hpp"
#include "helpers.hpp"


int main() {
    std::vector<std::vector<double>> X_train, X_test;
    std::vector<int> y_train, y_test;

    loadCSV("../train_data.csv", X_train, y_train);
    loadCSV("../test_data.csv", X_test, y_test);

    auto rf = RandomForestParallel(100);
    rf.train(X_train, y_train, {
    {0, 0.6353744738305138}, {1, 3.2089851584436424}, {2, 0.8972633467922836}});



    std::vector<int> predictions;
    for (const auto& x : X_test) {
        predictions.push_back(rf.predict(x));
    }

    evaluate(y_test, predictions);
    return 0;
}