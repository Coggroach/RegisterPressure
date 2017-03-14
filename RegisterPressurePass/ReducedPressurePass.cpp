#include "ReducedPressurePass.h"
#include "Vertex.h"
#include "Edge.h"

static RegisterPass<ReducedPressurePass> X("ReducedPressurePass", "Reduced Register Pressure Pass", false, false);
char ReducedPressurePass::ID = 0;

std::vector<std::string> ReducedPressurePass::getOperandNames(Instruction* instruction)
{
	auto results = std::vector<std::string>();

	auto num = instruction->getNumOperands();
	for (auto i = 0; i < num; i++)
	{
		auto name = instruction->getOperand(i)->getName().str();
		if (name.empty())
			continue;
		if (std::find(results.begin(), results.end(), name) == results.end())
			results.push_back(name);
	}
	return results;
}

bool ReducedPressurePass::processForGraph(BasicBlock & bb)
{
	this->Graph = new DataDependence::Graph();

	for (BasicBlock::iterator bbi = bb.begin(); bbi != bb.end(); ++bbi)
	{
		auto instruction = bbi.getNodePtrUnchecked();
		auto name = instruction->getName().str();

		if (name.empty()) continue;

		auto operands = getOperandNames(instruction);
		this->Graph->AddVertex(name, operands);
	}

	this->Graph->CreateMinimumChains();
	this->Graph->CreateSchedule();
	return false;
}

ReducedPressurePass::ReducedPressurePass() : BasicBlockPass(ID)
{
}

ReducedPressurePass::~ReducedPressurePass()
{
}

bool ReducedPressurePass::runOnBasicBlock(BasicBlock & bb)
{
	return processForGraph(bb);
}
