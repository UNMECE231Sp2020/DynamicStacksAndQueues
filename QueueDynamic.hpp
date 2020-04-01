#include <iostream>

template <class Data>
class Queue {
	private:
		size_t _size;
		Data *_values;
	public:
		Queue() {
			_size = 0;
			_values = nullptr;
		}

		Queue(Data value) {
			_size = 1;
			_values = new Data(value);
		}

		Queue(const Queue &q) {
			if(q.size() == 0) {
				_size = 0;
				_values = nullptr;
			}
			else {
				int q_size = q.size();
				Data *q_values_copy = new Data[q_size];
				int i;
				for(i=0; i<q_size; i++) {
					*(q_values_copy+i) = *(q._values+i);
				}

				if(q_size == 1) {
					_values = new Data(*q_values_copy);
				}
				else {
					_values = new Data[q_size];
					for(i=0; i<q_size; i++) {
						*(_values+i) = *(q_values_copy+i);
					}
				}
				_size = q_size;
				delete [] q_values_copy;
			}
		}

		~Queue() {
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

		Data front() const {
			return *(_values+size()-1);
		}

		Data back() const {
			return *_values;
		}

		void enqueue(Data value) {
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

				*(_values) = value;
				for(i=0; i<data_size; i++) {
					*(_values+i+1) = *(data_copy+i);
				}
				_size++;
				delete [] data_copy;
			}
		}

		void dequeue() {
			if(_values == nullptr) {
				std::cout << "Could not pop empty Queue" << std::endl;
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
			return _values == nullptr;
		}

		bool search(Data value) {
			for(int i=0; i<size(); i++) {
				if(*(_values+i) == value) {
					return true;
				}
			}
			return false;
		}

		Queue<Data> operator=(const Queue<Data> &q) {
			if(q.size() == 0) {
				return *this;
			}
			if(q.size() == 1) {
				Data values_copy = *q._values;
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
				int values_size = q.size();
				Data *values_copy = new Data[values_size];
				for(int i=0; i<values_size; i++) {
					*(values_copy+i) = *(q._values+i);
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

		template <class Q>
		friend std::ostream &operator<<(std::ostream &out, const Queue<Q> &queue);

		template <class Q>
		friend bool operator==(const Queue<Q> &left_side, const Queue<Q> &right_side);

		template <class Q>
		friend bool operator!=(const Queue<Q> &left_side, const Queue<Q> &right_side);
};

template <class Q>
std::ostream &operator<<(std::ostream &out, const Queue<Q> &queue) {
	for(int i=0; i<queue.size(); i++) {
		out << *(queue._values+i) << " ";
	}
	return out;
}

template <class Q>
bool operator==(const Queue<Q> &left_side, const Queue<Q> &right_side) {
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

template <class Q>
bool operator!=(const Queue<Q> &left_side, const Queue<Q> &right_side) {
	return !(left_side==right_side);
}
