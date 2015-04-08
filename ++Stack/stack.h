#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

const int WRONG_NUM = 0;
const int STD_STACK_SIZE = 10;
const int STACK_NUMBER_DIGITS = 9;
const int STACK_MEMBER_WIDTH = 20;
enum STACK_ERRNO_VALUES
{ 
	STACK_IS_OK = 0, 
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	STACK_DATA_PTR_NULL
};

class Stack_exception
{
public:
	Stack_exception():state_code_(STACK_IS_OK){};
	Stack_exception(int code):state_code_(code){};
	~Stack_exception(){};
	int get_state_code();
private:
	int state_code_;
};


template <class T>
class Stack {
public:
	Stack();
	Stack(int size);
	~Stack();
	int not_ok();
	int dump(ostream& ostr);
	int push(const T value);
	T pop();
	template <class R> friend ostream& operator<<(ostream& ostr, const Stack<R>& stack);
	std::string strerror(int code);
	int react(Stack_exception exception);
private:
	T* data_;
	int count_;
	int size_;
	int stack_errno_;
};

template <class T> Stack<T>::Stack():
	data_(new T[STD_STACK_SIZE]), count_(0), size_(STD_STACK_SIZE), stack_errno_(STACK_IS_OK)
{
	try
	{
		assert(data_);
		memset(data_, 0, size_*sizeof(T));
		this->not_ok();
	}
	catch (Stack_exception exception)
	{
		this->react(exception);
	}
}

template <class T> Stack<T>::Stack(int size):
	data_(new T[size]), count_(0), size_(size), stack_errno_(STACK_IS_OK)
{
	try
	{
		assert(data_);
		memset(data_, 0, size_*sizeof(T));
		this->not_ok();
	}
	catch (Stack_exception exception)
	{
		this->react(exception);
	}
}

template <class T> Stack<T>::~Stack()
{
	delete [] data_;
	data_ = NULL;
	count_ = WRONG_NUM;
	size_ = WRONG_NUM;
} 
template <class T> int Stack<T>::not_ok() 
{
	if (!data_)
	{ 
		stack_errno_ = STACK_DATA_PTR_NULL;
		throw Stack_exception(STACK_DATA_PTR_NULL);
	}
	else if (count_>size_)
	{
		stack_errno_ = STACK_OVERFLOW;
		throw Stack_exception(STACK_OVERFLOW);
	}
	else if (count_<0)
	{
		stack_errno_ = STACK_UNDERFLOW;
		throw Stack_exception(STACK_UNDERFLOW);
	}
	else
	{
		stack_errno_ = STACK_IS_OK;
	}

	return stack_errno_;
}

template <class T> int Stack<T>::dump(ostream& ostr) 
{
	using namespace std;
	ostr << "Stack [" << this << "] [" << "" << this->strerror(this->stack_errno_) << "]" << endl;
	ostr << "--->Count = " << count_ << ", Size = " << size_ << endl; 
	ostr << "--->Data[" << data_ << "]" << endl;
	if (data_)
	{
		for (int i = 0; i < size_; i++)
		{
			ostr << "[";
			ostr.width(STACK_NUMBER_DIGITS);
			ostr.fill('#');
			ostr << i << "][" << &data_[i] << "]:";
			ostr.width(STACK_MEMBER_WIDTH);
			ostr.fill('-');
			ostr << data_[i];
			if (i > count_-1) ostr << "<---NU";
			ostr << endl;
		}
	}
	ostr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	return 0;
} 
template <class T> int Stack<T>::push(const T value)
{
	try
	{
		this->not_ok();
		count_++;
		this->not_ok();
		data_[count_-1] = value;
		this->not_ok();
		return stack_errno_;
	}
	catch (Stack_exception exception)
	{
		this->react(exception);
	}
}

template <class T> T Stack<T>::pop()
{
	try
	{
		this->not_ok();
		count_--;
		this->not_ok();
		int result = data_[count_];
		this->not_ok();
		return result;
	}
	catch (Stack_exception exception)
	{
		this->react(exception);
	}
}

template <class T> std::string Stack<T>::strerror(int code)
{
	std::string rtr_val = "";
	switch (code)
	{
		case STACK_IS_OK: rtr_val = "Stack is OK";				break;
		case STACK_OVERFLOW: rtr_val = "Stack overflow";			break;
		case STACK_UNDERFLOW: rtr_val = "Stack underflow";			break;
		case STACK_DATA_PTR_NULL: rtr_val = "Stack data null pointer";		break;
	}

	return rtr_val;
}


template <class T> ostream& operator<< (ostream& ostr, Stack<T>& stack)
{
	stack.dump(ostr);
	return ostr;
}

template <class T> int Stack<T>::react(Stack_exception exception)
{
	T* old_data = NULL;
	T* new_data = NULL;


	switch (exception.get_state_code())
	{
		case STACK_IS_OK: 	cerr << "The stack is OK, this message mustn't be written unless exceptions are developed wrong" << endl;
					cerr << "Okay, I'll give you a dump, to be on the safe side" << endl << this;
		break;
		case STACK_OVERFLOW:
					cerr << "There was an stack overflow, but I have an algorythm to fix it. It\' all right!!!" << endl;
					cerr << "Here\'s the dump for you to feel safe" << endl;
					old_data = data_;
					new_data = new T[size_*2];
					assert(new_data);
					memset(new_data, 0, size_*2*sizeof(T));

					for (int i = 0; i < count_ - 1; i++)
					{
						new_data[i] = old_data[i];
					}

					delete [] old_data;
					data_ = new_data;
					size_ *= 2;
					cerr << *this;
		break;
		case STACK_UNDERFLOW:
					cerr << "There\'s stack underflow. You mustn\'t let it REPEAT AGAIN!!! TAKE THE DUMP!!! FIX IT!!!";
					cerr << endl;
					cerr << *this;
		break;
		case STACK_DATA_PTR_NULL:
					cerr << "The data pointer is null in your stack. Here it is to make it clear:" << endl << *this;
		break;
		default:
					cerr << "The error only donkey can have!!! There is some unpredictable state. It\'s code is ";
					cerr << exception.get_state_code() << endl;
		break;
	}

	return 0;
}

int Stack_exception::get_state_code()
{
	return this->state_code_;
}
