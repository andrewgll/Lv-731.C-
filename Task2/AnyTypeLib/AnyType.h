// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_ANYTYPE_H_
#define _KLEPATSKYI_ANYTYPE_H_
#include "AnyTypeException.h"

/*
* Used to lossless convertation of fundamentals types.
* If value cannot be converted without loss of data,
* throws TypeConversionException
*/
template<typename T1, typename T2>
T2 tryConvert(T1 arg);

/*
* AnyType is a class for storing value of any fundamental type.
* 
* get*() methods will throw an exception if the type contained is not the type requested.
* 
* to*() methods will try to convert stored value to the requested type and
* if the converted value is not the same, e.g. loss of information/precision,
* the exception will be thrown.
*/
class AnyType {
public:
	enum Type : unsigned char {
		EMPTY = 0,
		BOOL,			
		CHAR,			// signed char
		UCHAR,			// unsigned char
		SHORT,			// short int
		USHORT,			// unsigned short int
		INT,			// int
		UINT,			// unsigned int
		FLOAT,			// float
		LONG,			// long int
		ULONG,			// unsigned long int
		DOUBLE,			// double
		LLONG,			// long long int
		ULLONG,			// unsigned long long int
		LDOUBLE			// long double
	};
private:
	union {
		bool _b;
		char _c;
		short int _si;
		int _i;
		long int _li;
		long long int _lli;
		float _f;
		double _d;
		long double _ld;
	};

	Type _storedType;
public:
	AnyType() : _ld(0), _storedType(EMPTY) {}
	AnyType(bool b) : _b(b), _storedType(BOOL) {}
	AnyType(char c) : _c(c), _storedType(CHAR) {}
	AnyType(unsigned char uc) : _c(uc), _storedType(UCHAR) {}
	AnyType(short int s) : _si(s), _storedType(SHORT) {}
	AnyType(unsigned short int us) : _si(us), _storedType(USHORT) {}
	AnyType(int i) : _i(i), _storedType(INT) {};
	AnyType(unsigned int ui) : _i(ui), _storedType(UINT) {};
	AnyType(long int li) : _li(li), _storedType(LONG) {};
	AnyType(unsigned long int uli) : _li(uli), _storedType(ULONG) {};
	AnyType(float f) : _f(f), _storedType(FLOAT) {};
	AnyType(double d) : _d(d), _storedType(DOUBLE) {};
	AnyType(long double ld) : _ld(ld), _storedType(LDOUBLE) {};
	AnyType(long long int lli) : _lli(lli), _storedType(LLONG) {};
	AnyType(unsigned long long int ulli) : _lli(ulli), _storedType(ULLONG) {};

	AnyType(const AnyType& other)
		: _ld(other._ld), _storedType(other._storedType)
	{}

	AnyType& operator=(const AnyType& other)
	{
		_ld = other._ld;
		_storedType = other._storedType;
	}

	AnyType(AnyType&& other) noexcept
		: _ld(other._ld), _storedType(other._storedType)
	{
		other.clear();
	}

	inline void clear()
	{
		_storedType = EMPTY;
		_ld = 0;
	}

	inline void swap(AnyType& other)
	{
		{
			long double temp = _ld;
			_ld = other._ld;
			other._ld = temp;
		}
		{
			Type temp = _storedType;
			_storedType = other._storedType;
			other._storedType = temp;
		}
	}

	inline Type valueType()
	{
		return _storedType;
	}

	inline AnyType& operator=(bool b)
	{
		_b = b; _storedType = BOOL; return *this;
	}
	inline AnyType& operator=(char c)
	{
		_c = c; _storedType = CHAR; return *this;
	}
	inline AnyType& operator=(unsigned char uc)
	{ 
		_c = uc; _storedType = UCHAR; return *this;
	}
	inline AnyType& operator=(short int s)
	{ 
		_si = s; _storedType = SHORT; return *this;
	}
	inline AnyType& operator=(unsigned short int us)
	{ 
		_si = us; _storedType = USHORT; return *this;
	}
	inline AnyType& operator=(int i)
	{ 
		_i = i; _storedType = INT; return *this;
	}
	inline AnyType& operator=(unsigned int ui)
	{
		_i = ui; _storedType = UINT; return *this;
	}
	inline AnyType& operator=(long int li)
	{ 
		_li = li; _storedType = LONG; return *this;
	}
	inline AnyType& operator=(unsigned long int uli)
	{ 
		_li = uli; _storedType = ULONG; return *this;
	}
	inline AnyType& operator=(float f)
	{ 
		_f = f; _storedType = FLOAT; return *this;
	}
	inline AnyType& operator=(double d)
	{ 
		_d = d; _storedType = DOUBLE; return *this;
	}
	inline AnyType& operator=(long double ld)
	{ 
		_d = ld; _storedType = LDOUBLE; return *this;
	}
	inline AnyType& operator=(long long int lli)
	{ 
		_lli = lli; _storedType = LLONG; return *this;
	}
	inline AnyType& operator=(unsigned long long int ulli)
	{ 
		_lli = ulli; _storedType = ULLONG; return *this;
	}

	inline bool getBool() const { checkType(BOOL); return _b; };
	inline char getChar() const { checkType(CHAR); return _c; };
	inline unsigned char getUChar() const { checkType(UCHAR); return _c; };
	inline short int getShort() const { checkType(SHORT); return _si; };
	inline unsigned short int getUShort() const { checkType(USHORT); return _si; };
	inline int getInt() const { checkType(INT); return _i; };
	inline unsigned int getUInt() const { checkType(UINT); return _i; };
	inline long int getLong() const { checkType(LONG); return _li; };
	inline unsigned long getULong() const { checkType(ULONG); return _li; };
	inline float getFloat() const { checkType(FLOAT); return _f; };
	inline double getDouble() const { checkType(DOUBLE); return _d; };
	inline long double getLDouble() const { checkType(LDOUBLE); return _ld; };
	inline long long int getLLong() const { checkType(LLONG); return _lli; }
	inline unsigned long long int getULLong() const { checkType(ULLONG); return _lli; }

	template<typename T>
	T to() const;

	inline bool toBool() const { return to<bool>(); };
	inline char toChar() const { return to<char>(); };
	inline unsigned char toUChar() const { return to<unsigned char>(); };
	inline short toShort() const { return to<short>(); };
	inline unsigned short toUShort() const { return to<unsigned short>(); };
	inline int toInt() const { return to<int>(); };
	inline unsigned int toUInt() const { return to<unsigned int>(); };
	inline long toLong() const { return to<long>(); };
	inline unsigned long toULong() const { return to<unsigned long>(); };
	inline float toFloat() const { return to<float>(); };
	inline double toDouble() const { return to<double>(); };
	inline long double toLDouble() const { return to<long double>(); };
	inline long long toLLong() const { return to<long long>(); }
	inline unsigned long long toULLong() const { return to<unsigned long long>(); }
	
private:
	inline void checkType(Type t) const
	{
		if (_storedType == AnyType::EMPTY)
			throw EmptyValueException();
		if (t != _storedType)
			throw StoredTypeMismatchException();
	}
};

template<typename T1, typename T2>
T2 tryConvert(T1 arg)
{
	T2 converted = static_cast<T2>(arg);
	std::string typename1 = typeid(T1).name();
	std::string typename2 = typeid(T2).name();
	// for signed/unsigned versions
	if (typename1.find("unsigned") == 0 || typename2.find("unsigned") == 0)
	{
		if (arg < 0 || converted < 0)
			throw TypeConversionException(typeid(T1).name(), typeid(T2).name());
	}
	T1 reconverted = static_cast<T1>(converted);
	if (arg != reconverted)
		throw TypeConversionException(typeid(T1).name(), typeid(T2).name());
	return converted;
}

template<typename T>
T AnyType::to() const
{
	switch (_storedType) {
	case EMPTY:
		throw EmptyValueException();
	case BOOL:
		return static_cast<T>(_b);
	case CHAR:
		return (tryConvert<char, T>(_c));
	case UCHAR:
		return tryConvert<unsigned char, T>(_c);
	case SHORT:
		return tryConvert<short, T>(_si);
	case USHORT:
		return tryConvert<unsigned short, T>(_si);
	case INT:
		return tryConvert<int, T>(_i);
	case UINT:
		return tryConvert<unsigned int, T>(_i);
	case FLOAT:
		return tryConvert<float, T>(_f);
	case LONG:
		return tryConvert<long, T>(_li);
	case ULONG:
		return tryConvert<unsigned long, T>(_li);
	case DOUBLE:
		return tryConvert<double, T>(_d);
	case LLONG:
		return tryConvert<long long, T>(_lli);
	case ULLONG:
		return tryConvert<unsigned long long, T>(_lli);
	case LDOUBLE:
		return tryConvert<long double, T>(_ld);
	}
};

#endif // _KLEPATSKYI_ANYTYPE_H_
