/*
* $File: log.cpp
* $Date: Thu Jan 06 15:33:07 2011 +0800
* $Author: Zhou Xinyu <zxytim@gmail.com>
*/
/*
  This file is part of naive-cube

  Copyright (C) <2010>  Zhou Xinyu <zxytim@gmail.com>

  naive-cube is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  naive-cube is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with naive-cube.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "log.h"

#include <iostream>
#include <fstream>
#include <string>

static std::string file = "log";
static std::ofstream fout(file.c_str());
LogLevel Log::log_table;
bool Log::use_file;
static std::string prefix[N_LOG_LEVEL] = 
{
	"[DEBUG]",
	"[INFO]",
	"[WARNING]",
	"[ERROR]",
	"[CRITICAL]"
};

Log::Log()
{
	log_table = LOG_LEVEL_ALL;
#ifndef DEBUG
	log_table ^= LOG_LEVEL_DEBUG;
#endif
	use_file = false;
}

Log::~Log()
{
}

Log* Log::instance()
{
	static Log log;
	return &log;
}

void Log::enable(LogLevel level)
{
	log_table |= level;
}

void Log::disable(LogLevel level)
{
	if (log_table & level)
		log_table ^= level;
}

void Log::log(LogLevel level, std::string msg)
{
	fprintf(stdout, "HELLO");
	std::cout << "hello" ;
	if (log_table & level)
	{
		msg = prefix[level] + msg;
		if (use_file)
			fout << msg << std::endl;
		else
		{
			if (level < 3)
				std::cout << msg << std::endl;
			else std::cerr << msg << std::endl;
		}
	}
}

void Log::enableFile()
{
	use_file = true;
}

void Log::disableFile()
{
	use_file = false;
}

