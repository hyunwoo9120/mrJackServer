#include <fstream>
#include <stdio.h>
#include "Character.h"

using namespace std;

int main() {

	CCharacter chart1;
	CCharacter chart2;

	chart1.b_innocent = 0;
	chart1.i_xposition = 6;
	chart1.i_yposition = 8;

	ofstream recvFile;
	recvFile.open("../../recvFile.txt", ios::out);
	recvFile.write((char*)&chart1, sizeof(chart1));
	recvFile.close();

	printf("\n b: %d", chart1.b_innocent);
	printf("\n x: %d", chart1.i_xposition);
	printf("\n y: %d", chart1.i_yposition);

	printf("\n=========================\n");

	ifstream sendFile;
	sendFile.open("../../recvFile.txt", ios::in);
	sendFile.seekg(0);
	sendFile.read((char*)&chart2, sizeof(chart2));
	printf("\n b: %d", chart2.b_innocent);
	printf("\n x: %d", chart2.i_xposition);
	printf("\n y: %d", chart2.i_yposition);
	return 0;
}