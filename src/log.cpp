/*
* $File: log.cpp
* $Date: Wed Dec 29 09:20:41 2010 +0800
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
static bool log_table[N_LOG_LEVEL] = {
#ifdef DEBUG
	true, 
#else
	false,
#endif
	true,
   	true, 
	true, 
	true
};
static bool use_file = false;
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
	log_table[level] = true;
}

void Log::disable(LogLevel level)
{
	log_table[level] = false;
}

void Log::log(LogLevel level, std::string msg)
{
	if (log_table[level])
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

