#include <iostream>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

#include <fstream>
#include <map>
#include <set>
#include <string>

void generate_call_graph(const std::string& input, const std::string& output)
{
    llvm::SMDiagnostic Err;
    llvm::LLVMContext Context;
    const auto Mod = parseIRFile(input, Err, Context);
    if (!Mod) {
        std::cerr << "Unable to read stream\n";
        return;
    }

    std::ofstream outputStream(output + ".dot");
    std::string outputString;
    llvm::raw_string_ostream rawOutputString(outputString);

    std::map<llvm::StringRef, std::set<llvm::StringRef>> calls;

    rawOutputString << "digraph D {\n";

    for (const auto& func : *Mod) {
        for (const auto& basic_block : func) {
            for (const auto& inst : basic_block) {
                if (const auto* ci = llvm::dyn_cast<llvm::CallInst>(&inst)) {
                    calls[func.getName()].insert(
                            ci->getCalledFunction()->getName());
                }
            }
        }
    }

    for (const auto& call : calls) {
        for (const auto& func : call.second) {
            rawOutputString << " " << call.first << " -> " << func << "\n";
        }
    }

    rawOutputString << "}";

    outputStream << outputString;

    std::string command = "dot " + output + ".dot -Tsvg -o " + output + ".svg";
    std::cout << command << std::endl;
    outputStream.close();
    system(command.c_str());
}

void generate_def_use_graph(const std::string& input, const std::string& output)
{
    llvm::SMDiagnostic Err;
    llvm::LLVMContext Context;
    const auto Mod = parseIRFile(input, Err, Context);
    if (!Mod) {
        std::cerr << "Unable to read stream\n";
        return;
    }

    std::ofstream outputStream(output + ".dot");
    std::string outputString;
    llvm::raw_string_ostream rawOutputString(outputString);
    rawOutputString << "digraph D {\n";
    for (const auto& func : *Mod) {
        for (const auto& basic_block : func) {
            for (const auto& inst : basic_block) {
                for (const auto* user : inst.users()) {
                    if (const auto* userInst
                        = llvm::dyn_cast<llvm::Instruction>(user)) {
                        rawOutputString << "\"" << *userInst << "\" -> \""
                                        << inst << "\"\n";
                    }
                }
            }
        }
    }
    rawOutputString << "}";

    outputStream << outputString;

    std::string command = "dot " + output + ".dot -Tsvg -o " + output + ".svg";
    std::cout << command << std::endl;
    outputStream.close();
    system(command.c_str());
}