#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <fstream>

// Classic helper function
class Util {

public:
	static void getStream(std::string path, std::ifstream& stream);
	static int getStoredHighestScore();
	static void writeNewHighestScore(int score);
};

// wrapper for creating streams
void Util::getStream(std::string path, std::ifstream& stream){
    stream.open (path, std::ifstream::in);
    if (!stream && !stream.is_open()){
        stream.close();
        throw std::runtime_error("Non - existing PID");
    }
    //return stream;
}

//Get previous highest score.
int Util::getStoredHighestScore(){
  std::string line;
  std::ifstream myfile ("../src/highestscore");
  if (myfile.is_open())
  {
    getline (myfile,line);
    myfile.close();
    return std::stoi(line);
  }
  std::cout << "\nHighestscore files not found.";
  return 0;
}

//Write new highest score
void Util::writeNewHighestScore(int score){
	std::ofstream myfile ("../src/highestscore");
  if (myfile.is_open())
  {
    myfile << std::to_string(score);
    myfile.close();
  }
}

#endif