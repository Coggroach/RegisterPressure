#include "ReducedPressurePass.h"
#include "Vertex.h"
#include "Edge.h"
#include "Scheduler.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

static RegisterPass<ReducedPressurePass> X("ReducedPressurePass", "Reduced Register Pressure Pass", true, false);
char ReducedPressurePass::ID = 0;

std::vector<std::string> ReducedPressurePass::getOperandNames(const Instruction& instruction)
{
	auto results = std::vector<std::string>();

	auto num = instruction.getNumOperands();
	for (auto i = 0; i < num; i++)
	{
		auto name = instruction.getOperand(i)->getName().str();
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

	for (auto& instruction : bb)
	{
		auto name = instruction.getName().str();

		if (name.empty()) continue;

		auto operands = getOperandNames(instruction);
		this->Graph->AddVertex(name, operands);
	}

	this->Graph->CreateMinimumChains();
	this->Graph->LinkVerticesToChains();
	this->Graph->CreateSchedule();
	return false;
}

bool ReducedPressurePass::processReorder(BasicBlock &bb)
{
	auto& sch = this->Graph->Schedule->Schedule;
	if (sch.size() == 0)
		return false;	

	auto ins = std::vector<Instruction*>();
	for (auto s : sch)
	{
		for (auto& instruction : bb)
		{
			if (s->Name == instruction.getName().str())
			{
				auto clone = instruction.clone();
				auto name = instruction.getName();
				clone->setName(s->RegisterName + "_");
				ins.push_back(clone);
				break;
			}
		}
	}

	int i = 0;
	for (auto bbi = bb.begin(), bbe = bb.end(); bbi != bbe; ++bbi)
	{
		if (bbi->getName().empty())
			continue;
		ReplaceInstWithInst(bb.getInstList(), bbi, ins[i++]);
	}
	errs() << bb;
 	return true;
}

ReducedPressurePass::ReducedPressurePass() : BasicBlockPass(ID) { }

ReducedPressurePass::~ReducedPressurePass() { }

bool ReducedPressurePass::runOnBasicBlock(BasicBlock & bb)
{
	return processForGraph(bb) || processReorder(bb);
}
