#ifndef newtonpolygon
#define newtonpolygon

#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include "debug.h"
#include <vector>

using namespace std;

class Polygon
{

public:
	struct Vertex
	{
		char value;
		int index;
		
		static Vertex empty()
		{
			Vertex temp;
			return temp;
		}

		Vertex()
		{
			value = ' ';
			index = 0;
		}

		Vertex(char _value)
		{
			value = _value;
			index = 0;
		}

		Vertex(const Vertex& other)
		{
			value = other.value;
			index = other.index;
		}

		~Vertex()
		{
		}

		Vertex& operator=(bool other)
		{
			if (other)
				value = '+';
			else
				value = '-';
			return *this;
		}

		Vertex& operator=(Vertex &other)
		{
			value = other.value;
			index = other.index;
			return *this;
		}

		bool operator==(Vertex& other)
		{
			if (value == other.value)
			{
				if (index == other.index)
				{
					return true;
				}
			}
			return false;
		}

		Vertex operator*(int other)
		{
			Vertex temp(*this);
			if ((*this).value == ' ') temp.value = other;
			if (other > 0)
			{
				if ((*this).value == '+') temp.value = '+';
				else temp.value = '-';
			}
			else if (other < 0)
			{
				if ((*this).value == '-') temp.value = '+';
				else temp.value = '-';
			}
			return temp;
		}


		friend ostream& operator<<(ostream& os, const Vertex& other)
		{
			os << other.value;
			return os;
		}

		bool operator!=(Vertex& other)
		{
			return !(*this == other);
		}


	};

	struct Vector
	{
	public:
		int x, y;
		Vector() :x(0), y(0){}
		Vector(int _x, int _y) :x(_x), y(_y){}
		Vector(const Vector& other) :x(other.x), y(other.y){}
		Vector& operator=(Vector& other)
		{
			x = other.x;
			y = other.y;
		}
		bool operator==(Vector& other)
		{
			if ((x == other.x) && (y == other.y)) return true;
			else return false;
		}
	};
	struct Triangle
	{
		int v1, v2, v3;

		Triangle() :v1(0), v2(0), v3(0){}
		Triangle(const Triangle& other) :v1(other.v1), v2(other.v2), v3(other.v3){}
		Triangle(int _v1, int _v2, int _v3) :v1(_v1), v2(_v2), v3(_v3){}

		bool operator==(Triangle& other)
		{
			bool check1 = false;
			bool check2 = false;
			bool check3 = false;
			if ((v1 == other.v1) || (v1 == other.v2) || (v1 == other.v3))
				check1 = true;
			if ((v2 == other.v1) || (v2 == other.v2) || (v2 == other.v3))
				check2 = true;
			if ((v3 == other.v1) || (v3 == other.v2) || (v3 == other.v3))
				check3 = true;
			if ((check1)&&(check2)&&(check3))
				return true;
			return false;
		}

		bool operator!=(Triangle& other)
		{
			return !(*this == other);
		}

		Triangle& operator=(Triangle& other)
		{
			if (*this == other) return *this;
			v1 = other.v1;
			v2 = other.v2;
			v3 = other.v3;
			return *this;
		}
	};
	

private:
	Vertex* data;
	int degree;
	std::vector<Triangle> mesh;
public:

	Polygon()
		:degree(0), data(0), mesh(0)
	{}

	Polygon(int n)
	{
		degree = n;
		data = new Vertex[Sum(n)];
		for (int i = 0; i < Sum(degree); i++)
		{
			data[i].index = i;
			data[i] = false;
		}
	}

	Polygon(const Polygon& other)
		:Polygon(other.degree)
	{
		for (int i = 0; i < Sum(degree); i++)
		{
			data[i] = other.data[i];
		}
		mesh = other.mesh;
	}

	~Polygon()
	{
		delete[] data;
	}



	void FillXor()
	{
		for (int i = 0; i < degree; i++)
			for (int j = 0; j < degree - i; j++)
				(*this)(i, j) = ((i % 2 == j % 2) && (j % 2 == 0));
	}

	void FillRandom()
	{
		srand(time(0));
		for (int i = 0; i < degree; i++)
			for (int j = 0; j < degree - i; j++)
				(*this)(i, j) = rand()%2;
	}

	void FillWith(bool value)
	{
		for (int i = 0; i < degree; i++)
			for (int j = 0; j < degree - i; j++)
				(*this)(i, j) = value;
	}

	void Invert()
	{
		for (int i = 0; i < degree; i++)
			for (int j = 0; j < degree - i; j++)
			{
				(*this)(i, j) = !((*this)(i, j).value=='+');
			}
	}

	Vertex& operator()(int i, int j)
	{
		if ((degree - abs(i) - 1) < abs(j))
		{
			/*Debug::Log("DIM MISMATCH");
			Debug::Log(i, j);
			Debug::Log(abs(degree - abs(i) - 1), abs(j), 0);*/
			return Vertex::empty();
		}
		return data[Sum(degree - abs(i) - 1) + abs(j)];
	}

	/*Vertex& operator()(int i, int j)
	{
		if ((degree - abs(i)-1) < abs(j))
		{
			Debug::Log("DIM MISMATCH");
			Debug::Log(i, j);
			Debug::Log(abs(degree - abs(i) - 1), abs(j), 0);
			return Vertex::empty();
		}
		int ip = 1, jp = 1;
		if (i < 0) ip = -1;
		if (j < 0) jp = -1;
		if ((ip == 1) && (jp == 1))
			return data[Sum(degree - abs(i) - 1) + abs(j)];
		else
			return data[Sum(degree - abs(i) - 1) + abs(j)] * (pow(ip, abs(i))*pow(jp, abs(j)));
	}*/

	Vertex Get(int i, int j)
	{
		if ((degree - abs(i) - 1) < abs(j))
		{
			/*Debug::Log("DIM MISMATCH");
			Debug::Log(i, j);
			Debug::Log(abs(degree - abs(i) - 1), abs(j), 0);*/
			return Vertex::empty();
		}
		int ip = 1, jp = 1;
		if (i < 0) ip = -1;
		if (j < 0) jp = -1;
		if ((ip == 1) && (jp == 1))
			return data[Sum(degree - abs(i) - 1) + abs(j)];
		else
			return data[Sum(degree - abs(i) - 1) + abs(j)] * (pow(ip, abs(i))*pow(jp, abs(j)));
	}

	bool operator==(Polygon& other)
	{
		if (degree == other.degree)
		{
			for (int i = 0; i < Sum(degree); i++)
			{
				if (data[i] != other.data[i]) return false;
			}
			if (mesh.size() == other.mesh.size())
			{
				for (int i = 0; i < mesh.size(); i++)
				{
					if (mesh[i] == other.mesh[i]) return false; //почему-то vector==other.vector не работает, пришлось велосипедить
				}
				return true;
			}
		}
		return false;
	}

	Polygon& operator=(Polygon& other)
	{
		if (*this == other) return *this;
		degree = other.degree;
		mesh = other.mesh;
		delete[] data;
		data = new Vertex[Sum(degree)];
		for (int i = 0; i < Sum(degree); i++)
		{
			data[i] = other.data[i];
		}
		return *this;
	}



	Vertex& operator[](int k)
	{
		return data[k];
	}

	int GetDegree()
	{
		return degree;
	}

	std::string toString()
	{
		std::stringstream out;
		for (int i = 0; i < degree; i++)
		{
			for (int j = Sum(i); j < Sum(i + 1); j++)
			{
				out << data[j].value;
			}
			out << std::endl;
		}

		return out.str();
	}

	void toFile(std::string filename)
	{
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::trunc);
		file << toString();
		file.close();
		Debug::Log(filename);
	}

	void fromFile(std::string filename)
	{
		std::ifstream file;
		file.open(filename, std::ios::in);
		std::string line;
		std::string store;
		int j = 0;
		while (!file.eof())
		{
			std::getline(file, line, '\n');
			//if (file.eof()) break;
			for (int i = 0; i < line.size(); i++)
			{
				store.push_back(line[i]);
			}
			j++;
		}
		degree = j;
		file.close();

		delete[] data;
		data = new Vertex[Sum(degree)];
		for (int i = 0; i < Sum(degree); i++)
		{
			data[i].value = store[i];
			data[i].index = i;
		}

	}


	void SimpleTriangulate()
	{
		mesh.clear();
		for (int i = degree; i > 0; i--)
		{
			for (int j = 0; j < degree - i; j++)
			{
				int v1 = ConvertCoords(i, j);
				int v2 = v1;
				int v3 = v1;

				if ((*this)(i - 1, j).value != ' ')
					v2 = ConvertCoords(i - 1, j);
				else
				{
					//Debug::Log("Triangulation error: Out of range");
					continue;
				}
				
				if ((*this)(i - 1, j + 1).value != ' ')
					v3 = ConvertCoords(i - 1, j + 1);
				else
				{
					//Debug::Log("Triangulation error: Out of range");
					continue;
				}
					
				mesh.push_back(Triangle(v1,v2,v3));
				v2 = v1;
				
				if ((*this)(i, j + 1).value != ' ')
					v2 = ConvertCoords(i, j + 1);
				else
				{
					//Debug::Log("Triangulation error: Out of range");
					continue;
				}
				
				mesh.push_back(Triangle(v1, v3, v2));

			}
		}

		for (int i = 0; i < mesh.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (mesh[i] == mesh[j])
				{
					mesh.erase(mesh.begin() + i);
					i--;
					j--;
				}
			}
		}

	}

	std::string toStringTriangulation()
	{
		std::stringstream out;
		for (int i = 0; i < mesh.size(); i++)
		{
			out << mesh[i].v1 << " " << mesh[i].v2 << " " << mesh[i].v3<<" ";
			out << std::endl;
		}
		return out.str();
	}

	void toFileTriangulation(std::string filename)
	{
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::trunc);
		file << toStringTriangulation();
		file.close();
	}

	void fromFileTriangulation(std::string filename)
	{
		std::ifstream file;
		file.open(filename, std::ios::in);
		std::string line;
		std::string symbol;
		std::vector<int> store;
		while (!file.eof())
		{
			std::getline(file, line, '\n');
			//if (file.eof()) break;
			for (int i = 0; i < line.size(); i++)
			{
				if ((line[i] != ' '))
				{
					symbol.push_back(line[i]);
				}
				else
				{
					if (symbol.size() != 0)
					{
						store.push_back(std::atoi(symbol.c_str()));
						symbol.clear();
					}
				}
			}
			if (symbol.size() != 0)
			{
				store.push_back(std::atoi(symbol.c_str()));
				symbol.clear();
			}
		}

		mesh.clear();
		for (int i = 0; i < store.size(); i += 3)
		{
			mesh.push_back(Triangle(store[i], store[i + 1], store[i + 2]));
			//Debug::Log(store[i], store[i + 1], store[i + 2]);
		}

		for (int i = 0; i < mesh.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (mesh[i] == mesh[j])
				{
					mesh.erase(mesh.begin() + i);
					i--;
					j--;
				}
			}
		}

	}

	std::vector<Triangle>& GetMesh()
	{
		return mesh;
	}

	std::vector<Triangle> GetMeshForVertex(Vertex& source)
	{
		std::vector<Triangle> temp;
		for each(Triangle i in mesh)
		{
			if ((source.index == i.v1) || (source.index == i.v2) || (source.index == i.v3))
			{
				temp.push_back(i);
			}
		}
		return temp;
	}


	int Sum(int in)
	{
		return (in*(in + 1)) / 2;
	}

	Vector ConvertIndex(int index)
	{
		Vector temp;
		int max = -1;
		for (int i = 0; i < degree; i++)
		{
			if (index - Sum(i)<i + 1)
			{
				if (max == -1)
				{
					max = i;
				}
			}
		}
		if (max >= 0)
		{
			temp.y = degree - max - 1;
			temp.x = index - Sum(max);
		}
		return temp;
	}

	int ConvertCoords(int i, int j)
	{
			return Sum(degree - abs(i) - 1) + abs(j);
	}
};


#endif