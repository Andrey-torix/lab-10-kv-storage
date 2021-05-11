#pragma once
#include <boost/program_options.hpp>
#include <string>
class EApplication {
	char** argv;
	int argc;
public:

	void menu(int argc, const char** argv);
	int exec();
	std::string path_to_programm;
private:
	boost::program_options::positional_options_description p;
	
	boost::program_options::options_description m_desk{ "��������� �����" };
	boost::program_options::variables_map m_vm;
	/*
	--log-level
	--thread-count
	--output
	*/
	std::string log_level;      //
	int thread_count;   //���������� �������
	std::string path;     //���� � ����� � �����������
	std::string input_path; 
	
};