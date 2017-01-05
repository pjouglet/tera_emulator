#ifndef _PACKET_HPP_
#define _PACKET_HPP_

#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <iostream>
#include "utils.hpp"
#include "data_type.hpp"

#define PACKET_MAX_SIZE 0xffff

class packet
{
	protected:
		ushort	pos_switch;
		ushort	size_max;
		void	write_len(ushort);

	public:
		packet();
		~packet();
		ushort	id;	// OpCode ID
		ushort	size;
		ushort	pos;
		byte*	raw;

		int	seek(int, int);
		bool	eof();

		virtual bool	swap();
		virtual bool	swap(ushort);
		packet*	clone();
		ushort	full_size();
		void	resize(int);
		void	get_header();
		virtual void	set_header();
		virtual void	set_header(ushort);

		virtual ushort	write(void*, ushort);
		virtual ushort	write(char*);
		virtual ushort	write(uchar);
		virtual ushort	write(ushort);
		virtual ushort	write(short);
		virtual ushort	write(uint);
		virtual ushort	write(int);
		virtual ushort	write(ulong);
		virtual ushort	write(long);
		virtual ushort	write(float);

		virtual ushort	read(void*, ushort);
		virtual byte*	read(ushort);
		virtual ushort	read(char*);
		char*	read_S();
		uchar	read_1();
		ushort	read_2();
		uint	read_4();
		ulong	read_8();
		float	read_F();
		virtual ushort	read(uchar*);
		virtual ushort	read(ushort*);
		virtual ushort	read(short*);
		virtual ushort	read(uint*);
		virtual ushort	read(int*);
		virtual ushort	read(ulong*);
		virtual ushort	read(long*);
		virtual ushort	read(float*);
};

#endif // _PACKET_HPP_
