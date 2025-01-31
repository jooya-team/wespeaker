// Copyright (c) 2023 Chengdong Liang (liangchengdong@mail.nwpu.edu.cn)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

#include "utils/utils.h"
#include "glog/logging.h"

namespace wespeaker {

void WriteToFile(const std::string& file_path,
                 const std::vector<std::vector<float>>& embs) {
  // embs [num_enroll, emb_dim]
  std::ofstream fout;
  fout.open(file_path, std::ios::out);
  for (size_t i = 0; i < embs.size(); i++) {
    for (size_t j = 0; j < embs[0].size(); j++) {
      fout << embs[i][j] << " ";
    }
    fout << std::endl;
  }
  fout.close();
}

void ReadToFile(const std::string& file_path,
                std::vector<std::vector<float>>* embs) {
  // embs [num_enroll, emb_dim]
  std::ifstream fin(file_path);
  std::string line;
  while (getline(fin, line)) {
    std::vector<float> tmp;
    std::stringstream word(line);
    float num;
    while (word >> num) {
      tmp.push_back(num);
    }
    embs->push_back(tmp);
  }
}

std::string Ltrim(const std::string& str) {
  size_t start = str.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : str.substr(start);
}

std::string Rtrim(const std::string& str) {
  size_t end = str.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string Trim(const std::string& str) { return Rtrim(Ltrim(str)); }

void SplitString(const std::string& str, std::vector<std::string>* strs) {
  SplitStringToVector(Trim(str), " \t", true, strs);
}

void SplitStringToVector(const std::string& full, const char* delim,
                         bool omit_empty_strings,
                         std::vector<std::string>* out) {
  size_t start = 0, found = 0, end = full.size();
  out->clear();
  while (found != std::string::npos) {
    found = full.find_first_of(delim, start);
    // start != end condition is for when the delimiter is at the end
    if (!omit_empty_strings || (found != start && start != end))
      out->push_back(full.substr(start, found - start));
    start = found + 1;
  }
}

}  // namespace wespeaker
