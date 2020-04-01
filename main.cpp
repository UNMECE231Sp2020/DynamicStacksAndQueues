#include <iostream>
#include "StackDynamic.hpp"
#include "QueueDynamic.hpp"

int main() {
	Stack<int> s;
	std::cout << "Inital size: " << s.size() << std::endl;

	s.push(5);
	s.push(19);
	s.push(45);
	std::cout << "Size after three pushes: " << s.size() << std::endl;
	s.print();
	std::cout << "Top of the stack: " << s.top() << std::endl;

	Stack<int> second_stack(s);
	second_stack.print();
	second_stack.pop();
	second_stack.push(8);
	second_stack.print();

	Stack<double> a(9.8);
	a.print();

	Stack<double> b = a;
	b.print();
	a.push(6.2);

	Stack<double> c = a;
	c.print();

	std::cout << second_stack << std::endl;

	if(a == c) { std::cout << "nice" << std::endl; }
	if(b != c) { std::cout << "Eyy" << std::endl; }

	Queue<float> z;
	z.enqueue(4.1);
	z.enqueue(3.2);
	z.enqueue(2.3);
	z.enqueue(1.4);
	std::cout << z << std::endl;

	Queue<float> y(z);
	y.dequeue();
	y.print();
	y.enqueue(0.5);

	std::cout << "Front: " << y.front() << " back: " << y.back();
	std::cout << std::endl;

	return 0;
}
