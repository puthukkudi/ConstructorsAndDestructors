/*
* Demo to illustrate Constructor and Destructor usage
* Created by Prashant Puthukkudi
* Date : 28/06/2023
*/

#include <iostream>

/*
* Types of constructor call
* =======================
*/

class BaseDemo1
{
	private :
		int m_Value;
	public:
		 BaseDemo1(int x = 0) : m_Value(x)
		{
			std::cout << "BaseDemo1 parameterized constructor : m_Value : " << m_Value << std::endl;
		}

		BaseDemo1(const BaseDemo1 &other) : m_Value(other.m_Value) 
		{
			std::cout << "BaseDemo1 copy constructor : m_Value : " << m_Value << std::endl;
		}

		BaseDemo1& operator=(const BaseDemo1& other)
		{
			m_Value = other.m_Value;
			std::cout << "BaseDemo1 Copy assignment operator : m_Value : " << m_Value << std::endl;
			return *this;
		}

		~BaseDemo1()
		{
			std::cout << "BaseDemo1 called destructor : m_Value : " << m_Value << std::endl;
		}
};

/*
* Sequence of Constructor and destructor call in multilevel inheritance during upcasting
* =========================================================
*/

class BaseDemo2
{
public:
	BaseDemo2()
	{
		std::cout << "BaseDemo2  default constructor is called" << std::endl;
	}
	
	~BaseDemo2()
	{
		std::cout << "BaseDemo2  destructor is called" << std::endl;
	}
};

class ChildA :public BaseDemo2
{
public:
	ChildA()
	{
		std::cout << "ChildA  default constructor is called" << std::endl;
	}

	~ChildA()
	{
		std::cout << "ChildA  destructor is called" << std::endl;
	}
};

class ChildB :public ChildA
{
public:
	ChildB()
	{
		std::cout << "ChildB  default constructor is called" << std::endl;
	}

	~ChildB()
	{
		std::cout << "ChildB  destructor is called" << std::endl;
	}
};




/*
* Use of virtual destructor
* ================
*/
class BaseDemo3
{
public:
	//virtual BaseDemo3() // Compiler throws error.
    BaseDemo3()
	{
		std::cout << "BaseDemo3  default constructor is called" << std::endl;
	}

	virtual ~BaseDemo3()
	{
		std::cout << "BaseDemo3  destructor is called" << std::endl;
	}
};

class ChildC :public BaseDemo3
{
public:
	ChildC()
	{
		std::cout << "ChildC  default constructor is called" << std::endl;
	}

	~ChildC()
	{
		std::cout << "ChildC  destructor is called" << std::endl;
	}
};

class ChildD :public ChildC
{
public:
	ChildD()
	{
		std::cout << "ChildD default constructor is called" << std::endl;
	}

	~ChildD()
	{
		std::cout << "ChildD  destructor is called" << std::endl;
	}
};


/*
* Calling Base class constructor from Child class Constructor
* =====================================
*/

class BaseDemo4
{
protected : 
	int mX, mY;
public:
	BaseDemo4()
	{
		std::cout << mX <<" : "<<mY << std::endl; // prints garbage value as  data member mX and mY is not initiallized.
		std::cout << "DemoBase4  default constructor is called" << std::endl;		
	}

	BaseDemo4(int x)
	{
		std::cout << "DemoBase4  1 parameterized constructor is called" << std::endl;
	}

	BaseDemo4(int x, int y)
	{
		std::cout << "DemoBase4  2 parameterized constructor is called" << std::endl;
	}
};

class ChildE : public BaseDemo4
{
public:
	ChildE()
	{
		std::cout << "ChildE  default constructor is called" << std::endl;
	}

	ChildE(int x)
	{
		std::cout << "ChildE  1 parameterized constructor is called" << std::endl;
	}

	ChildE(int x, int y) : BaseDemo4(x, y)
	{
		std::cout << "ChildE  2 parameterized constructor is called" << std::endl;
	}
};

class ChildF : public ChildE
{
public:
	ChildF()
	{
		std::cout << "ChildF  default constructor is called" << std::endl;
	}

	ChildF(int x)
	{
		std::cout << "ChildF  1 parameterized constructor is called" << std::endl;
	}

	ChildF(int x, int y) : ChildE(x, y)
	{
		std::cout << "ChildF  2 parameterized constructor is called" << std::endl;
	}
};


int main()
{
	/*
	* Below statement tries to create an object of D1 and call the default constructor and throws an error
	* Compiler will not add default constructor if you have defined your own constructor
	* 
	* Types of constructor call
	*/
	{
		std::cout << "Types of constructor call :" << std::endl;
		BaseDemo1 Bd1_1;
		BaseDemo1 Bd1_2(4);
		BaseDemo1 Bd1_3(Bd1_2);
		BaseDemo1 Bd1_4;
		Bd1_4 = Bd1_3;
		std::cout << std::endl;
	}	
	std::cout << std::endl;

	/*
	* Sequence of Constructor and destructor call in multilevel inheritance
	*/
	{
		std::cout << "Sequence of Constructor and destructor call in multilevel inheritance : " << std::endl;
		ChildB b;		
		std::cout << std::endl;
	}
	std::cout << std::endl;

	/*
	* Sequence of Constructor and destructor call in multilevel inheritance during upcasting
	*/
	{
		std::cout << "Sequence of Constructor and destructor call in multilevel inheritance during upcasting : " << std::endl;
		BaseDemo2* Bd2_1 = new ChildB;
		delete Bd2_1;
		std::cout << std::endl;
	}
	std::cout << std::endl;

	/*
	* In above Bd2_1 destruction Destructor of BaseDemo2 is called as pointer is of type BaseDemo2 and destructor of ChildA and ChildB is never called which might result in memory leak
	* To avoid this we need to make destructor of BaseDemo2 as virtual.
	* Constructors can't be made virtual as compiler makes the virtual pointer and make it point to vtable in the constructor. If tried compiler will throw error.
	*/
	{
		std::cout << "Use of virtual destructor :  " << std::endl;
		BaseDemo3* Bd3_1 = new ChildD;
		delete Bd3_1;
		std::cout << std::endl;
	}

	{
		std::cout << "Calling Base class constructor from Child class Constructor : " << std::endl;
		ChildE e1;
		std::cout << std::endl;
		ChildE e2(5); // this will call DemoBase4 class default constructor then 1 parametrized constructor of ChildE
		std::cout << std::endl;
		ChildE e3(5, 6);  // this will call DemoBase4 class 2 parametrized constructor then 2 parametrized constructor of ChildE

		std::cout << std::endl<<std::endl;
			
		// Just an extension example
		ChildF f1;
		std::cout << std::endl;
		ChildF f2(5);
		std::cout << std::endl;
		ChildF f3(5, 6);
		std::cout << std::endl;

	}
	std::cin.get();
}