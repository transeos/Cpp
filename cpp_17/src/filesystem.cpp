// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 9/7/21.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;

namespace fs = std::filesystem;

void DisplayContent(fs::path const &p) {
  cout << p.filename() << endl;

  if (!fs::is_directory(p))
    return;

  for (auto const &e : fs::directory_iterator(p)) {
    if (fs::is_regular_file(e.status()))
      cout << "  " << e.path().filename() << " [" << fs::file_size(e)
           << " bytes]\n";
    else if (fs::is_directory(e.status()))
      cout << "  " << e.path().filename() << endl;
  }
}

int main(const int argc, const char **argv) {
  cout << "\n=== filesystem ===\n";
  {
    fs::path dir = "../src";
    DisplayContent(dir);
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
