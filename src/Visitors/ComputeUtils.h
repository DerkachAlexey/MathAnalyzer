#pragma once 
#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>


class ComputeResult
{
	std::unordered_set<std::string> requiredArgs;
	std::unordered_set<std::string> stringConstants;
	double value;

public:

	bool IsValue();
	bool IsRequiredArgs();

	double GetValue() const;

	void SetValue(double value);
	void AddRequiredArg(std::string const& name);
	void AddStringConstans(std::string const& name);
	void MergeRequiredArgs(std::unordered_set<std::string> const& set);
	void MergeStringConstants(std::unordered_set<std::string> const& set);

	std::unordered_set<std::string> GetRequiredArgs() const;
	std::unordered_set<std::string> GetStringConsts() const;


};

std::ostream& operator << (std::ostream & os, ComputeResult const & result);

class ComputeContext
{
	std::unordered_map<std::string, double> variables;

public:
	ComputeContext();
	ComputeContext(std::vector<std::pair<const std::string, double>> const & il);
	void AddVariable(std::string const& name, double value);
	bool HasVariable(std::string const& name) const;
	double GetVariable(std::string const& name) const;
	void DeleteVariable(std::string const& name);

};