#include "loader.h"

bool loadObj(const char *path, std::vector<GLfloat> &vertices, std::vector<GLfloat> &cores, std::vector<GLfloat> &normais, std::vector<std::vector<GLuint>> &faces)
{

	std::ifstream infile(path);
	std::string line;
	vector<unsigned int> vIndices, uvIndices, nIndices;

	while (getline(infile, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream iss(line.substr(2));
			GLfloat v;
			iss >> v;
			vertices.push_back(v);
			iss >> v;
			vertices.push_back(v);
			iss >> v;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream iss(line.substr(2));
			GLfloat v;
			iss >> v;
			normais.push_back(v);
			iss >> v;
			normais.push_back(v);
			iss >> v;
			normais.push_back(v);
		}
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream iss(line.substr(2));
			GLfloat v;
			iss >> v;
			cores.push_back(v);
			iss >> v;
			cores.push_back(v);
			iss >> v;
			cores.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			unsigned int verticesIndex[3], uvIndex[3], normalIndex[3];
			std::vector<GLuint> face;
			sscanf(line.substr(2).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &verticesIndex[0], &uvIndex[0], &normalIndex[0], &verticesIndex[1], &uvIndex[1], &normalIndex[1], &verticesIndex[2], &uvIndex[2], &normalIndex[2]);
			/*vIndices.push_back(verticesIndex[0]);
			vIndices.push_back(verticesIndex[1]);
			vIndices.push_back(verticesIndex[2]);
			nIndices.push_back(normalIndex[0]);
			nIndices.push_back(normalIndex[1]);
			nIndices.push_back(normalIndex[2]);*/
			face.push_back(verticesIndex[0] - 1);
			face.push_back(verticesIndex[1] - 1);
			face.push_back(verticesIndex[2] - 1);
			faces.push_back(face);
		}

		//FIXME: indice dos arrays de vn e vt
	}
	infile.close();
	/*vector<GLfloat> out_vertex;
	vector<GLfloat> out_normals;
	
	for(unsigned int i = 0; i < vIndices.size(); i++)
	{
		unsigned int vertexIndex = vIndices[i];
		unsigned int normalIndex = nIndices[i];

		out_vertex.push_back(vertices[vertexIndex]);
		out_normals.push_back(normais[normalIndex]);
	}

	vertices = out_vertex;
	normais = out_normals;
	*/
	return true;
}
