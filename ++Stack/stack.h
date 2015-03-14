#include <cassert>

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

template <class T>
class Stack {
public:
	Stack();
	Stack(int size);
	~Stack();
	int not_ok();
	int dump();
	int push(const double value);
	T pop();
	std::string strerror(int code);
private:
	T* data_;
	int count_;
	int size_;
	int stack_errno_;
};

template <class T> Stack<T>::Stack():
	data_(new T[STD_STACK_SIZE]), count_(0), size_(STD_STACK_SIZE), stack_errno_(STACK_IS_OK)
{
	assert(data_);
	memset(data_, 0, size_*sizeof(T));
	this->ok();
}

template <class T> Stack<T>::Stack(int size):
	data_(new T[size]), count_(0), size_(size), stack_errno_(STACK_IS_OK)
{
	assert(data_);
	memset(data_, 0, size_*sizeof(T));
	this->not_ok();
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
	}
	else if (count_>size_)
	{
		stack_errno_ = STACK_OVERFLOW;
	}
	else if (count_<0)
	{
		stack_errno_ = STACK_UNDERFLOW;
	}
	else
	{
		stack_errno_ = STACK_IS_OK;
	}

	return stack_errno_;
}

template <class T> int Stack<T>::dump() 
{
	using namespace std;
	cout << "Stack [" << this << "] [" << "" << this->strerror( this->not_ok() ) << "]" << endl;
	cout << "--->Count = " << count_ << ", Size = " << size_ << endl; 
	cout << "--->Data[" << data_ << "]" << endl;
	for (int i = 0; i < size_; i++)
	{
		cout << "[";
		cout.width(STACK_NUMBER_DIGITS);
		cout.fill('#');
		cout << i << "][" << &data_[i] << "]:";
		cout.width(STACK_MEMBER_WIDTH);
		cout.fill('-');
		cout << data_[i];
		if (i > count_-1) cout << "<---NU";
		cout << endl;
	}
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	return 0;
} 
template <class T> int Stack<T>::push(const double value)
{
	if(this->not_ok()) this->dump();

	count_++;
	
	if(this->not_ok() == STACK_OVERFLOW)
	{
		T* old_data = data_;
		T* new_data = new T[size_*2];
		assert(new_data);
		memset(new_data, 0, size_*2*sizeof(T));

		for (int i = 0; i < count_ - 1; i++)
		{
			new_data[i] = old_data[i];
		}

		delete [] old_data;
		data_ = new_data;
		size_ *= 2;
	}

	data_[count_-1] = value;
	if(this->not_ok()) this->dump();

	return stack_errno_;
}

template <class T> T Stack<T>::pop()
{
	if(this->ok()) this->dump();
	int result = data_[count_-1];
	count_--;
	if(this->ok()) this->dump();
	return result;
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
