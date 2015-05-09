#include <iostream>
#include <cstring>
#include <cassert>

using std::ostream;
using std::cerr;
using std::bad_alloc;
using std::endl;
using std::string;
using std::exception;

const int WRONG_NUM = 0;
const int STD_STACK_SIZE = 10;
const int STACK_NUMBER_DIGITS = 9;
const int STACK_MEMBER_WIDTH = 20;
const int RETURN_EXC_CODE = 1;
enum STACK_ERRNO_VALUES
{ 
	STACK_IS_OK = 0, 
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	STACK_DATA_PTR_NULL,
    STACK_IMPOSSIBLE_TO_FIX
};

class Stack_exception : public exception
{
public:
	Stack_exception():state_code_(STACK_IS_OK){};
	Stack_exception(int code):state_code_(code){};
	~Stack_exception(){};
	inline int get_state_code() const noexcept;
    const char* what() const noexcept;
protected:
	int state_code_;
};

class Stack_crushed : public Stack_exception
{
public:
    Stack_crushed() {this->state_code_ = STACK_IMPOSSIBLE_TO_FIX;};
};


template <class T>
class Stack {
public:
	Stack(long size, ostream& ostr);
	~Stack();
	int not_ok();
	int dump(ostream& ostr) const;
	int push(const T value);
	T pop();
	template <class R> friend ostream& operator<<(ostream& ostr, const Stack<R>& stack) noexcept;
	int react(Stack_exception exception);
private:
	T* data_;
	int count_;
	int size_;
	int stack_errno_;
    ostream& stack_stream_;
};

template <class T> Stack<T>::Stack(long size = STD_STACK_SIZE, ostream& ostr = cerr):
	data_(nullptr), count_(0), size_(size), stack_errno_(STACK_IS_OK), stack_stream_(ostr)
{
	try
	{
        data_ = new T[size];
		memset(data_, 0, size_*sizeof(T));
		this->not_ok();
	}
    catch (bad_alloc)
    {
        this->react(Stack_exception(STACK_DATA_PTR_NULL));
        throw Stack_crushed(); 
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

template <class T> int Stack<T>::dump(ostream& ostr) const 
{
	ostr << "Stack [" << this << "]" << endl;
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
        return RETURN_EXC_CODE;
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
        return RETURN_EXC_CODE;
	}
}

const char* Stack_exception::what() const noexcept
{
	switch (this->state_code_)
	{
		case STACK_IS_OK: return "Stack is OK"; 			                           	break;
		case STACK_OVERFLOW: return "Stack overflow";	    	                      	break;
		case STACK_UNDERFLOW: return "Stack underflow"; 		                    	break;
		case STACK_DATA_PTR_NULL: return "Stack data null pointer"; 		            break;
        case STACK_IMPOSSIBLE_TO_FIX: return "It\'s impossible to fix this stack!!!";   break;
	}
}


template <class T> ostream& operator<< (ostream& ostr, Stack<T>& stack) noexcept
{
	stack.dump(ostr);
	return ostr;
}

template <class T> int Stack<T>::react(Stack_exception exc)
{
	T* old_data = NULL;
	T* new_data = NULL;

    this->stack_stream_ << exc.what() << endl;

	switch (exc.get_state_code())
	{
		case STACK_IS_OK: 	
                    this->stack_stream_ << "The stack is OK, this message mustn't be written unless exceptions are developed wrong" << endl;
					this->stack_stream_ << "Okay, I'll give you a dump, to be on the safe side" << endl << this;
		break;
		case STACK_OVERFLOW:
					this->stack_stream_ << "There was an stack overflow, but I have an algorythm to fix it. It\'s all right!!!" << endl;
					this->stack_stream_ << "Here\'s the dump for you to feel safe" << endl;
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
					this->stack_stream_ << *this;
		break;
		case STACK_UNDERFLOW:
					this->stack_stream_ << "There\'s stack underflow. You mustn\'t let it REPEAT AGAIN!!! TAKE THE DUMP!!! FIX IT!!!";
					this->stack_stream_ << endl;
					this->stack_stream_ << *this;
                    throw Stack_crushed();
		break;
		case STACK_DATA_PTR_NULL:
					this->stack_stream_ << "The data pointer is null in your stack. Here it is to make it clear:" << endl << *this;
                    throw Stack_crushed();
		break;
		default:
					this->stack_stream_ << "The error only donkey can have!!! There is some unpredictable state. It\'s code is ";
					this->stack_stream_ << exc.get_state_code() << endl;
                    throw Stack_crushed();
		break;
	}

	return 0;
}

inline int Stack_exception::get_state_code() const noexcept
{
	return this->state_code_;
}
