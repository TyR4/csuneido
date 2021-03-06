#ifndef SUVALUE_H
#define SUVALUE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This file is part of Suneido - The Integrated Application Platform
 * see: http://www.suneido.com for more information.
 * 
 * Copyright (c) 2000 Suneido Software Corp. 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation - version 2. 
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License in the file COPYING
 * for more details. 
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "std.h"
#include <stdlib.h>

class Value;
class gcstring;
class Ostream;
class SuNumber;
class SuObject;
struct Named;

// abstract base class for user accessible values
class SuValue
	{
public:
	virtual ~SuValue()
		{ }
	virtual void out(Ostream&) = 0;

	virtual size_t hashfn();
	virtual int integer() const;
	virtual gcstring gcstr() const;
	virtual int symnum() const;				// creates if necessary
	virtual bool int_if_num(int* pn) const;	// defined by SuNumber
	virtual SuNumber* number();				// defined by SuNumber & SuString
	virtual const char* str_if_str() const;	// defined by SuString
	virtual SuObject* ob_if_ob();			// defined by SuObject & SuSeq
	SuObject* object();

	virtual Value call(Value self, Value member, 
		short nargs, short nargnames, ushort* argnames, int each);

	virtual Value getdata(Value);
	virtual void putdata(Value, Value);

	virtual size_t packsize() const;
	virtual void pack(char* buf) const;

	// WARNING: order-able types must define both order and lt
	virtual int order() const;
	virtual bool lt(const SuValue& y) const;
	virtual bool eq(const SuValue& y) const;

	virtual const char* type() const;
	virtual Named* get_named();

	// defined by value to release resources
	// called by WinMain message loop
	virtual void finalize();
	};

int order(char* name);

Ostream& operator<<(Ostream& out, SuValue* x);

#endif
