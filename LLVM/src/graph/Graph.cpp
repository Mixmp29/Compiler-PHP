#include <graph/Graph.hpp>

llvm::cl::opt<std::string> InputFilename(
        "i",
        llvm::cl::desc("Specify input filename"),
        llvm::cl::value_desc("filename"));

llvm::cl::opt<std::string> InputFilename2(
        "input",
        llvm::cl::desc("Specify input filename"),
        llvm::cl::value_desc("input file"));

llvm::cl::opt<std::string> OutputFilename(
        "o",
        llvm::cl::desc("Specify output filename"),
        llvm::cl::value_desc("filename"));

llvm::cl::opt<std::string> OutputFilename2(
        "output",
        llvm::cl::desc("Specify output filename"),
        llvm::cl::value_desc("output file"));

llvm::cl::opt<bool> DotCallGraph(
        "dot-callgraph", llvm::cl::desc("Enable binary output on terminals"));

llvm::cl::opt<bool> DotDefUse(
        "dot-def-use", llvm::cl::desc("Don't print informational messages"));

int main(int argc, char** argv)
{
    llvm::cl::ParseCommandLineOptions(argc, argv);

    if (DotCallGraph) {
        std::cout << InputFilename.c_str() << std::endl;
        generate_call_graph(InputFilename.c_str(), OutputFilename.c_str());
    }

    if (DotDefUse) {
        generate_def_use_graph(InputFilename.c_str(), OutputFilename.c_str());
    }

    return 0;
}
