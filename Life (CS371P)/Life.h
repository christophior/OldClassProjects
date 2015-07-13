// ---------
// Life.h
// ---------

#ifndef Life_h
#define Life_h

#include <vector>
#include <iostream>
#include <typeinfo>
#include <string>

#include "Handle.h"
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"


using namespace std;

template <typename T>
class Life{
	public:
		vector<vector<T> > _grid;
		vector<vector<int> > _neighbors;
		int _generation, _population, row, col;

		//set up grid with certain cell type
		Life (int x, int y, T cell){
			_generation = 0;
			_population = 0;
			row = x + 2;
			col = y + 2;
			_grid = vector<vector<T> >(row, vector<T>(col, cell));
			_neighbors = vector<vector<int> > (row, vector<int>(col, 0));
		}

		//print out Life grid
		void print(){
			cout << "Generation = " << _generation << ", Population = ";
			cout << _population << "." << endl;

			for (int i = 1; i<row-1; ++i){
				for (int j = 1; j<col-1; ++j){
					cout << _grid[i][j].symbol(); 
				}
				cout<<endl;
			}
		}

		//set which starting cells to be alive
		void respawn(int x, int y){
			_grid[x+1][y+1].respawn();
			++_population;
		}

		//have Life run a certain amount of generation cycles
		void run(int cycles){
			for (int c = 0; c<cycles; ++c){
				_population = 0;
				++_generation;
				neighborHelper();
				for (int i = 1; i<row-1; ++i){
					for (int j = 1; j<col-1; ++j){
						_population += _grid[i][j].nextGen(_neighbors[i][j]) ? 1 : 0;
					}
				}
			}
		}

		//get neighbors for each cell before starting a certain
		//generation cycle
		void neighborHelper(){
			for (int i = 1; i<row-1; ++i){
				for (int j = 1; j<col-1; ++j){
					if (_grid[i][j].name() == "ConwayCell"){
						_neighbors[i][j] = getConwayNeighborCount(i, j);	
					} else {
						_neighbors[i][j] = getFredkinNeighborCount(i, j);	
					}
				}
			}
		}

		int getConwayNeighborCount(int x, int y){
			int cNeighbors = 0;
			
			int temp[3] = {-1, 0, 1};
			for (int i = 0; i < 3; ++i){
				for (int j = 0; j < 3; ++j){
					if (!(temp[i] == 0 && temp[j] == 0)){
						//Conway
						if (_grid[x + temp[i]][y + temp[j]].isAlive()){
							++cNeighbors;
						}
					}
				}
			}
			return cNeighbors;
		}

		int getFredkinNeighborCount(int x, int y){
			int fNeighbors = 0;

			int temp[3] = {-1, 0, 1};
			for (int i = 0; i < 3; ++i){
				for (int j = 0; j < 3; ++j){
					if (!(temp[i] == 0 && temp[j] == 0)){
						//Fredkin
						if (!(temp[i] != 0 && temp[j] != 0)){
							if (_grid[x + temp[i]][y + temp[j]].isAlive()){
								++fNeighbors;
							}

						}
					}
				}
			}
			return fNeighbors;
		}

//Generation = 283, Population = 492.
		void printHelp(){
			for (int i = 1; i<row-1; ++i){
				for (int j = 1; j<col-1; ++j){
					cout << _neighbors[i][j]; 
				}
				cout<<endl;
			}
		}
};

#endif // Life_h