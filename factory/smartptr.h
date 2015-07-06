#ifndef SMARTPTR_INCLUDE_H
#define SMARTPTR_INCLUDE_H
#include <iostream>
using namespace std;
namespace commutil
{
	template<typename T>
	class SmartPtr
	{
	public:
		SmartPtr(T *p = 0);
		SmartPtr(const SmartPtr &);
		SmartPtr &operator=(const SmartPtr &);
		~SmartPtr();
		T &operator *();
		T *operator ->();
	private:
		void decreaseRef();
		T *m_p;
		int *m_useCnt;
	};
	template<typename T>
	SmartPtr<T>::SmartPtr(T *p=0):m_p(p)
	{
		//调用此构造函数时，默认引用数为1
		m_useCnt = new int(1);
	}

	template<typename T>
	SmartPtr<T>::SmartPtr(const SmartPtr &rhs)
	{
		//使用复制构造函数，创建新的对象，引用数加1
		this->m_p = rhs.m_p;
		this->m_useCnt = rhs.m_useCnt;
		(*m_useCnt)++;
	}

	template<typename T>
	SmartPtr<T>::~SmartPtr()
	{
		decreaseRef();
	}

	template<typename T>
	void SmartPtr<T>::decreaseRef()
	{
		if(--(*m_useCnt)==0)
		{//当引用数为0时，释放heap内存
			delete m_useCnt;
			delete m_p;
		}
	}

	template<typename T>
	T &SmartPtr<T>::operator *()
	{
		//重载解引用符
		return *m_p;
	}

	template<typename T>
	T *SmartPtr<T>::operator ->()
	{
		//重载 ->运算符，返回真实的对象指针
		return m_p;
	}

	template<typename T>
	SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr &anotherPtr)
	{
		if(this==&anotherPtr)
		{//防止自赋值
			return *this;
		}
		//使用赋值运算符，原来所指对象的引用数减1。
		decreaseRef();
		m_p = anotherPtr.m_p;
		m_useCnt = anotherPtr.m_useCnt;
		++*m_useCnt;//指向新的对象，所指对象引用数加1
		return *this;
	}
}
#endif