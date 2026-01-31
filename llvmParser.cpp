#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <memory>

using namespace std;
using namespace llvm;
int main(int argc, char **argv) {
    //checking if user provided input file
    if (argc < 2){
        cerr<<"Usage: "<<argv[0]<<"<input.ll>"<<endl;
        return 1;
    }
    outs()<<argv;
    LLVMContext context;
    SMDiagnostic error;
    //parsing the IR file
    unique_ptr<Module> module = parseIRFile(argv[1], error, context);

    if(!module){
        cerr<<"Error parsing the IR file"<<endl;
        error.print(argv[0], errs());
        return 1;
    }
    outs()<<"Module Information\n";
    string moduleName = module->getName().str();
    outs()<<"Module Name: "<<moduleName<<"\n";

    int functionCount = 0;
    outs()<<"====================\n";
    outs()<<"FUNCTION DETAILS\n";
    outs()<<"====================\n";
    int idx = 1;
    for (Function &F: *module){
        outs()<<"Function #"<<idx++<<"\n\t";
        //functuion name
        outs()<<"Name: "<<F.getName().str()<<"\n\t";
        //func return type
        outs()<<"Return Type: ";
        Type *returnType = F.getReturnType();
        returnType->print(outs());
        outs()<<"\n\t";
        //no. of args
        int argsCount = F.arg_size();
        outs()<<"No. of parameters: "<<argsCount<<"\n\t";

        //args datatype
        if  (argsCount>0){
            outs()<<"Parameter Types: ";
            bool isFirst = true;
            for (Argument &Arg: F.args()){
                if (!isFirst) outs()<<", ";
                Type *argType = Arg.getType();
                argType->print(outs());
                isFirst=false;
            }
            outs()<<"\n\t";
        }
    

        if(F.isDeclaration()) outs()<<"Type: Declaration(no body)\n\t";
        else{
            outs()<<"Type: Definition(has body)\n\t";
            int basicBlockCount = F.size();
            outs() << "Basic Blocks: " << basicBlockCount << "\n\t";
            int totalInstructions = 0;
            for (BasicBlock &BB : F) {
                    totalInstructions += BB.size();
                }
            outs() << "Instructions: " << totalInstructions << "\n";
        }
    }

    outs()<<"====================\n";
    outs()<<"ANALYSIS COMPLETE\n";
    outs()<<"====================\n";
    return 0;
}