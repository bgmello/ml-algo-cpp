#ifndef __INCREMENTALCLUSTERING_H__
#define __INCREMENTALCLUSTERING_H__
#include <algorithm>
#include <array>
#include <set>
#include <string>
#include <vector>

class IncrementalClustering {
  double alpha;
  int n;

  std::set<std::string> get_ngram(std::string sentence);

  double jaccard(std::set<std::string> ngram1, std::set<std::string> ngram2);
  double distance(std::set<std::string> ngram1, std::set<std::string> ngram2);

 public:
  IncrementalClustering();

  IncrementalClustering(double alpha, int n);

  std::vector<int> fit_predict(std::vector<std::string> sentences);
};

#endif