#include <iostream>
#include "include/taquin.h"
#include <ctime>
#include <iomanip>
// #include <chrono>  // Higher precision
// typedef std::chrono::high_resolution_clock Clock;

int main()
{
	unsigned f[] = { 1,2,3,4,5,6,7,8,0 };
	unsigned i[] = { 5,6,7,8,1,2,3,4,0 };  //Problema con solucion a maxima profundidad
	// unsigned i[]= {8,1,3,4,5,2,6,7,0};
	taquin::Taquin taq(i, f);

	//  auto t1= Clock::now();
	clock_t start = clock();
	std::cout << "EN AMPLITUD\n";
	taq.amplitud();
	taq.solucion();

	clock_t end = clock();
	//  auto t2= Clock::now();
	//  std::cout<< std::setprecision(10)<<"Tiempo empleado: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()<<std::endl;
	double time_elapsed = double(end - start);
	std::cout << "Tiempo empleado: " << time_elapsed / 1000 << std::endl;

	clock_t start2 = clock();
	//  auto t3= Clock::now();
	std::cout << "EN PROFUNDIDAD\n";
	// taq.profundidad();
	taq.profundidad(31);
	taq.solucion();

	clock_t end2 = clock();
	// auto t4= Clock::now();
	// std::cout <<"Tiempo empleado: "<<std::chrono::duration_cast<std::chrono::seconds>(t4 - t3).count()<<std::endl;
	double time_elapsed2 = double(end2 - start2);
	std::cout << "Tiempo empleado: " << time_elapsed2 / 1000 << std::endl;
}
