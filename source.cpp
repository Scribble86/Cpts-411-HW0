#include <iostream>
# include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

//hello world program as directed. Easy stuff. also printing arguments and number of arguments supplied.
// this is written in c style.
int hello(int argc, char* argv[])
{
	printf("Hello World!\n");
	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{
			printf(argv[i]);
			printf("\n");
		}
	}
	else
	{
		printf("no additional arguments supplied.\n");
		char buf[256];
		sprintf_s(buf, 256, "%d", argc);
	}
	return 0;
}

//attempted to switch to C++ style for this and following prompts.

//takes input arguments (number, filename) and creates or overwrites the named file.
//fills it with random numbers between 0 and 6499 up to the number determined by number.
int input(int argc, char* argv[])
{
	if (argc > 1)
	{
		
		std::vector<int> v = {};
		int max = std::stoi(argv[1]);
		v.get_allocator().allocate(max);
		std::vector<int>::iterator it = v.begin();
		std::string filename = "default.txt";
		if (argc > 2)
		{
			filename = argv[2];
		}
		std::ofstream output{ filename, std::ofstream::out };
		for (int i = 0; i < max; i++)
		{
			int num = rand() % 6500;
			it = v.insert(it, num);
			std::cout << num << "\n";
			output << num << std::endl;
		}
		
		output.close();
	}
	else
	{
		std::cout << "No additional arguments provided.";
	}
	return 0;
}

//opens a file with the given name (otherwise opens the default name) and reads the supplied number of lines
//from the file. If the file is shorter than the number of lines, prints an error and quits. 
// if no arguments are provided, defaults to reading 0 lines and produces the sum anyway.
int output(int argc, char* argv[])
{
	std::string filename = "default.txt";
	std::ifstream input;
	int max = 0;
	if (argc > 2)
	{
		max = std::atoi(argv[1]);
		filename = argv[2];
	}
	try
	{
		input.open(filename, std::ifstream::in);
	}
	catch (const std::exception&)
	{
		std::cout << "No such file " << filename << std::endl;
		return 1;
	}
	std::vector<int> v = {};
	v.get_allocator().allocate(max);
	std::vector<int>::iterator it = v.begin();
	for (int i = 0; i < max; i++)
	{
		int num;
		try
		{
			std::string temp;
			input >> temp;
			num = std::stoi(temp);
		}
		catch (const std::exception&)
		{
			std::cout << "Unexpected end of file.\n";
			return 1;
		}
		if (input.good())
		{
			it = v.insert(it, num);
		}
	}
	input.close();
	int size = v.size();
	if (size > 0)
	{
		int sum = v[0];
		int max = v[0];
		int min = v[0];

		for (int i = 1; i < v.size(); i++)
		{
			int num = v[i];
			sum += num;
			if (num > max)
			{
				max = num;
			}
			if (num < min)
			{
				min = num;
			}
		}
		std::cout << "Sum: " << sum << "\nMin: " << min << "\nMax: " << max << "\n";
	}
	return 0;
}

//builds one very long array that is n*m in length, then carefully reads from the array
//as if it were a two-dimensional array. creates smaller n and m length arrays to store
//sums for columns and rows. As the array is built, the sums for rows and columns are
//also constructed. as the array is constructed, it is printed to the terminal in the
//expected two-dimensional way. when the array has been built, the results are printed.
int MatrixBuilder(int argc, char* argv[])
{
	int n = 0;
	int m = 0;
	std::vector<int> v = {};
	std::vector<int>::iterator vit = v.begin();
	std::vector<int> colSums = {};
	std::vector<int>::iterator cit = colSums.begin();
	std::vector<int> rowSums = {};
	std::vector<int>::iterator rit = rowSums.begin();
	if (argc > 2) {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
	}
	if (n > 0 and m > 0)
	{
		int max = n * m;
		int num;
		try
		{
			v.get_allocator().allocate(max);
			rowSums.get_allocator().allocate(m);
			colSums.get_allocator().allocate(n);
		}
		catch (const std::exception&)
		{
			std::cout << "Matrix size exceeds memory capacity. Aborting.\n";
			return -1;
		}
		for (int i = 0; i < max; i++)
		{
			if (i < n)
			{
				cit = colSums.insert(cit, 0);
				cit++;
			}
			if (i < m)
			{
				rit = rowSums.insert(rit, 0);
				rit++;
			}
			num = rand() % 4;
			vit = v.insert(vit, num);
			//std::cout << "i: " << i << "\n" << "num: " << v[i] << "\n" << "i % n: " << i % n << "\n" << "i / m: " << i / m << "\n";
			int row = i / n;
			int col = i % n;
			rowSums[row] += num;
			colSums[col] += num;
			if (i % n == 0)
			{
				std::cout << "\n";
			}
			std::cout << num << " ";
		}
		std::cout << "\nColumn Sums: ";
		for (int i = 0; i < colSums.size(); i++)
		{
			std::cout << colSums[i] << " ";
		}
		std::cout << "\nRow Sums: ";
		for (int i = 0; i < rowSums.size(); i++)
		{
			std::cout << rowSums[i] << " ";
		}
	}

}
