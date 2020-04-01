#include <iostream>

template <class Data>
class Stack {
	private:
		size_t _size;
		Data *_values;
	public:
		Stack() {
			_size = 0;
			_values = nullptr;
		}

		Stack(Data value) {
			_size = 1;
			_values = new Data(value);
		}

		Stack(const Stack &s) {
			if(s.size() == 0) {
				_size = 0;
				_values = nullptr;
			}
			else {
				int s_size = s.size();
				Data *s_values_copy = new Data[s_size];
				int i;
				for(i=0; i<s_size; i++) {
					*(s_values_copy+i) = *(s._values+i);
				}

				if(s_size == 1) {
					_values = new Data(*s_values_copy);
				}
				else {
					_values = new Data[s_size];
					for(i=0; i<s_size; i++) {
						*(_values+i) = *(s_values_copy+i);
					}
				}
				_size = s_size;
				delete [] s_values_copy;
			}
		}

		~Stack() {
			if(size() < 2) {
				delete _values;
			}
			else {
				delete [] _values;
			}
		}

		size_t size() const {
			return _size;
		}

		Data top() const {
			return *(_values+size()-1);
		}

		void push(Data value) {
			if(_values == nullptr) {
				_values = new Data(value);
				_size++;
			}
			else {
				int data_size = size();
				Data *data_copy = new Data[data_size];
				int i;
				for(i=0; i<data_size; i++) {
					*(data_copy+i) = *(_values+i);
				}

				delete [] _values;
				_values = new Data[data_size+1];

				for(i=0; i<data_size; i++) {
					*(_values+i) = *(data_copy+i);
				}
				*(_values+i) = value;
				_size++;
				delete [] data_copy;
			}
		}

		void pop() {
			if(_values == nullptr) {
				std::cout << "Could not pop empty Stack" << std::endl;
				return;
			}
			else if(size() == 1) {
				delete _values;
				_values = nullptr;
				_size = 0;
			}
			else {
				int data_size = size();
				Data *data_copy = new Data[data_size-1];
				int i;
				for(i=0; i<data_size-1; i++) {
					*(data_copy+i) = *(_values+i);
				}

				delete [] _values;
				_values = new Data[data_size-1];

				for(i=0; i<data_size-1; i++) {
					*(_values+i) = *(data_copy+i);
				}
				delete [] data_copy;
				_size--;
			}
		}

		void print() {
			for(int i=0; i<size(); i++) {
				std::cout << *(_values+i) << " ";
			}
			std::cout << std::endl;
		}

		bool empty() const {
			return (_values == nullptr) && (_size == 0);
		}

		bool search(Data value) {
			for(int i=0; i<size(); i++) {
				if(*(_values+i) == value) {
					return true;
				}
			}
			return false;
		}
		Stack<Data> operator=(const Stack<Data> &s) {
			if(s.size() == 0) {
				return *this;
			}
			if(s.size() == 1) {
				Data values_copy = *s._values;
				if(size() < 2) {
					delete _values;
				}
				else {
					delete [] _values;
				}
				_values = new Data(values_copy);
				_size = 1;
			}
			else {
				int values_size = s.size();
				Data *values_copy = new Data[values_size];
				for(int i=0; i<values_size; i++) {
					*(values_copy+i) = *(s._values+i);
				}

				if(size() < 2) {
					delete _values;
				}
				else {
					delete [] _values;
				}
				_values = new Data[values_size];

				for(int i=0; i<values_size; i++) {
					*(_values+i) = *(values_copy+i);
				}
				_size = values_size;
				delete [] values_copy;
			}
		}

		template <class S>
		friend std::ostream &operator<<(std::ostream &out, const Stack<S> &stack);

		template <class S>
		friend bool operator==(const Stack<S> &left_side, const Stack<S> &right_side);

		template <class S>
		friend bool operator!=(const Stack<S> &left_side, const Stack<S> &right_side);
};

template <class S>
std::ostream &operator<<(std::ostream &out, const Stack<S> &stack) {
	for(int i=0; i<stack.size(); i++) {
		out << *(stack._values+i) << " ";
	}
	return out;
}

template <class S>
bool operator==(const Stack<S> &left_side, const Stack<S> &right_side) {
	if(left_side.size() != right_side.size()) {
		return false;
	}
	for(int i=0; i<left_side.size(); i++) {
		if(*(left_side._values+i) != *(right_side._values+i)) {
			return false;
		}
	}
	return true;
}

template <class S>
bool operator!=(const Stack<S> &left_side, const Stack<S> &right_side) {
	return !(left_side==right_side);
}
