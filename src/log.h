/*
 * $File: log.h
 * $Date: Tue Dec 07 08:21:09 2010 +0800
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

enum LogLevel
{
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_CRITICAL,
	N_LOG_LEVEL
};

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
};

#endif // HEADER_LOG
