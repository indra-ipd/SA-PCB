///////////////////////////////////////////////////////////////////////////////
// Authors: Chester Holtz, Devon Merrill, James (Ting-Chou) Lin, Connie (Yen-Yi) Wu
//          (respective Ph.D. advisors: Chung-Kuan Cheng, Andrew B. Kahng, Steven Swanson).
//
// BSD 3-Clause License
//
// Copyright (c) 2018, The Regents of the University of California
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///////////////////////////////////////////////////////////////////////////////

#define BOOST_NO_AUTO_PTR

#include <cstdio>
#include "BoardGrid.h"
//#include "kicadPcbDataBase.h"
#include "globalParam.h"
#include "util.h"

#include <functional>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <numeric>
#include <cmath>
#include <unistd.h>
#include <ctime>
#include <ratio>
#include <chrono>

// boost version 1.69.0
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/geometry.hpp>
#include <boost/assign.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry/index/rtree.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "readFiles.hpp"
//#include "readScl.h"
#include "time.h"
//#include "taskflow/taskflow.hpp"

class HPlacerUtils
{
public:
  void initialize_params(map<int, vector<Module *> > &netToCell);
  void validate_move(Module *node, double rx, double ry);
  double cost(map<int, vector <Module *> > &netToCell,
              int temp_debug = 0);
  double cost_partial(vector < Module *> &nodes, map<int, vector<Module *> > &netToCell);
  double cell_overlap();
  double wirelength(map<int, vector<Module *> > &netToCell);
  double cell_overlap_partial(vector < Module * > &nodes);
  double wirelength_partial(vector < Module * > &nodes, map<int, vector<Module *> > &netToCell);
  double rudy(map<int, vector<Module *> > &netToCell);
  float annealer(map<int, vector<Module *> > &netToCell, string initial_pl,int level=0);
  double initialize_temperature(double &Temperature,map<int, vector<Module *> > &netToCell);
  double initiate_move(double current_cost, double & Temperature,map<int, vector<Module *> > &netToCell);
  void random_placement(int xmin, int xmax, int ymin, int ymax, Module &n);
  vector < Module * > ::iterator random_node();
};