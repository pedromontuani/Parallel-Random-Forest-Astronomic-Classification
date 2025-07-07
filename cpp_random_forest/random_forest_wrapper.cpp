//
// Created by pedro on 7/6/25.
//

#include "random_forest.hpp"
#include "random_forest_parallel.hpp"
#include "helpers.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <omp.h>


std::map<std::string, double> execute(const std::string& train_dataset, const std::string& test_dataset, int num_trees, const std::map<int, double>& classWeights, bool parallel = false) {
    std::vector<std::vector<double>> X_train, X_test;
    std::vector<int> y_train, y_test;

    loadCSV(train_dataset, X_train, y_train);
    loadCSV(test_dataset, X_test, y_test);

    std::vector<int> predictions;


    if (parallel) {
        auto rf = RandomForestParallel(num_trees);
        rf.train(X_train, y_train, classWeights);

        for (const auto& x : X_test) {
            predictions.push_back(rf.predict(x));
        }
    } else {
        auto rf = RandomForest(num_trees);
        rf.train(X_train, y_train, classWeights);

        for (const auto& x : X_test) {
            predictions.push_back(rf.predict(x));
        }
    }

    return evaluate(y_test, predictions);
}

std::map<std::string, double> execute_single_thread(const std::string& train_dataset, const std::string& test_dataset, int num_trees, const std::map<int, double>& classWeights, bool parallel = false) {
    return execute(train_dataset, test_dataset, num_trees, classWeights, false);
}

std::map<std::string, double> execute_parallel(const std::string& train_dataset, const std::string& test_dataset, int num_trees, const std::map<int, double>& classWeights) {
    return execute(train_dataset, test_dataset, num_trees, classWeights, true);
}

int get_num_threads() {
    return omp_get_max_threads();
}

BOOST_PYTHON_MODULE(random_forest_wrapper) {
     using namespace boost::python;
     class_<std::map<int, double>>("IntDoubleMap")
        .def(map_indexing_suite<std::map<int, double>>());
     class_<std::map<std::string, double>>("StrDoubleMap")
        .def(map_indexing_suite<std::map<std::string, double>>());

     def("execute_single_thread", &execute_single_thread,
         (arg("train_dataset"), arg("test_dataset"), arg("num_trees") = 10), arg("classWeights") = std::map<int, double>());
     def ("execute_parallel", &execute_parallel,
         (arg("train_dataset"), arg("test_dataset"), arg("num_trees") = 10, arg("classWeights") = std::map<int, double>()));
    def("get_num_threads", &get_num_threads);
 }
