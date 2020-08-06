#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

int two_to_oned(int row, int column, int side_len);
bool proc_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);
void random_2_gen(std::vector<int>& v);
bool move_left(std::vector<int>& v);
bool move_right(std::vector<int>& v);
bool move_up(std::vector<int>& v);
bool move_down(std::vector<int>& v);

int main(){
  std::string input_file;
  std::ifstream infile;
  std::vector<int>grid;
  std::cout << "Enter initial configuration file name: " << std::endl;
  std::cin >> input_file;

  infile.open(input_file.c_str());
  if(!infile.is_open()){
    std::cout << "File not found. Using default start configuration" << std::endl;
    for(int i=0;i<15;i++){
      grid.push_back(0);
    }
    grid.push_back(2);
  }
  int number;
  while(infile >> number){
    grid.push_back(number);
  }
  print_grid(grid);
  std::cout << std::endl;
  std::string input_key;
  while(!game_over(grid)){
    std::cin >> input_key;
    // w = up
    // a = left
    // s = down
    // d = right 
    if(input_key == "w"){
      if(move_up(grid)){
        std::cout << std::endl;
        random_2_gen(grid);
        print_grid(grid);
        std::cout << std::endl;
      }
    }
    else if(input_key == "a"){
      if(move_left(grid)){
        std::cout << std::endl;
        random_2_gen(grid);
        print_grid(grid);
        std::cout << std::endl;
      }
    }
    else if(input_key == "s"){
      if(move_down(grid)){
        std::cout << std::endl;
        random_2_gen(grid);
        print_grid(grid);
        std::cout << std::endl;
      }
    }
    else if(input_key == "d"){
      if(move_right(grid)){
        std::cout << std::endl;
        random_2_gen(grid);
        print_grid(grid);
        std::cout << std::endl;
      }
    }
  }
  std::cout << "Game over" << std::endl;
  return 0;
}

int two_to_oned(int row, int column, int side_len){ // fn converts bidimensional indicies to one dimen index
  return (row*side_len) + column;
}
bool proc_num(std::vector<int>& v, int bi, int ei){ // bi = beginning index, ei = 1 + end index
  std::vector<int>v_copy, temp, v_out;
  v_copy = v;
  v_out = v;
  // numbers to merege in new vector
  for(int i = bi; i<ei; i++){
    if(v[i] != 0){
      temp.push_back(v[i]);
    }
  }
  // only do merege if there are actually numbers present in temp
  if(temp.size() != 0){
    // mergeing the numbers
    for(int i = 0; i<temp.size()-1; i++){
      if(temp[i] == temp[i+1]){
        temp[i] = temp[i] * 2;
        temp[i+1] = 0;
      }
    }
    // zero all entries in the range bi to ei
    for(int i = bi; i<ei; i++){
      v_out[i] = 0;
    }
    // returning merged numbers back to vector in right place
    int counter = 0;
    for(int i = bi; counter < temp.size(); counter++){
      if(temp[counter] != 0){
        v_out[i] = temp[counter];
        i++;
      }
    }
  }
  v = v_out;
  if(v == v_copy){ // if there is no change in the vector then return false else return true
    return false;
  }
  else{
    return true;
  }
}
void rotate_anti_clock(std::vector<int>& v){
  std::vector<int> v_copy;
  v_copy = v; // make a copy of the vector
  int dimension = std::sqrt(v_copy.size()); // length of each side
  v.clear(); // clear all conent from original vector

  for(int i = dimension -1 ; i >= 0; i--){ // column for loop
    for(int j = 0; j<dimension; j++){ // row for loop
      v.push_back(v_copy[two_to_oned(j, i, dimension)]); // works out new index using 2-1D, find value in copy v correspoding to index, add value to original v
    }
  }
}
bool game_over(const std::vector<int>& v){
  std::vector<int>v2 = v;
  if(!move_up(v2) && !move_down(v2) && !move_left(v2) && !move_right(v2)){
    return true;
  }
  else{
    return false;
  }
}
void print_grid(const std::vector<int>& v){
  int grid_size = std::sqrt(v.size()); // gives dimension of the grid
  for(int i = 0; i < grid_size; i++){ // row for loop
    for(int j = 0; j < grid_size; j++){ // col for loop
      std::cout << v[two_to_oned(i,j,grid_size)] << "\t" ; //converts indices from 2D to 1D and prints out in grid style
    }
    std::cout << std::endl;
  }
}
void random_2_gen(std::vector<int>& v){
  std::vector<int>v_copy = v;
  srand((int) time(0));
  while(v_copy == v){
    int random_index = rand() % v.size();
    if(v[random_index] == 0){
      v[random_index] = 2;
    }
  }
}
bool move_left(std::vector<int>& v){
  std::vector<int>v_copy = v;
  int side = std::sqrt(v.size());
  int i =0;
  while(i<v.size()){
    for(int j = side; j<=v.size();j=j+side){//ei
      bool proc = proc_num(v,i,j);
      i = i + side;
    }
  }
  if(v == v_copy){ // if there is no change in the vector then return false else return true
    return false;
  }
  else{
    return true;
  }
}
bool move_right(std::vector<int>& v){
  std::vector<int>v_copy = v;
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  int side = std::sqrt(v.size());
  int i =0;
  while(i<v.size()){
    for(int j =side; j<=v.size();j=j+side){//ei
      bool proc = proc_num(v,i,j);
      i = i + side;
    }
  }
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  if(v == v_copy){ // if there is no change in the vector then return false else return true
    return false;
  }
  else{
    return true;
  }
}
bool move_up(std::vector<int>& v){
  std::vector<int>v_copy = v;
  rotate_anti_clock(v);
  int side = std::sqrt(v.size());
  int i =0;
  while(i<v.size()){
    for(int j =side; j<=v.size();j=j+side){//ei
      bool proc = proc_num(v,i,j);
      i = i + side;
    }
  }
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  if(v == v_copy){ // if there is no change in the vector then return false else return true
    return false;
  }
  else{
    return true;
  }
}
bool move_down(std::vector<int>& v){
  std::vector<int>v_copy = v;
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  int side = std::sqrt(v.size());
  int i =0;
  while(i<v.size()){
    for(int j =side; j<=v.size();j=j+side){//ei
      bool proc = proc_num(v,i,j);
      i = i + side;
    }
  }
  rotate_anti_clock(v);
  if(v == v_copy){ // if there is no change in the vector then return false else return true
    return false;
  }
  else{
    return true;
  }
}
