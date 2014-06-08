/** 
 * @file param.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 9/6/2013
 *
 * 详细说明   
 */
#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include <windows.h>
#include <vector>

using namespace std;

enum v_type_val {
	type_none,
	type_int,
	type_char,
};

template <typename T> 
struct TypeTraits {
	enum  {
		result = v_type_val::type_none,
	};
};

template <>
struct TypeTraits<int> {
	enum  {
		result = v_type_val::type_int,
	};
};

class Var{
public:
	v_type_val vtype_;

	//virtual std::type_info GetType() = 0;
};

template <typename T> 
class VType : public Var{
public:
	typedef T type;

	enum {
		//typeval_ = TypeTraits<T>::result,
		typeval_ = 1,
	};

	VType<T>& operator = (T& t) 
    {
		this->val_ = &t;
        return *this;
	}

	VType<T>& operator = (T t) 
    {
		this->val_ = t;
        return *this;
	}

	VType() {};

	VType(T& p): val_(p) : vtype_() {}

	VType(T p): val_(p) : vtype_() {}

	T value() const {
		return val_;
	}

	/*virtual std::type_info GetType() {
		return typeid(T);
	}*/

	T val_;
};

struct ParameterList {
	std::vector<Var*> paramlist_;

	inline size_t GetSize() const
    {
        return paramlist_.size();
    }

	Var* operator [] (size_t pos) 
    {
        return (pos < GetSize() + 1) ? paramlist_[pos-1] : NULL;
	}

};
#endif