#pragma once
#include <memory>
#include <type_traits>

class SymbolVisitor;
class Symbol
	: public std::enable_shared_from_this<Symbol>

{
public:
	virtual void Accept(SymbolVisitor * v) = 0;
	virtual std::shared_ptr<Symbol>  Clone() = 0;
	virtual ~Symbol() = 0
	{}
};

bool operator == (std::shared_ptr<Symbol> left, std::shared_ptr<Symbol> right);
std::ostream & operator<<(std::ostream& os, Symbol & s);