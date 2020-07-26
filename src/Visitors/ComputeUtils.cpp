#include "ComputeUtils.h"
#include "ComputeUtils.h"
#include <algorithm>
#include <iterator>

bool ComputeResult::IsValue()
{
	return requiredArgs.empty();
}

bool ComputeResult::IsRequiredArgs()
{
	return !requiredArgs.empty();
}

double ComputeResult::GetValue() const
{
	return value;
}

void ComputeResult::SetValue(double value)
{
	this->value = value;
}

void ComputeResult::AddRequiredArg(std::string const & name)
{
	requiredArgs.insert(name);
}

void ComputeResult::AddStringConstans(std::string const & name)
{
	stringConstants.insert(name);
}

void ComputeResult::MergeRequiredArgs(std::unordered_set<std::string> const & set)
{
	std::unordered_set<std::string> res;
	std::set_union(requiredArgs.begin(), requiredArgs.end(), set.begin(), set.end(), std::inserter(res, res.begin()));
	requiredArgs = std::move(res);
}

void ComputeResult::MergeStringConstants(std::unordered_set<std::string> const & set)
{
	std::unordered_set<std::string> res;
	std::set_union(stringConstants.begin(), stringConstants.end(), set.begin(), set.end(), std::inserter(res, res.begin()));
	stringConstants = std::move(res);
}

std::unordered_set<std::string> ComputeResult::GetRequiredArgs() const
{
	return requiredArgs;
}

std::unordered_set<std::string> ComputeResult::GetStringConsts() const
{
	return stringConstants;
}


//------------------------------------------------------------------------------------------------------------------------------


ComputeContext::ComputeContext()
{
}

ComputeContext::ComputeContext(std::vector<std::pair<const std::string, double>> const & il)
	: variables(il.begin(), il.end())
{
	
}

void ComputeContext::AddVariable(std::string const & name, double value)
{
	variables.emplace(name, value);
}

bool ComputeContext::HasVariable(std::string const & name) const
{
	return variables.find(name) != variables.end();
}

double ComputeContext::GetVariable(std::string const & name) const
{
	return (*variables.find(name)).second;
}

void ComputeContext::DeleteVariable(std::string const & name)
{
	variables.erase(name);
}

std::ostream & operator<<(std::ostream & os, ComputeResult const &  result)
{
	os << result.GetValue();
	for (auto & const_string : result.GetStringConsts())
	{
		os << " + " << const_string ;
	}

	return os;
}
