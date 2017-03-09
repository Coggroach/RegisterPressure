#pragma once
#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "Graph.h"

using namespace llvm;

class ReducedPressurePass : public BasicBlockPass
{
private:
	std::vector<std::string> getOperandNames(Instruction*);
	bool processForGraph(BasicBlock &bb);

public:
	DataDependence::Graph* Graph;

	ReducedPressurePass();
	~ReducedPressurePass();

	bool runOnBasicBlock(BasicBlock &bb) override;

	static char ID;
};

