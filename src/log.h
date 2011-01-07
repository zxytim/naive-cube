/*
 * $File: log.h
 * $Date: Thu Jan 06 15:28:05 2011 +0800
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


/*
 * naive-cube loggin system
 */
#ifndef HEADER_LOG
#define HEADER_LOG

#include <string>

#define LOG_LEVEL_DEBUG				0x01
#define LOG_LEVEL_INFO				0x02
#define LOG_LEVEL_WARNING			0x04
#define LOG_LEVEL_ERROR				0x08
#define LOG_LEVEL_CRITICAL			0x10
#define LOG_LEVEL_ALL				0x1F
#define N_LOG_LEVEL					5

typedef unsigned int LogLevel;
class Log
{
	public:
		static Log* instance();
		static void enable(LogLevel level);
		static void disable(LogLevel level);
		static void log(LogLevel level, std::string msg);
		static void enableFile();
		static void disableFile();
		static void setLogFile(std::string file);

	private:
		Log();
		~Log();
		static LogLevel log_table;
		static bool use_file;
};

#endif // HEADER_LOG
