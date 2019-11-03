#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include"opencv/cv.h"
#include"opencv/highgui.h"
#include"opencv/cvaux.h"
#include"opencv2/core/core.hpp"
#include"opencv2/features2d/features2d.hpp"
#include"opencv2/nonfree/features2d.hpp"

using namespace std;
const int C = 8;
const int L = 15;

int toInt(string s)
{
    stringstream ss(s);
    int x = 0;
    ss >> x;
    return x;
}

class DataLoader
{
private:
    int N;
    vector<vector<string> > data;
public:
    DataLoader(int);
    void readFromFile();
    void displayData();

    vector<vector<string> > getData();
};

DataLoader::DataLoader(int Number)
{
    N = Number;
}

void DataLoader::readFromFile()
{
    fstream file;
    file.open("test_labels.csv");
    string line;
    getline(file, line);
    string d;
    for (int l = 0; l < N; l++)
    {
        getline(file, line);
        stringstream s(line);
        data.push_back(vector<string>() );
        for (int c = 0; c < C; c++)
        {
            getline(s, d, ',');
            data[l].push_back(d);
        }
    }
}

void DataLoader::displayData()
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

vector<vector<string> > DataLoader::getData()
{
    return data;
}

struct Size
{
    int height;
    int width;
};

struct Point
{
    int x;
    int y;
};

class BoundBox
{
    private:
        string name;
        string classe;
        Point corner;
        Size box_size;
    public:
        Size img_size;

        int Area();
        Point Centroid();

        string getName();
        string getClass();
        Point getCorner();
        Size getSize();

        void setName(string);
        void setClass(string);
        void setCorner(int, int);
        void setSize(int, int);

        void displayImage(bool);
};

string BoundBox::getName()
{
    return name;
}

string BoundBox::getClass()
{
    return classe;
}

Point BoundBox::getCorner()
{
    return corner;
}

Size BoundBox::getSize()
{
    return box_size;
}

void BoundBox::setName(string in_name)
{
    name = in_name;
}

void BoundBox::setClass(string in_class)
{
    classe = in_class;
}

void BoundBox::setCorner(int xx, int yy)
{
    corner.x = xx;
    corner.y = yy;
}

void BoundBox::setSize(int h, int w)
{
    box_size.height = h;
    box_size.width = w;
}

int BoundBox::Area()
{
    return box_size.height*box_size.width;
}

Point BoundBox::Centroid()
{
    Point p;
    p.x = corner.x + box_size.height/2;
    p.y = corner.y + box_size.width/2;
    return p;
}

void BoundBox::displayImage(bool rect=false)
{
    string new_name = "images/test/"+name;


    cv::Mat img = cv::imread(new_name);
    if (rect)
    {
        cv::Point pt1(corner.x, corner.y);
        cv::Point pt2(corner.x+box_size.height, corner.y+box_size.width);
        cv::rectangle(img, pt1, pt2, cv::Scalar(0, 255, 0));
    }
    cv::imshow(name, img);
    cv::waitKey(0);
}

int main()
{
    DataLoader loader(L);
    loader.readFromFile();
    vector<vector<string> > data = loader.getData();
    // affichae
    loader.displayData();
    //data to class
    vector<BoundBox> boxes(L);
    for (int k = 0; k < L; k++)
    {
        boxes[k].setName(data[k][0]);
        boxes[k].setClass(data [k][3]);
        boxes[k].setCorner(toInt(data[k][4]), toInt(data[k][5]));
        boxes[k].setSize(toInt(data[k][6]) - toInt(data[k][4]), toInt(data[k][7]) - toInt(data[k][5]));

        boxes[k].displayImage(true);
        cout<<boxes[k].getClass()<<endl;
    }



    return 0;
}
