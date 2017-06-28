#pragma once
#include <limits.h>
#include <cmath>
#include <fstream>
#include <set>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::set;
using std::istream;
using std::ostream;
using std::pair;

class _Bin_matrix
{
protected:
	bool** matrix;
	size_t width;
	size_t height;
	void _create_matrix();
public:
	class TteratorMatrix;
	friend class IteratorMatrix;
	class IteratorMatrix
	{
	private:
		size_t width;
		size_t height;
		unsigned int heightIndex;
		unsigned int widthIndex;
		bool** matrix;
	public:
		IteratorMatrix(const _Bin_matrix&);
		IteratorMatrix(const IteratorMatrix&);
		const bool operator*()const;
		bool& operator*();
		IteratorMatrix operator++();
	};
	_Bin_matrix(size_t = 1, size_t = 1);
	_Bin_matrix(const _Bin_matrix&);
	~_Bin_matrix();
	const bool* operator[](int)const;
	bool* operator[](int);
	friend ostream& operator<<(ostream&, const _Bin_matrix&);
	friend istream& operator>>(istream&, _Bin_matrix&);
};


template<typename _FTy, typename _STy>
class Relation
{
	unsigned int firstIndex;
	unsigned int secondIndex;
	map<_FTy, unsigned int> firstSet;
	map<_STy, unsigned int> secondSet;
	_Bin_matrix matrix;
public:
	Relation(const set<_FTy>&, const set<_STy>&);
	void setPair(const _FTy&, const _STy&, bool = true);
	bool reflexivity()const;
	bool irreflexivity()const;
};

template<typename _FTy, typename _STy>
inline Relation<_FTy, _STy>::Relation(const set<_FTy>& _first, const set<_STy>& _second)
{	//constructin relation
	for (_FTy i : _first)
	{
		firstSet.insert(pair<_FTy, unsigned int>(firstIndex++, _first));
	}
	for (_STy i : _second)
	{
		secondSet.insert(pair<_STy, unsigned int>(secondIndex++, _second));
	}
	matrix._create_matrix(first.size, second.size);
}

template<typename _FTy, typename _STy>
inline void Relation<_FTy, _STy>::setPair(const _FTy& firstElement, const _STy& secondElement, bool _value)
{
	matrix[firstSet.find(firstElement)][secondSet.find(secondElement)] = _value;
}

template<typename _FTy, typename _STy>
inline bool Relation<_FTy, _STy>::reflexivity() const
{	//check reflexivity

}

template<typename _FTy, typename _STy>
inline bool Relation<_FTy, _STy>::irreflexivity() const
{
	if()
}

