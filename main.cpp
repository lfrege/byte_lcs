#include <iostream>
#include <fstream>


using namespace std;

class dint
{
	public:
	int a;
	int b;

	dint()
	{
		a = 0;
		b = 0;
	}

	dint(int x, int y)
	{
		a = x;
		b = y;
	}
};

vector<dint> byte_lcs(const string& left, const string& right)
{
	int i, j;
	int *clist = new int[right.length()];
	int *plist = new int[right.length()];
	int *temp;

	for (i = 0; i < left.length(); i++)
	{
		for (j = 0; j < right.length(); j++)
		{
			
		}
	}
}

int main(int argc, char** argv)
{
	
}
