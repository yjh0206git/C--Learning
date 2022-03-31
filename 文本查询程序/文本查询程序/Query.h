#pragma once
#ifndef QUERY_H
#define QUERY_H

#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include<algorithm>
#include<iterator>
using namespace std;

class Query_base {
	friend class Query;
public:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual string rep() const = 0;
};

class Query {
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const string&);
	QueryResult eval(const TextQuery& t) const {
		return q->eval(t);
	}
	string rep() const { return q->rep(); }
private:
	Query(shared_ptr<Query_base> query) :q(query){}
	shared_ptr<Query_base> q;
};

inline 
ostream& operator<<(ostream& os, const Query& query) {
	return os << query.rep();
}

class WordQuery :public Query_base {
	friend class Query;
	WordQuery(const string& s):query_word(s){}
	QueryResult eval(const TextQuery& t) const {
		return t.query(query_word);
	}
	string rep() const { return query_word; }
	string query_word;
};

class NotQuery :public Query_base {
	friend Query operator~(const Query&);
	Query query;
	NotQuery(const Query& q):query(q){}
	string rep() const {
		return "~(" + query.rep() + ")";
	}
	QueryResult eval(const TextQuery&) const;
};

inline 
Query operator~(const Query& operand) {
	return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery :public Query_base {
protected:
	Query lhs, rhs;
	string opSym;
	BinaryQuery(const Query& l,const Query& r,string s):
		lhs(l),rhs(r),opSym(s){}
	string rep() const {
		return "(" + lhs.rep() + " " + opSym + " "
			+ rhs.rep() + ")";
	}
};

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query& left,const Query& right):
		BinaryQuery(left,right,"&"){}
	QueryResult eval(const TextQuery&) const;
};

inline 
Query operator&(const Query& lhs, const Query& rhs) {
	return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query& left, const Query& right) :
		BinaryQuery(left, right, "|") {
	}
	QueryResult eval(const TextQuery&) const;
};

inline
Query operator|(const Query& lhs, const Query& rhs) {
	return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline
Query::Query(const std::string& s) :q(new WordQuery(s))
{

}

#endif