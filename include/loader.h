#ifndef _LOADER_HPP_
#define _LOADER_HPP_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glut.h>

using namespace std;

bool loadObj(const char *path, std::vector<GLfloat> &vertices, std::vector<GLfloat> &cores, std::vector<GLfloat> &normais, std::vector<std::vector<GLuint>> &faces);

#endif