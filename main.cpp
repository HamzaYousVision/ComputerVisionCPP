#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
const int C = 8;
const int L = 10;

int toInt(string s)
{
    stringstream ss(s);
    int x = 0;
    ss >> x;
    return x;
}

vector<vector<string> > readDataFromFile()
{
    fstream file;
    file.open("test_labels.csv");
    string line;
    getline(file, line);
//    cout<<line<<endl;

    vector<vector<string> > data;
    string d;
    for (int l = 0; l < L; l++)
    {
        getline(file, line);
        stringstream s(line);
        data.push_back(vector<string>() );
        for (int c = 0; c < C; c++)
        {
            getline(s, d, ',');

            data[l].push_back(d);
//            cout<<data[l][c]<<"    ";
        }
//        cout<<endl;
    }

    return data;
}

void displayData(vector<vector<string> > data)
{
    for (int i=0 ; i<L ; i++)
    {
        for (int j = 0; j<C ; j++)
        {
            cout<<data [i][j]<< "  ";
        }
        cout<<endl;
    }
}

class Rectangle
{
    public:
        string name;
        int width;
        int height;
        string classe;
        int xmin;
        int ymin;
        int xmax;
        int ymax;
    private:
        int Area();
};

int Rectangle::Area()
{
    int h = xmax - xmin;
    int w = ymax - ymin;
    int S = h * w;
    return S;
}


int main()
{
    vector<vector<string> > data;
    data = readDataFromFile();
    // affichae
    displayData(data);
    //data to class
    Rectangle rectA;
    rectA.name = data[0][0];
    rectA.width= toInt(data[0][1]);
    rectA.height= toInt (data [0][2]);
    rectA.classe=  data [0][3];
    rectA.xmin= toInt (data[0][4]);
    rectA.ymin= toInt (data [0][5]);
    rectA.xmax= toInt (data [0][6]);
    rectA.ymax= toInt (data [0][7]);

    int s = rectA.Area();
    cout<<s<<endl;



    return 0;
}
