#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

const int MAX = 100;	//���� �� �������� ��� ������� �����

using namespace std;

class Graph {
	private:
		int Vertixes_;
		int MatrixType_;	//0 -�����������������, 1 - ���������������
		int **AdjacencyMatrix_;	//������� ���������
		int **AdjacencyList_;	//������ ���������
		int **IncidenceMatrix_;	//������� �������������
		int Edges_;
	public:
		Graph(int tmp_vertixes, int tmp_type){	//�����������
			Vertixes_ = tmp_vertixes;
			MatrixType_ = tmp_type;
			Edges_ = 0;
			AdjacencyMatrix_ = new int*[MAX];
			for(int i=0; i<MAX; i++)
				AdjacencyMatrix_[i] = new int[MAX];
			AdjacencyList_ = new int*[MAX];
			for(int i=0; i<MAX; i++)
				AdjacencyList_[i] = new int[MAX];
			IncidenceMatrix_ = new int*[MAX];
			for(int i=0; i<MAX; i++)
				IncidenceMatrix_[i] = new int[MAX];
			for(int i=0; i<MAX; i++)
				for(int j=0; j<MAX; j++){
					AdjacencyMatrix_[i][j] = 0;
					AdjacencyList_[i][j] = NULL;
					IncidenceMatrix_[i][j] = 0;
				}
		}
		void addElem(int first, int second);
		void generateAdjacencyList();
		void printGraph();
		~Graph(){	//����������
			for(int i=0; i<MAX; i++){
				delete[] AdjacencyMatrix_[i];
				delete[] AdjacencyList_[i];
				delete[] IncidenceMatrix_[i];
			}
			delete[] AdjacencyMatrix_;
			delete[] AdjacencyList_;
			delete[] IncidenceMatrix_;
		}
};

void Graph::addElem(int first, int second){
	if(MatrixType_ == 0){
		AdjacencyMatrix_[first][second] = AdjacencyMatrix_[second][first] = 1;
		IncidenceMatrix_[first][Edges_] = IncidenceMatrix_[second][Edges_] = 1;
	}
	else {
		AdjacencyMatrix_[first][second] = 1;
		IncidenceMatrix_[first][Edges_] = 1;
		IncidenceMatrix_[second][Edges_] = -1;
	}
	Edges_++;
}

void Graph::generateAdjacencyList(){
	for(int i=0; i<=Vertixes_; i++){
		int temp = 0;
		for(int j=0; j<=Vertixes_; j++){
			if(AdjacencyMatrix_[i][j] == 1){
				AdjacencyList_[i][temp] = j;
				temp++;
			}
		}
	}
}

void Graph::printGraph(){
	generateAdjacencyList();
	cout<<"\n������ ��������� \n";
	for(int i=0; i<=Vertixes_; i++){
		bool tmp_column = false;
		int j = 0;
		cout<<'V'<<i<<": ";
		do{
			if(AdjacencyList_[i][j] != NULL){
				cout<<'V'<<AdjacencyList_[i][j]<<' ';
				j++;
			}
			else
				tmp_column = true;
		}while(tmp_column != true);
		cout<<';'<<endl;
	}
	cout<<"\n������� ��������� \n";
	cout<<"   ";
	for(int i=0; i<=Vertixes_; i++){
		cout<<" V"<<i;
	}
	cout<<endl;
	for(int i=0; i<=Vertixes_; i++){
		cout<<'V'<<i<<":";
		for(int j=0; j<=Vertixes_; j++){
			cout<<setw(3)<<right<<AdjacencyMatrix_[i][j];
		}
		cout<<endl;
	}
	cout<<"\n������� ������������� \n";
	cout<<"   ";
	for(int i=1; i<=Edges_; i++){
		cout<<" E"<<i;
	}
	cout<<endl;
	for(int i=0; i<=Vertixes_; i++){
		cout<<'V'<<i<<":";
		for(int j=0; j<Edges_; j++){
			cout<<setw(3)<<IncidenceMatrix_[i][j];
		}
		cout<<endl;
	}
}

int main(){
	setlocale(LC_ALL,"Russian");	//� Dev-C++ �����������, � ������ ������������ ������ ��������� �� Russian � RUS
	int vertixes, first, second, type;
	cout<<"������� ���������� ������ � ��� �����(0 - �����������������, 1 - ���������������) ����� ������:";
	cin>>vertixes>>type;
	Graph point(vertixes, type);
	cout<<"������� ���� �� ������� � ���� X Y. ��� ������ ������� 4242 4242 \n";	//4242 �������� �.�. � ���������� ��� ����� ����� ������, � 42 ����� �� ��� �������
	while(first != 4242, second != 4242){
		cin>>first>>second;
		if(first != 4242, second != 4242)	//��� ��� �������� ��� �� ����� �� ������ ��� �������
			point.addElem(first, second);
	}
	point.printGraph();
}
