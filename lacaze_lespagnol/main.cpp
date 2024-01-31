#include <iostream>
#include "Algo_PRIM/PrimM.h"
#include "Algo_PRIM/PrimL.h"

int main(int argc,char** argv) {
    if (argc >= 4 && argc <= 5){
        std::string p = argv[1];
        std::string input = argv[2];
        char * ptr;
        int s = strtol(argv[3],&ptr,10);
        if(p=="PrimM"){
            if(argc == 4){

                PrimM prim(input,s);
            }
            else{
                std::string out = argv[4];
                PrimM prim(input,s,out);
            }

        }
        else if (p=="PrimL"){
            if(argc == 4){
                PrimL prim(input,s);
            }
            else{
                std::string out = argv[4];
                PrimL prim(input,s,out);
            }
        }
        else{
            std::cout << "error 1er argument doit etre PrimL ou PrimM"<< std::endl;
        }
    }
    else{
        std::cout << "mauvais nombre d'argument" << std::endl;
    }



    return 0;
}
