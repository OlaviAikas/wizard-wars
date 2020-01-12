
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}
int main(){
    // std::cout << "test" << std::endl;
    // must_init(al_init(), "allegro");
    // return 0;

    // using namespace std;
    // ofstream outf("Settings.txt");
    // if (!outf){
    //     cerr << "Unable to open Settings.txt" <<endl;
    //     exit(1);
    // }
    // outf << "Resolution" << endl;
    // outf << "Buffer" << endl;
    // outf << "VSYNC" << endl;
	using namespace std;
	ifstream myfile("Settings.txt"); 
	if (myfile.is_open()) 
	{
        std::string line;
        std::vector<std::string> vt;
        vt.reserve(2);
		while (getline(myfile, line)) {
            vt.push_back(std::move(line));
		
	    }
        myfile.close(); 
        std::cout << vt[0] <<std::endl;
        std::cout << vt[1] <<std::endl;
    } else { 
        cerr << "Unable to open Settings.txt" <<endl;
        exit(1);
    } 
	// for(l_2=0;l_2<=l;l_2++){ 
	// 	cout<<array[l_2]<<endl;    
    // }
    return 0;
    
    }
