#include <iostream>
#include "helper/helper.h"

// Default 
float p_near = 0.6;
float p_far = -0.6;
char *smf_model1 = "bound-sprellpsd.smf";
char *smf_model2 = "";
char *smf_model3 = "";

// Declare funcitons
void handleArgvs(int, char**);

// Main function: a pipeline to process 3d images to 2d using z-buffering
int main(int argc, char **argv) {

  // parse argvs
  handleArgvs(argc, argv);
  return 0;
}

void handleArgvs(int argc, char **argv) {
  // parse argv
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) {
      fileName = (char *)argv[++i];
  }
  viewPort.loadDim(j, k, o, p);
  VRC.loadDim(u, v, U, V);
  pbmFile.world = world;

  // print to debug
  std::cerr << "---------Specs: \n";
  std::cerr << "filename: " << fileName << "\n";
}
