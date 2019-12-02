#pragma once



class NodeGraph
{
	class Block
	{
		// has some functionality
		virtual void init() {};
		virtual void execute() {};
	};

	template <typename  T>
	class Variable : Block
	{
		T& var;
	};

	template <typename T>
	class ComponentBlock : Block
	{
		T& component;
	};
	
	template <typename T>
	struct Connector
	{
		Block* owner;
		T& value;
	};
	
	template <typename A>
	struct Connection
	{
		Connector<A>* from = nullptr;
		Connector<A>* to = nullptr;
	};
	
public:
	NodeGraph() { id = 1; }
	int id;
};