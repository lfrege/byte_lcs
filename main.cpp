#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class dint
{
	public:
	int a;
	int b;
	int l;
	char c;

	dint()
	{
		a = 0;
		b = 0;
		l = 0;
		c = ' ';
	}

	dint(int x, int y, int z, char ch)
	{
		a = x;
		b = y;
		l = z;
		c = ch;
	}
};

int max(int a, int b)
{
	if (a < b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

vector<dint> reduce(const vector<dint>& input)
{
	vector<dint> output;
	int lastx = -1;
	int lasty = -1;
	int i;

	for (i = 0; i < (int)input.size(); i++)
	{
		if (input[i].a > lastx && input[i].b > lasty)
		{
			output.push_back(input[i]);
			lastx = input[i].a;
			lasty = input[i].b;
			cout << input[i].a << "\t" << input[i].b << "\t" << input[i].l << "\t" << input[i].c << endl; 
		}
	}

	return output;
}

vector<dint> overlap_list(const string& left, const string& right)
{
	int i, j;
	int *clist = new int[right.length()];
	int *plist = new int[right.length()];
	int *temp;
	vector<dint> output;

	for (j = 0; j < (int)right.length(); j++)
	{
		plist[j] = 0;
	}

	for (i = 0; i < (int)left.length(); i++)
	{
		for (j = 0; j < (int)right.length(); j++)
		{
			if (left.at(i) == right.at(j))
			{
				if (j == 0)
				{
					clist[j] = 1;
				}
				else
				{
					clist[j] = plist[j-1] + 1;
				}
				output.push_back(dint(i,j,clist[j],right.at(j)));
			}
			else
			{
				if (j == 0)
				{
					clist[j] = plist[j];
				}
				else
				{
					clist[j] = max(clist[j-1], plist[j]);
				}
			}
		}
		temp = plist;
		plist = clist;
		clist = temp;
	}

	return output;
}

int main(int argc, char** argv)
{
	reduce(overlap_list("this is not a string", "this is a better string"));
}
