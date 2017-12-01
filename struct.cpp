#include "struct.h"
#include "iterator.h"
Iterator * Struct::createIterator()
{
	return new StructIterator(this);
}
Iterator * Struct::createDFSIterator()
{
	return new DFSIterator<Struct>(this);
}
Iterator * Struct::createBFSIterator()
{
	return new BFSIterator<Struct>(this);
}