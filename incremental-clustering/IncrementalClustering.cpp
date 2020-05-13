#include "IncrementalClustering.h"

#include <iostream>

IncrementalClustering::IncrementalClustering() {
  this->alpha = 0.4;
  this->n = 1;
}

IncrementalClustering::IncrementalClustering(double alpha, int n) {
  this->alpha = alpha;
  this->n = n;
}

std::set<std::string> IncrementalClustering::get_ngram(std::string sentence) {
  std::set<std::string> ngram;

  for (int i = 0; i <= sentence.size() - this->n; i++) {
    ngram.insert(sentence.substr(i, this->n));
  }

  return ngram;
}

double IncrementalClustering::jaccard(std::set<std::string> ngram1,
                                      std::set<std::string> ngram2) {
  if (ngram1.size() == 0 or ngram2.size() == 0) return 0;

  std::set<std::string> intersect;

  std::set_intersection(ngram1.begin(), ngram1.end(), ngram2.begin(),
                        ngram2.end(),
                        std::inserter(intersect, intersect.begin()));

  return intersect.size() / (ngram1.size() + ngram2.size() - intersect.size());
}

double IncrementalClustering::distance(std::set<std::string> ngram1,
                                       std::set<std::string> ngram2) {
  return 1 - this->jaccard(ngram1, ngram2);
}

std::vector<int> IncrementalClustering::fit_predict(
    std::vector<std::string> sentences) {
  const int sent_size = sentences.size();

  std::vector<std::set<std::string>> ngrams(sent_size);

  for (int i = 0; i < sent_size; i++)  // precompute all ngrams
  {
    ngrams[i] = this->get_ngram(sentences[i]);
  }

  std::vector<int> clusters(sentences.size());
  std::vector<int> centroids;  // we will store the index of the words

  clusters[0] = 0;
  centroids.push_back(0);

  for (int i = 1; i < sent_size; i++) {
    double d_min = 2;
    int idx_min = -1;

    for (int j = 0; j < centroids.size(); j++) {
      int centroid_idx = centroids[j];

      double jacc = this->distance(ngrams[i], ngrams[centroid_idx]);

      if (d_min > jacc) {
        idx_min = j;
        d_min = jacc;
      }
    }

    if (d_min <= this->alpha) {
      clusters[i] = idx_min;

      int centroid_idx = centroids[idx_min];

      if (sentences[centroid_idx].size() > sentences[i].size()) {
        centroids[idx_min] = i;
      }
    } else {
      centroids.push_back(i);
      clusters[i] = centroids.size() - 1;
    }

    if (i % 500 == 0) {
      std::cout << "Progress: " << i * 100 / sent_size << "%" << std::endl;
    }
  }

  return clusters;
}