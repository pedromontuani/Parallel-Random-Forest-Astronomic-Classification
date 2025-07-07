#pragma once
#include <vector>
#include <map>
#include <random>
#include <algorithm>

class DecisionTree {
public:
    int featureIndex;
    double threshold;
    int leftLabel, rightLabel;

    void train(const std::vector<std::vector<double>>& X,
               const std::vector<int>& y,
               const std::map<int, double>& classWeights) {
        featureIndex = 0;
        threshold = X[0][0];
        leftLabel = rightLabel = y[0];

        for (size_t i = 0; i < X[0].size(); ++i) {
            double bestThresh = X[0][i];
            std::map<int, double> leftVotes, rightVotes;

            for (size_t j = 0; j < X.size(); ++j) {
                int label = y[j];
                double weight = classWeights.at(label);
                if (X[j][i] < bestThresh)
                    leftVotes[label] += weight;
                else
                    rightVotes[label] += weight;
            }

            double leftScore = leftVotes[0] + leftVotes[1];
            double rightScore = rightVotes[0] + rightVotes[1];

            if (leftScore + rightScore > classWeights.at(leftLabel) + classWeights.at(rightLabel)) {
                featureIndex = i;
                threshold = bestThresh;
                leftLabel = leftVotes[1] > leftVotes[0] ? 1 : 0;
                rightLabel = rightVotes[1] > rightVotes[0] ? 1 : 0;
            }
        }
    }

    int predict(const std::vector<double>& x) const {
        return x[featureIndex] < threshold ? leftLabel : rightLabel;
    }
};