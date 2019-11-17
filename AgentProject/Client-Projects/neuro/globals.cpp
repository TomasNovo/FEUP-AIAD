#include "globals.h"

#include <stdio.h>
#include <string.h>
#include <fstream>

default_random_engine generator;
normal_distribution<double> normalDistribution;
uniform_real_distribution<double> uniformDistribution;

vector<vector<vector<double>>> images;
vector<int> labels;
vector<vector<double>> input;
vector<vector<double>> output;

int maxImages = 10000;

void initializeGlobals()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator = std::default_random_engine(seed);
	normalDistribution = std::normal_distribution<double>(0.0, 1.0);
	uniformDistribution = uniform_real_distribution<double>(0.0, 1.0);
}

int readInt(ifstream& ifs)
{
	unsigned char buffer[4];
	ifs.read((char*)buffer, 4);
	int num = 0;

	for (int i = 0; i < 4; ++i)
	{
		num += buffer[i] << 32-(i+1)*8;
	}

	return num;
}

unsigned char readByte(ifstream& ifs)
{
	unsigned char buffer[1];
	ifs.read((char*)buffer, 1);

	return buffer[0];
}

void printVector(const vector<double>& input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		cout << input[i];
		if (i != input.size()-1)
			cout << ",";
	}

	cout << "\n";
}

void printVector(const vector<vector<double>>& input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		printVector(input[i]);
	}

	cout << "\n";
}


bool getImages(string imagesFilename, string labelsFilename)
{
	images.clear();
	labels.clear();
	input.clear();
	output.clear();

	ifstream imagesFs(imagesFilename, ifstream::binary), labelsFs(labelsFilename, ifstream::binary);
	unsigned char foo;

	char buffer[4];
	labelsFs.read(buffer, 4);
	labelsFs.read(buffer, 4);

	imagesFs.read(buffer, 4);

	if (buffer[0] != 0 || buffer[1] != 0)
		return false;

	char dataType = (int)buffer[2];
	int numDimensions = buffer[3];

	if (dataType == 8) // Unsigned byte
	{
		int numImages = readInt(imagesFs);
		int numRows = readInt(imagesFs);
		int numColumns = readInt(imagesFs);
		bool leave = false;

		// cout << "numImages = " << numImages << "\n";
		// cout << "numRows = " << numRows << "\n";
		// cout << "numColumns = " << numColumns << "\n";

		for (int i = 0; i < numImages && i < maxImages; ++i)
		{
			vector<double> row(numColumns, 0);
			images.push_back(vector<vector<double>>(numRows, row));

			labels.push_back(readByte(labelsFs));

			for (int j = 0; j < numRows; ++j)
			{
				// images[i].push_back(vector<double>());
				for (int k = 0; k < numColumns; ++k)
				{
					if (imagesFs.peek() == EOF)
						leave = true;

					if (leave)
						break;

					images[i][k][27-j] = (double)readByte(imagesFs)/256;
				}

				if (leave)
					break;
			}

			if (leave)
				break;
		}

		// Create input
		input.clear();
		for (int i = 0; i < images.size(); ++i)
		{
			input.push_back(vector<double>());
			for (int j = 0; j < images[i].size(); ++j)
			{
				for (int k = 0; k < images[i][j].size(); ++k)
				{
					input[i].push_back(images[i][j][k]);
				}
			}
		}

		// Create expected output
		output.clear();
		for (int i = 0; i < labels.size(); ++i)
		{
			output.push_back(vector<double>());
			for (int j = 0; j < 10; ++j)
			{
				if (labels[i] == j)
					output[i].push_back(1.0);
				else
					output[i].push_back(0.0);
			}
		}

		return true;
	}

	return false;
}

void saveImage(string filename, const vector<double>& input)
{
	vector<vector<double>> vec;

	for (int i = 0; i < 28; ++i)
	{
		vector<double> row;
		for (int j = 0; j < 28; ++j)
		{
			row.push_back(input[i*28+j]);
		}

		vec.push_back(row);
	}

	saveImage(filename, vec);
}


void saveImage(string filename, const vector<vector<double>>& input)
{
	int r,g,b;
	int w = input[0].size(), h = input.size(), x, y;
	FILE *f;
	unsigned char *img = NULL;
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

	img = (unsigned char *)malloc(3*w*h);
	memset(img,0,3*w*h);

	for(int i=0; i<h; i++)
	{
	    for(int j=0; j<w; j++)
	    {
	        x=i; y=(h-1)-j;
	        r = input[i][j]*255;
	        g = input[i][j]*255;
	        b = input[i][j]*255;
	        if (r > 255) r=255;
	        if (g > 255) g=255;
	        if (b > 255) b=255;
	        img[(x+y*w)*3+2] = (unsigned char)(r);
	        img[(x+y*w)*3+1] = (unsigned char)(g);
	        img[(x+y*w)*3+0] = (unsigned char)(b);
	    }
	}

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	f = fopen(filename.c_str(),"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<h; i++)
	{
	    fwrite(img+(w*(h-i-1)*3),3,w,f);
	    fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}

	free(img);
	fclose(f);
}

// Reads an image and converts it to an input vector. Flips horizontally and rotates 90º clockwise to conform with the images from MNIST
vector<double> readImage(string filename)
{
    ifstream ifs(filename, ifstream::binary);
    unsigned char info[54];
    ifs.read((char*)info, 54); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char data[size]; // allocate 3 bytes per pixel
    vector<double> values;
    ifs.read((char*)data, size); // read the rest of the data at once
    ifs.close();

    for (int i = 0; i < size; i += 3)
    {
        values.push_back((double)data[i]/256);
    }

    // Flips horizontally and rotates 90º clockwise
    vector<double> newValues(values.size(), 0.0);
    for (int i = 0; i < values.size(); ++i)
    {
    	int x = i % 28;
    	int y = i / 28;

    	int newX = y;
    	int newY = x;
    	int newI = newY*28 + newX;

    	newValues[i] = values[newI];
    }

    return newValues;
}