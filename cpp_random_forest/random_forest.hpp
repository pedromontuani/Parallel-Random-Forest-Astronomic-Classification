#pragma once
#include "decision_tree.hpp"


class RandomForest {
private:
    int nTrees = 10;

public:
    explicit RandomForest(int numTrees = 10) : nTrees(numTrees) {}

    std::vector<DecisionTree> trees;

    void train(const std::vector<std::vector<double>>& X,
           const std::vector<int>& y,
           const std::map<int, double>& classWeights) {
        trees.clear();
        std::mt19937 rng(42);
        std::uniform_int_distribution<> dist(0, X.size() - 1);

        for (int i = 0; i < nTrees; ++i) {
            std::vector<std::vector<double>> sampleX;
            std::vector<int> sampleY;
            for (size_t j = 0; j < X.size(); ++j) {
                int idx = dist(rng);
                sampleX.push_back(X[idx]);
                sampleY.push_back(y[idx]);
            }
            DecisionTree tree;
            tree.train(sampleX, sampleY, classWeights);
            trees.push_back(tree);
        }
    }


    int predict(const std::vector<double>& x) const {
        std::map<int, int> votes;
        for (const auto& tree : trees) {
            votes[tree.predict(x)]++;
        }
        return votes[0] > votes[1] ? 0 : 1;
    }
};
