// iostream standard header for Microsoft
#pragma once
#ifndef _IOSTREAM_
#define _IOSTREAM_
#ifndef RC_INVOKED
// istream standard header
#pragma once
#ifndef _ISTREAM_
#define _ISTREAM_
#ifndef RC_INVOKED
// ostream standard header
#pragma once
#ifndef _OSTREAM_
#define _OSTREAM_
#ifndef RC_INVOKED
#include <ios>

#ifdef _MSC_VER
 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
 #pragma warning(disable: 4390)
#endif  /* _MSC_VER */

_STD_BEGIN

		// I/O EXCEPTION MACROS

 #if _HAS_EXCEPTIONS
 #define _TRY_IO_BEGIN	_TRY_BEGIN	/* begin try block */

 #define _CATCH_IO_END	_CATCH_ALL	/* catch block for _Myios */ \
	_Myios::setstate(ios_base::badbit, true);	/* set badbit and rethrow */ \
	_CATCH_END

 #define _CATCH_IO_(x)	_CATCH_ALL	/* catch block for basic_ios x */ \
	(x).setstate(ios_base::badbit, true);	/* set badbit and rethrow */ \
	_CATCH_END

 #else /* _HAS_EXCEPTIONS */
 #define _TRY_IO_BEGIN	{	/* begin try block */

 #define _CATCH_IO_END	}	/* catch block for _Myios */

 #define _CATCH_IO_(x)	}	/* catch block for basic_ios x */
 #endif /* _HAS_EXCEPTIONS */

		// TEMPLATE CLASS basic_ostream
template<class _Elem,
	class _Traits>
	class basic_ostream
		: virtual public basic_ios<_Elem, _Traits>
	{	// control insertions into a stream buffer
public:
	typedef basic_ostream<_Elem, _Traits> _Myt;
	typedef basic_ios<_Elem, _Traits> _Myios;
	typedef basic_streambuf<_Elem, _Traits> _Mysb;
	typedef ostreambuf_iterator<_Elem, _Traits> _Iter;
	typedef num_put<_Elem, _Iter> _Nput;

	explicit __CLR_OR_THIS_CALL basic_ostream(basic_streambuf<_Elem, _Traits> *_Strbuf,
		bool _Isstd = false)
		{	// construct from a stream buffer pointer
		_Myios::init(_Strbuf, _Isstd);
		}

	__CLR_OR_THIS_CALL basic_ostream(_Uninitialized, bool _Addit = true)
		{	// construct uninitialized
		if (_Addit)
			ios_base::_Addstd(this);	// suppress for basic_iostream
		}

	virtual __CLR_OR_THIS_CALL ~basic_ostream()
		{	// destroy the object
		}

	typedef typename _Traits::int_type int_type;
	typedef typename _Traits::pos_type pos_type;
	typedef typename _Traits::off_type off_type;

	class _Sentry_base
		{	// stores thread lock and reference to output stream
	public:
		__CLR_OR_THIS_CALL _Sentry_base(_Myt& _Ostr)
			: _Myostr(_Ostr)
			{	// lock the stream buffer, if there
			if (_Myostr.rdbuf() != 0)
				_Myostr.rdbuf()->_Lock();
			}

		__CLR_OR_THIS_CALL ~_Sentry_base()
			{	// destroy after unlocking
			if (_Myostr.rdbuf() != 0)
				_Myostr.rdbuf()->_Unlock();
			}

		_Myt& _Myostr;	// the output stream, for _Unlock call at destruction
		};

	class sentry
		: public _Sentry_base
		{	// stores thread lock and state of stream
	public:
		explicit __CLR_OR_THIS_CALL sentry(_Myt& _Ostr)
			: _Sentry_base(_Ostr)
			{	// construct locking and testing stream
			if (_Ostr.good() && _Ostr.tie() != 0)
				_Ostr.tie()->flush();
			_Ok = _Ostr.good();	// store test only after flushing tie
			}

		__CLR_OR_THIS_CALL ~sentry()
			{	// destroy the object

 #if _HAS_EXCEPTIONS
			if (!_XSTD uncaught_exception())
				this->_Myostr._Osfx();
			}

 #else /* _HAS_EXCEPTIONS */
			this->_Myostr._Osfx();
		}
 #endif /* _HAS_EXCEPTIONS */

		__CLR_OR_THIS_CALL operator bool() const
			{	// test if stream state okay
			return (_Ok);
			}

	private:
		__CLR_OR_THIS_CALL sentry(const sentry&);	// not defined
		sentry& __CLR_OR_THIS_CALL operator=(const sentry&);	// not defined

		bool _Ok;	// true if stream state okay at construction
		};

	bool __CLR_OR_THIS_CALL opfx()
		{	// test stream state and flush tie stream as needed (retained)
		if (ios_base::good() && _Myios::tie() != 0)
			_Myios::tie()->flush();
		return (ios_base::good());
		}

	void __CLR_OR_THIS_CALL osfx()
		{	// perform any wrapup (retained)
		_Osfx();
		}

	void __CLR_OR_THIS_CALL _Osfx()
		{	// perform any wrapup
		_TRY_BEGIN
		if (ios_base::flags() & ios_base::unitbuf)
			flush();	// flush stream as needed
		_CATCH_ALL
		_CATCH_END
		}

#ifdef  _M_CEE_PURE
	_Myt& __CLR_OR_THIS_CALL operator<<(_Myt& (__clrcall *_Pfn)(_Myt&))
		{	// call basic_ostream manipulator
		_DEBUG_POINTER(_Pfn);
		return ((*_Pfn)(*this));
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(_Myios& (__clrcall *_Pfn)(_Myios&))
		{	// call basic_ios manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(_Myios *)this);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(ios_base& (__clrcall *_Pfn)(ios_base&))
		{	// call ios_base manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(ios_base *)this);
		return (*this);
		}

#endif

	_Myt& __CLR_OR_THIS_CALL operator<<(_Myt& (__cdecl *_Pfn)(_Myt&))
		{	// call basic_ostream manipulator
		_DEBUG_POINTER(_Pfn);
		return ((*_Pfn)(*this));
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(_Myios& (__cdecl *_Pfn)(_Myios&))
		{	// call basic_ios manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(_Myios *)this);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(ios_base& (__cdecl *_Pfn)(ios_base&))
		{	// call ios_base manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(ios_base *)this);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(_Bool _Val)
		{	// insert a boolean
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(short _Val)
		{	// insert a short
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);
			ios_base::fmtflags _Bfl =
				ios_base::flags() & ios_base::basefield;
			long _Tmp = (_Bfl == ios_base::oct
				|| _Bfl == ios_base::hex)
				? (long)(unsigned short)_Val : (long)_Val;

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Tmp).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

        /*  Note that if your stream is wchar_t, and you are not using native wchar_t
            Then this operation will be unavailable as there is an explicit
            specialisation further down this file that is designed to treat an
            unsigned short as a character.

            If you wish to read or write unsigned shorts to wchar_t streams, you should
            consider making wchar_t a native type by turning on /Zc:wchar_t
        */
	_Myt& __CLR_OR_THIS_CALL operator<<(unsigned short _Val)
		{	// insert an unsigned short
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), (unsigned long)_Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(int __w64 _Val)
		{	// insert an int
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);
			ios_base::fmtflags _Bfl =
				ios_base::flags() & ios_base::basefield;
			long _Tmp = (_Bfl == ios_base::oct
				|| _Bfl == ios_base::hex)
				? (long)(unsigned int)_Val : (long)_Val;

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Tmp).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(unsigned int __w64 _Val)
		{	// insert an unsigned int
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), (unsigned long)_Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(long _Val)
		{	// insert a long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(unsigned long __w64 _Val)
		{	// insert an unsigned long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), (unsigned long)_Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

 #ifdef _LONGLONG
	_Myt& __CLR_OR_THIS_CALL operator<<(_LONGLONG _Val)
		{	// insert a long long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(_ULONGLONG _Val)
		{	// insert an unsigned long long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}
 #endif /* _LONGLONG */

	_Myt& __CLR_OR_THIS_CALL operator<<(float _Val)
		{	// insert a float
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), (double)_Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(double _Val)
		{	// insert a double
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(long double _Val)
		{	// insert a long double
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(const void *_Val)
		{	// insert a void pointer
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to insert
			const _Nput& _Nput_fac = _USE(ios_base::getloc(), _Nput);

			_TRY_IO_BEGIN
			if (_Nput_fac.put(_Iter(_Myios::rdbuf()), *this,
				_Myios::fill(), _Val).failed())
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator<<(_Mysb *_Strbuf)
		{	// insert until end-of-file from a stream buffer
		ios_base::iostate _State = ios_base::goodbit;
		bool _Copied = false;
		const sentry _Ok(*this);

		if (_Ok && _Strbuf != 0)
			for (int_type _Meta = _Traits::eof(); ; _Copied = true)
				{	// extract another character from stream buffer
				_TRY_BEGIN
				_Meta = _Traits::eq_int_type(_Traits::eof(), _Meta)
					? _Strbuf->sgetc() : _Strbuf->snextc();
				_CATCH_ALL
					_Myios::setstate(ios_base::failbit);
					_RERAISE;
				_CATCH_END

				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					break;	// end of file, quit

				_TRY_IO_BEGIN
					if (_Traits::eq_int_type(_Traits::eof(),
						_Myios::rdbuf()->sputc(
							_Traits::to_char_type(_Meta))))
						{	// insertion failed, quit
						_State |= ios_base::badbit;
						break;
						}
				_CATCH_IO_END
				}

		ios_base::width(0);
		_Myios::setstate(_Strbuf == 0 ? ios_base::badbit
			: !_Copied ? _State | ios_base::failbit : _State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL put(_Elem _Ch)
		{	// insert a character
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (!_Ok)
			_State |= ios_base::badbit;
		else
			{	// state okay, insert character
			_TRY_IO_BEGIN
			if (_Traits::eq_int_type(_Traits::eof(),
				_Myios::rdbuf()->sputc(_Ch)))
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL write(const _Elem *_Str,
		streamsize _Count)
		{	// insert _Count characters from array _Str
		if (0 < _Count)
			_DEBUG_POINTER(_Str);
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (!_Ok)
			_State |= ios_base::badbit;
		else
			{	// state okay, insert characters
			_TRY_IO_BEGIN
			if (_Myios::rdbuf()->sputn(_Str, _Count) != _Count)
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL flush()
		{	// flush output stream
		ios_base::iostate _State = ios_base::goodbit;
		if (!ios_base::fail() && _Myios::rdbuf()->pubsync() == -1)
			_State |= ios_base::badbit;	// sync failed
		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL seekp(pos_type _Pos)
		{	// set output stream position to _Pos
		if (!ios_base::fail()
			&& (off_type)_Myios::rdbuf()->pubseekpos(_Pos,
				ios_base::out) == _BADOFF)
			_Myios::setstate(ios_base::failbit);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL seekp(off_type _Off, ios_base::seekdir _Way)
		{	// change output stream position by _Off, according to _Way
		if (!ios_base::fail()
			&& (off_type)_Myios::rdbuf()->pubseekoff(_Off, _Way,
				ios_base::out) == _BADOFF)
			_Myios::setstate(ios_base::failbit);
		return (*this);
		}

	pos_type __CLR_OR_THIS_CALL tellp()
		{	// return output stream position
		if (!ios_base::fail())
			return (_Myios::rdbuf()->pubseekoff(0,
				ios_base::cur, ios_base::out));
		else
			return (pos_type(_BADOFF));
		}
	};

#ifndef _NATIVE_WCHAR_T_DEFINED
/*
This explicit template specialisation writes a single unicode character to the stream.

By default, the compiler treats wchar_t as if it were a typedef for unsigned short. This means
that we cannot distinguish between an unsigned short and a wchar_t in the library. To be most
consistent with previous practice, we add this explicit specialisation to ensure that a single
unsigned short is read and written as a character.

If you wish to read and write unsigned shorts as integers, we recommend you consider making
wchar_t a native type by using the /Zc:wchar_t compiler switch.
*/
template <> inline
	basic_ostream<unsigned short, char_traits<unsigned short> >&__CLR_OR_THIS_CALL
        basic_ostream<unsigned short, char_traits<unsigned short> >::operator<<(
		unsigned short _Ch)
	{	// insert a character
	typedef basic_ostream<unsigned short, char_traits<unsigned short> > _Myos;
        typedef char_traits<unsigned short> _Traits;
        _Myos &_Ostr=*this;
	ios_base::iostate _State = ios_base::goodbit;
	const _Myos::sentry _Ok(_Ostr);

	if (_Ok)
		{	// state okay, insert
		streamsize _Pad = _Ostr.width() <= 1 ? 0 : _Ostr.width() - 1;

		_TRY_IO_BEGIN
		if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
			for (; _State == ios_base::goodbit && 0 < _Pad;
				--_Pad)	// pad on left
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					_State |= ios_base::badbit;

		if (_State == ios_base::goodbit
			&& _Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ch)))
			_State |= ios_base::badbit;

		for (; _State == ios_base::goodbit && 0 < _Pad;
			--_Pad)	// pad on right
			if (_Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ostr.fill())))
				_State |= ios_base::badbit;
		_CATCH_IO_(_Ostr)
		}

	_Ostr.width(0);
	_Ostr.setstate(_State);
	return (_Ostr);
	}
#endif

 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

template class _CRTIMP2_PURE basic_ostream<char, char_traits<char> >;
template class _CRTIMP2_PURE basic_ostream<wchar_t, char_traits<wchar_t> >;



 #endif /* _DLL_CPPLIB */

		// INSERTERS

 template<class _Elem,
	class _Traits> inline
	basic_ostream<_Elem, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<_Elem, _Traits>& _Ostr, const char *_Val)
	{	// insert NTBS
	ios_base::iostate _State = ios_base::goodbit;
	streamsize _Count = (streamsize)::strlen(_Val);	// may overflow
	streamsize _Pad = _Ostr.width() <= 0 || _Ostr.width() <= _Count
		? 0 : _Ostr.width() - _Count;
	const typename basic_ostream<_Elem, _Traits>::sentry _Ok(_Ostr);

	if (!_Ok)
		_State |= ios_base::badbit;
	else
		{	// state okay, insert characters
		_TRY_IO_BEGIN
		const ctype<_Elem>& _Ctype_fac = _USE(_Ostr.getloc(), ctype<_Elem>);
		if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
			for (; 0 < _Pad; --_Pad)	// pad on left
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
					_State |= ios_base::badbit;
					break;
					}

		for (; _State == ios_base::goodbit && 0 < _Count; --_Count, ++_Val)
			if (_Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ctype_fac.widen(*_Val))))
					_State |= ios_base::badbit;

		if (_State == ios_base::goodbit)
			for (; 0 < _Pad; --_Pad)	// pad on right
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
					_State |= ios_base::badbit;
					break;
					}
		_Ostr.width(0);
		_CATCH_IO_(_Ostr)
		}

	_Ostr.setstate(_State);
	return (_Ostr);
	}

template<class _Elem,
	class _Traits> inline
	basic_ostream<_Elem, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<_Elem, _Traits>& _Ostr, char _Ch)
	{	// insert a character
	ios_base::iostate _State = ios_base::goodbit;
	const typename basic_ostream<_Elem, _Traits>::sentry _Ok(_Ostr);

	if (_Ok)
		{	// state okay, insert
		const ctype<_Elem>& _Ctype_fac = _USE(_Ostr.getloc(), ctype<_Elem>);
		streamsize _Pad = _Ostr.width() <= 1 ? 0 : _Ostr.width() - 1;

		_TRY_IO_BEGIN
		if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
			for (; _State == ios_base::goodbit && 0 < _Pad;
				--_Pad)	// pad on left
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					_State |= ios_base::badbit;

		if (_State == ios_base::goodbit
			&& _Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ctype_fac.widen(_Ch))))
			_State |= ios_base::badbit;

		for (; _State == ios_base::goodbit && 0 < _Pad;
			--_Pad)	// pad on right
			if (_Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ostr.fill())))
				_State |= ios_base::badbit;
		_CATCH_IO_(_Ostr)
		}

	_Ostr.width(0);
	_Ostr.setstate(_State);
	return (_Ostr);
	}

template<class _Traits> inline
	basic_ostream<char, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<char, _Traits>& _Ostr,
		const char *_Val)
	{	// insert NTBS into char stream
	typedef char _Elem;
	typedef basic_ostream<_Elem, _Traits> _Myos;
	ios_base::iostate _State = ios_base::goodbit;
	streamsize _Count = (streamsize)_Traits::length(_Val);	// may overflow
	streamsize _Pad = _Ostr.width() <= 0 || _Ostr.width() <= _Count
		? 0 : _Ostr.width() - _Count;
	const typename _Myos::sentry _Ok(_Ostr);

	if (!_Ok)
		_State |= ios_base::badbit;
	else
		{	// state okay, insert
		_TRY_IO_BEGIN
		if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
			for (; 0 < _Pad; --_Pad)	// pad on left
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
					_State |= ios_base::badbit;
					break;
					}

		if (_State == ios_base::goodbit
			&& _Ostr.rdbuf()->sputn(_Val, _Count) != _Count)
			_State |= ios_base::badbit;

		if (_State == ios_base::goodbit)
			for (; 0 < _Pad; --_Pad)	// pad on right
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
					_State |= ios_base::badbit;
					break;
					}
		_Ostr.width(0);
		_CATCH_IO_(_Ostr)
		}

	_Ostr.setstate(_State);
	return (_Ostr);
	}

template<class _Traits> inline
	basic_ostream<char, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<char, _Traits>& _Ostr, char _Ch)
	{	// insert a char into char stream
	typedef char _Elem;
	typedef basic_ostream<_Elem, _Traits> _Myos;
	ios_base::iostate _State = ios_base::goodbit;
	const typename _Myos::sentry _Ok(_Ostr);

	if (_Ok)
		{	// state okay, insert
		streamsize _Pad = _Ostr.width() <= 1 ? 0 : _Ostr.width() - 1;

		_TRY_IO_BEGIN
		if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
			for (; _State == ios_base::goodbit && 0 < _Pad;
				--_Pad)	// pad on left
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					_State |= ios_base::badbit;

		if (_State == ios_base::goodbit
			&& _Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ch)))
			_State |= ios_base::badbit;

		for (; _State == ios_base::goodbit && 0 < _Pad;
			--_Pad)	// pad on right
			if (_Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ostr.fill())))
				_State |= ios_base::badbit;
		_CATCH_IO_(_Ostr)
		}

	_Ostr.width(0);
	_Ostr.setstate(_State);
	return (_Ostr);
	}

template<class _Elem,
	class _Traits> inline
	basic_ostream<_Elem, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<_Elem, _Traits>& _Ostr, const _Elem *_Val)
	{	// insert NTCS
	typedef basic_ostream<_Elem, _Traits> _Myos;
	ios_base::iostate _State = ios_base::goodbit;
	streamsize _Count = (streamsize)_Traits::length(_Val);	// may overflow
	streamsize _Pad = _Ostr.width() <= 0 || _Ostr.width() <= _Count
		? 0 : _Ostr.width() - _Count;
	const typename _Myos::sentry _Ok(_Ostr);

	if (!_Ok)
		_State |= ios_base::badbit;
	else
		{	// state okay, insert
		_TRY_IO_BEGIN
		if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
			for (; 0 < _Pad; --_Pad)	// pad on left
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
					_State |= ios_base::badbit;
					break;
					}

		if (_State == ios_base::goodbit
			&& _Ostr.rdbuf()->sputn(_Val, _Count) != _Count)
			_State |= ios_base::badbit;

		if (_State == ios_base::goodbit)
			for (; 0 < _Pad; --_Pad)	// pad on right
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
					_State |= ios_base::badbit;
					break;
					}
		_Ostr.width(0);
		_CATCH_IO_(_Ostr)
		}

	_Ostr.setstate(_State);
	return (_Ostr);
	}

template<class _Elem,
	class _Traits> inline
	basic_ostream<_Elem, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<_Elem, _Traits>& _Ostr, _Elem _Ch)
	{	// insert a character
	typedef basic_ostream<_Elem, _Traits> _Myos;
	ios_base::iostate _State = ios_base::goodbit;
	const typename _Myos::sentry _Ok(_Ostr);

	if (_Ok)
		{	// state okay, insert
		streamsize _Pad = _Ostr.width() <= 1 ? 0 : _Ostr.width() - 1;

		_TRY_IO_BEGIN
		if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
			for (; _State == ios_base::goodbit && 0 < _Pad;
				--_Pad)	// pad on left
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
					_State |= ios_base::badbit;

		if (_State == ios_base::goodbit
			&& _Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ch)))
			_State |= ios_base::badbit;

		for (; _State == ios_base::goodbit && 0 < _Pad;
			--_Pad)	// pad on right
			if (_Traits::eq_int_type(_Traits::eof(),
				_Ostr.rdbuf()->sputc(_Ostr.fill())))
				_State |= ios_base::badbit;
		_CATCH_IO_(_Ostr)
		}

	_Ostr.width(0);
	_Ostr.setstate(_State);
	return (_Ostr);
	}

template<class _Traits> inline
	basic_ostream<char, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<char, _Traits>& _Ostr, const signed char *_Val)
	{	// insert a signed char NTBS
	return (_Ostr << (const char *)_Val);
	}

template<class _Traits> inline
	basic_ostream<char, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<char, _Traits>& _Ostr, signed char _Ch)
	{	// insert a signed char
	return (_Ostr << (char)_Ch);
	}

template<class _Traits> inline
	basic_ostream<char, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<char, _Traits>& _Ostr, const unsigned char *_Val)
	{	// insert an unsigned char NTBS
	return (_Ostr << (const char *)_Val);
	}

template<class _Traits> inline
	basic_ostream<char, _Traits>& __CLRCALL_OR_CDECL operator<<(
		basic_ostream<char, _Traits>& _Ostr, unsigned char _Ch)
	{	// insert an unsigned char
	return (_Ostr << (char)_Ch);
	}

		// MANIPULATORS
template<class _Elem,
	class _Traits> inline
	basic_ostream<_Elem, _Traits>&
		__CLRCALL_OR_CDECL endl(basic_ostream<_Elem, _Traits>& _Ostr)
	{	// insert newline and flush stream
	_Ostr.put(_Ostr.widen('\n'));
	_Ostr.flush();
	return (_Ostr);
	}

template<class _Elem,
	class _Traits> inline
	basic_ostream<_Elem, _Traits>&
		__CLRCALL_OR_CDECL ends(basic_ostream<_Elem, _Traits>& _Ostr)
	{	// insert null character
	_Ostr.put(_Elem());
	return (_Ostr);
	}

template<class _Elem,
	class _Traits> inline
	basic_ostream<_Elem, _Traits>&
		__CLRCALL_OR_CDECL flush(basic_ostream<_Elem, _Traits>& _Ostr)
	{	// flush stream
	_Ostr.flush();
	return (_Ostr);
	}

_CRTIMP2_PURE inline basic_ostream<char, char_traits<char> >&
	__CLRCALL_OR_CDECL endl(basic_ostream<char, char_traits<char> >& _Ostr)
	{	// insert newline and flush byte stream
	_Ostr.put('\n');
	_Ostr.flush();
	return (_Ostr);
	}

_CRTIMP2_PURE inline basic_ostream<wchar_t, char_traits<wchar_t> >&
	__CLRCALL_OR_CDECL endl(basic_ostream<wchar_t,
		char_traits<wchar_t> >& _Ostr)
	{	// insert newline and flush wide stream
	_Ostr.put('\n');
	_Ostr.flush();
	return (_Ostr);
	}


_CRTIMP2_PURE inline basic_ostream<char, char_traits<char> >&
	__CLRCALL_OR_CDECL ends(basic_ostream<char, char_traits<char> >& _Ostr)
	{	// insert null character into byte stream
	_Ostr.put('\0');
	return (_Ostr);
	}

_CRTIMP2_PURE inline basic_ostream<wchar_t, char_traits<wchar_t> >&
	__CLRCALL_OR_CDECL ends(basic_ostream<wchar_t,
		char_traits<wchar_t> >& _Ostr)
	{	// insert null character into wide stream
	_Ostr.put('\0');
	return (_Ostr);
	}


_CRTIMP2_PURE inline basic_ostream<char, char_traits<char> >&
	__CLRCALL_OR_CDECL flush(basic_ostream<char, char_traits<char> >& _Ostr)
	{	// flush byte stream
	_Ostr.flush();
	return (_Ostr);
	}

_CRTIMP2_PURE inline basic_ostream<wchar_t, char_traits<wchar_t> >&
	__CLRCALL_OR_CDECL flush(basic_ostream<wchar_t,
		char_traits<wchar_t> >& _Ostr)
	{	// flush wide stream
	_Ostr.flush();
	return (_Ostr);
	}


 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

 #endif /* _DLL_CPPLIB */

_STD_END

#ifdef _MSC_VER
 #pragma warning(default: 4390)
 #pragma warning(pop)
 #pragma pack(pop)
#endif  /* _MSC_VER */

#endif /* RC_INVOKED */
#endif /* _OSTREAM_ */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.02:0009 */

//#include <ostream>

#ifdef _MSC_VER
 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
#endif  /* _MSC_VER */

_STD_BEGIN

		// TEMPLATE CLASS basic_istream
template<class _Elem,
	class _Traits>
	class basic_istream
		: virtual public basic_ios<_Elem, _Traits>
	{	// control extractions from a stream buffer
public:
	typedef basic_istream<_Elem, _Traits> _Myt;
	typedef basic_ios<_Elem, _Traits> _Myios;
	typedef basic_streambuf<_Elem, _Traits> _Mysb;
	typedef istreambuf_iterator<_Elem, _Traits> _Iter;
	typedef ctype<_Elem> _Ctype;
	typedef num_get<_Elem, _Iter> _Nget;


	explicit __CLR_OR_THIS_CALL basic_istream(_Mysb *_Strbuf, bool _Isstd = false)
		: _Chcount(0)
		{	// construct from stream buffer pointer
		_Myios::init(_Strbuf, _Isstd);
		}

	__CLR_OR_THIS_CALL basic_istream(_Uninitialized)
		{	// construct uninitialized
		ios_base::_Addstd(this);
		}

	virtual __CLR_OR_THIS_CALL ~basic_istream()
		{	// destroy the object
		}

	typedef typename _Traits::int_type int_type;
	typedef typename _Traits::pos_type pos_type;
	typedef typename _Traits::off_type off_type;

		// TEMPLATE CLASS sentry
	class _Sentry_base
		{	// stores thread lock and reference to input stream
	public:
		__CLR_OR_THIS_CALL _Sentry_base(_Myt& _Istr)
			: _Myistr(_Istr)
			{	// lock the stream buffer, if there
			if (_Myistr.rdbuf() != 0)
				_Myistr.rdbuf()->_Lock();
			}

		__CLR_OR_THIS_CALL ~_Sentry_base()
			{	// destroy after unlocking
			if (_Myistr.rdbuf() != 0)
				_Myistr.rdbuf()->_Unlock();
			}

		_Myt& _Myistr;	// the input stream, for _Unlock call at destruction
		};

	class sentry
		: public _Sentry_base
		{	// stores thread lock and result of _Ipfx call
	public:
		explicit __CLR_OR_THIS_CALL sentry(_Myt& _Istr, bool _Noskip = false)
			: _Sentry_base(_Istr)
			{	// construct locking and calling _Ipfx
			_Ok = this->_Myistr._Ipfx(_Noskip);
			}

		__CLR_OR_THIS_CALL operator bool() const
			{	// test if _Ipfx succeeded
			return (_Ok);
			}

	private:
		__CLR_OR_THIS_CALL sentry(const sentry&);	// not defined
		sentry& __CLR_OR_THIS_CALL operator=(const sentry&);	// not defined

		bool _Ok;	// true if _Ipfx succeeded at construction
		};

	bool __CLR_OR_THIS_CALL _Ipfx(bool _Noskip = false)
		{	// test stream state and skip whitespace as needed
		if (ios_base::good())
			{	// state okay, flush tied stream and skip whitespace
			if (_Myios::tie() != 0)
				_Myios::tie()->flush();

			if (!_Noskip && ios_base::flags() & ios_base::skipws)
				{	// skip whitespace
				const _Ctype& _Ctype_fac = _USE(ios_base::getloc(), _Ctype);

				_TRY_IO_BEGIN
				int_type _Meta = _Myios::rdbuf()->sgetc();

				for (; ; _Meta = _Myios::rdbuf()->snextc())
					if (_Traits::eq_int_type(_Traits::eof(), _Meta))
						{	// end of file, quit
						_Myios::setstate(ios_base::eofbit);
						break;
						}
					else if (!_Ctype_fac.is(_Ctype::space,
						_Traits::to_char_type(_Meta)))
						break;	// not whitespace, quit
				_CATCH_IO_END
				}

			if (ios_base::good())
				return (true);
			}
		_Myios::setstate(ios_base::failbit);
		return (false);
		}

	bool __CLR_OR_THIS_CALL ipfx(bool _Noskip = false)
		{	// test stream state and skip whitespace as needed (retained)
		return _Ipfx(_Noskip);
		}

	void __CLR_OR_THIS_CALL isfx()
		{	// perform any wrapup (retained)
		}

#ifdef _M_CEE_PURE
	_Myt& __CLR_OR_THIS_CALL operator>>(_Myt& (__clrcall *_Pfn)(_Myt&))
		{	// call basic_istream manipulator
		_DEBUG_POINTER(_Pfn);
		return ((*_Pfn)(*this));
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(_Myios& (__clrcall *_Pfn)(_Myios&))
		{	// call basic_ios manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(_Myios *)this);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(ios_base& (__clrcall *_Pfn)(ios_base&))
		{	// call ios_base manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(ios_base *)this);
		return (*this);
		}
#endif

	_Myt& __CLR_OR_THIS_CALL operator>>(_Myt& (__cdecl *_Pfn)(_Myt&))
		{	// call basic_istream manipulator
		_DEBUG_POINTER(_Pfn);
		return ((*_Pfn)(*this));
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(_Myios& (__cdecl *_Pfn)(_Myios&))
		{	// call basic_ios manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(_Myios *)this);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(ios_base& (__cdecl *_Pfn)(ios_base&))
		{	// call ios_base manipulator
		_DEBUG_POINTER(_Pfn);
		(*_Pfn)(*(ios_base *)this);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(_Bool& _Val)
		{	// extract a boolean
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(short& _Val)
		{	// extract a short
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			long _Tmp = 0;
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Tmp);
			_CATCH_IO_END

			if (_State & ios_base::failbit
				|| _Tmp < SHRT_MIN || SHRT_MAX < _Tmp)
				_State |= ios_base::failbit;
			else
				_Val = (short)_Tmp;
			}

		_Myios::setstate(_State);
		return (*this);
		}

        /*  Note that if your stream is wchar_t, and you are not using native wchar_t
            Then this operation will be unavailable as there is an explicit
            specialisation further down this file that is designed to treat an
            unsigned short as a character.

            If you wish to read or write unsigned shorts to wchar_t streams, you should
            consider making wchar_t a native type by turning on /Zc:wchar_t
        */
	_Myt& __CLR_OR_THIS_CALL operator>>(unsigned short& _Val)
		{	// extract an unsigned short
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(int& _Val)
		{	// extract an int
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			long _Tmp = 0;
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Tmp);
			_CATCH_IO_END

			if (_State & ios_base::failbit
				|| _Tmp < INT_MIN || INT_MAX < _Tmp)
				_State |= ios_base::failbit;
			else
				_Val = _Tmp;
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(unsigned int& _Val)
		{	// extract an unsigned int
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(long& _Val)
		{	// extract a long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);
			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(unsigned long __w64& _Val)
		{	// extract an unsigned long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

 #ifdef _LONGLONG
	_Myt& __CLR_OR_THIS_CALL operator>>(_LONGLONG& _Val)
		{	// extract a long long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(_ULONGLONG& _Val)
		{	// extract an  unsigned long long
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}
 #endif /* _LONGLONG */

	_Myt& __CLR_OR_THIS_CALL operator>>(float& _Val)
		{	// extract a float
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(double& _Val)
		{	// extract a double
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);
		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(long double& _Val)
		{	// extract a long double
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);
			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(void *& _Val)
		{	// extract a void pointer
		ios_base::iostate _State = ios_base::goodbit;
		const sentry _Ok(*this);

		if (_Ok)
			{	// state okay, use facet to extract
			const _Nget& _Nget_fac = _USE(ios_base::getloc(), _Nget);

			_TRY_IO_BEGIN
			_Nget_fac.get(_Iter(_Myios::rdbuf()), _Iter(0),
				*this, _State, _Val);
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL operator>>(_Mysb *_Strbuf)
		{	// extract until end-of-file into a stream buffer
		ios_base::iostate _State = ios_base::goodbit;
		bool _Copied = false;
		const sentry _Ok(*this);

		if (_Ok && _Strbuf != 0)
			{	// state okay, extract characters
			_TRY_IO_BEGIN
			int_type _Meta = _Myios::rdbuf()->sgetc();

			for (; ; _Meta = _Myios::rdbuf()->snextc())
				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else
					{	// got a character, insert it into buffer
					_TRY_BEGIN
						if (_Traits::eq_int_type(_Traits::eof(),
							_Strbuf->sputc(_Traits::to_char_type(_Meta))))
							break;
					_CATCH_ALL
						break;
					_CATCH_END
					_Copied = true;
					}
			_CATCH_IO_END
			}

		_Myios::setstate(!_Copied ? _State | ios_base::failbit : _State);
		return (*this);
		}

	int_type __CLR_OR_THIS_CALL get()
		{	// extract a metacharacter
		int_type _Meta = 0;
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (!_Ok)
			_Meta = _Traits::eof();	// state not okay, return EOF
		else
			{	// state okay, extract a character
			_TRY_IO_BEGIN
			_Meta = _Myios::rdbuf()->sbumpc();

			if (_Traits::eq_int_type(_Traits::eof(), _Meta))
				_State |= ios_base::eofbit | ios_base::failbit;	// end of file
			else
				++_Chcount;	// got a character, count it
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (_Meta);
		}

	_Myt& __CLR_OR_THIS_CALL get(_Elem *_Str, streamsize _Count)
		{	// get up to _Count characters into NTCS
		return (get(_Str, _Count, _Myios::widen('\n')));
		}

	_Myt& __CLR_OR_THIS_CALL get(_Elem *_Str,
		streamsize _Count, _Elem _Delim)
		{	// get up to _Count characters into NTCS, stop before _Delim
		_DEBUG_POINTER(_Str);
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (_Ok && 0 < _Count)
			{	// state okay, extract characters
			_TRY_IO_BEGIN
			int_type _Meta = _Myios::rdbuf()->sgetc();

			for (; 0 < --_Count; _Meta = _Myios::rdbuf()->snextc())
				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else if (_Traits::to_char_type(_Meta) == _Delim)
					break;	// got a delimiter, quit
				else
					{	// got a character, add it to string
					*_Str++ = _Traits::to_char_type(_Meta);
					++_Chcount;
					}
			_CATCH_IO_END
			}

		_Myios::setstate(_Chcount == 0
			? _State | ios_base::failbit : _State);
		*_Str = _Elem();	// add terminating null character
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL get(_Elem& _Ch)
		{	// get a character
		int_type _Meta = get();
		if (!_Traits::eq_int_type(_Traits::eof(), _Meta))
			_Ch = _Traits::to_char_type(_Meta);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL get(_Mysb& _Strbuf)
		{	// extract up to newline and insert into stream buffer
		return (get(_Strbuf, _Myios::widen('\n')));
		}

	_Myt& __CLR_OR_THIS_CALL get(_Mysb& _Strbuf, _Elem _Delim)
		{	// extract up to delimiter and insert into stream buffer
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (_Ok)
			{	// state okay, use facet to extract
			_TRY_IO_BEGIN
			int_type _Meta = _Myios::rdbuf()->sgetc();

			for (; ; _Meta = _Myios::rdbuf()->snextc())
				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else
					{	// got a character, insert it into stream buffer
					_TRY_BEGIN
						_Elem _Ch = _Traits::to_char_type(_Meta);
						if (_Ch == _Delim
							|| _Traits::eq_int_type(_Traits::eof(),
								_Strbuf.sputc(_Ch)))
							break;
					_CATCH_ALL
						break;
					_CATCH_END
					++_Chcount;
					}
			_CATCH_IO_END
			}

		if (_Chcount == 0)
			_State |= ios_base::failbit;
		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL getline(_Elem *_Str, streamsize _Count)
		{	// get up to _Count characters into NTCS, discard newline
		return (getline(_Str, _Count, _Myios::widen('\n')));
		}

	_Myt& __CLR_OR_THIS_CALL getline(_Elem *_Str,
		streamsize _Count, _Elem _Delim)
		{	// get up to _Count characters into NTCS, discard _Delim
		_DEBUG_POINTER(_Str);
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (_Ok && 0 < _Count)
			{	// state okay, use facet to extract
			int_type _Metadelim = _Traits::to_int_type(_Delim);

			_TRY_IO_BEGIN
			int_type _Meta = _Myios::rdbuf()->sgetc();

			for (; ; _Meta = _Myios::rdbuf()->snextc())
				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else if (_Meta == _Metadelim)
					{	// got a delimiter, discard it and quit
					++_Chcount;
					_Myios::rdbuf()->sbumpc();
					break;
					}
				else if (--_Count <= 0)
					{	// buffer full, quit
					_State |= ios_base::failbit;
					break;
					}
				else
					{	// got a character, add it to string
					++_Chcount;
					*_Str++ = _Traits::to_char_type(_Meta);
					}
			_CATCH_IO_END
			}

		*_Str = _Elem();	// add terminating null character
		_Myios::setstate(_Chcount == 0 ? _State | ios_base::failbit : _State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL ignore(streamsize _Count = 1,
		int_type _Metadelim = _Traits::eof())
		{	// ignore up to _Count characters, discarding delimiter
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (_Ok && 0 < _Count)
			{	// state okay, use facet to extract
			_TRY_IO_BEGIN
			for (; ; )
				{	// get a metacharacter if more room in buffer
				int_type _Meta;
				if (_Count != INT_MAX && --_Count < 0)
					break;	// buffer full, quit
				else if (_Traits::eq_int_type(_Traits::eof(),
					_Meta = _Myios::rdbuf()->sbumpc()))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else
					{	// got a character, count it
					++_Chcount;
					if (_Meta == _Metadelim)
						break;	// got a delimiter, quit
					}
				}
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL _Read_s(_Elem *_Str, size_t _Str_size, streamsize _Count)
		{	// read up to _Count characters into buffer
		_DEBUG_POINTER(_Str);
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (_Ok)
			{	// state okay, use facet to extract
			_TRY_IO_BEGIN
			const streamsize _Num = _Myios::rdbuf()->_Sgetn_s(_Str, _Str_size, _Count);
			_Chcount += _Num;
			if (_Num != _Count)
				_State |= ios_base::eofbit | ios_base::failbit;	// short read
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL read(_Elem *_Str, streamsize _Count)
		{
		return _Read_s(_Str, (size_t)-1, _Count);
		}

	streamsize __CLR_OR_THIS_CALL _Readsome_s(_Elem *_Str, size_t _Str_size, streamsize _Count)
		{	// read up to _Count characters into buffer, without blocking
		_DEBUG_POINTER(_Str);
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);
		streamsize _Num;

		if (!_Ok)
			_State |= ios_base::failbit;	// no buffer, fail
		else if ((_Num = _Myios::rdbuf()->in_avail()) < 0)
			_State |= ios_base::eofbit;	// no characters available
		else if (0 < _Num)
			_Read_s(_Str, _Str_size, _Num < _Count ? _Num : _Count);	// read available

		_Myios::setstate(_State);
		return (gcount());
		}

	_SCL_INSECURE_DEPRECATE
	streamsize __CLR_OR_THIS_CALL readsome(_Elem *_Str, streamsize _Count)
		{
		return _Readsome_s(_Str, (size_t)-1, _Count);
		}

	int_type __CLR_OR_THIS_CALL peek()
		{	// return next character, unconsumed
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		int_type _Meta = 0;
		const sentry _Ok(*this, true);

		if (!_Ok)
			_Meta = _Traits::eof();	// state not okay, return EOF
		else
			{	// state okay, read a character
			_TRY_IO_BEGIN
			if (_Traits::eq_int_type(_Traits::eof(),
				_Meta = _Myios::rdbuf()->sgetc()))
				_State |= ios_base::eofbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (_Meta);
		}

	_Myt& __CLR_OR_THIS_CALL putback(_Elem _Ch)
		{	// put back a character
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (_Ok)
			{	// state okay, put character back
			_TRY_IO_BEGIN
			if (_Traits::eq_int_type(_Traits::eof(),
				_Myios::rdbuf()->sputbackc(_Ch)))
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL unget()
		{	// put back last read character
		ios_base::iostate _State = ios_base::goodbit;
		_Chcount = 0;
		const sentry _Ok(*this, true);

		if (_Ok)
			{	// state okay, use facet to extract
			_TRY_IO_BEGIN
			if (_Traits::eq_int_type(_Traits::eof(),
				_Myios::rdbuf()->sungetc()))
				_State |= ios_base::badbit;
			_CATCH_IO_END
			}

		_Myios::setstate(_State);
		return (*this);
		}

	streamsize __CLR_OR_THIS_CALL gcount() const
		{	// get count from last extraction
		return (_Chcount);
		}

	int __CLR_OR_THIS_CALL sync()
		{	// synchronize with input source
		ios_base::iostate _State = ios_base::goodbit;
		int _Ans;

		if (_Myios::rdbuf() == 0)
			_Ans = -1;	// no buffer, fail
		else if (_Myios::rdbuf()->pubsync() == -1)
			{	// stream buffer sync failed, fail
			_State |= ios_base::badbit;
			_Ans = -1;
			}
		else
			_Ans = 0;	// success

		_Myios::setstate(_State);
		return (_Ans);
		}

	_Myt& __CLR_OR_THIS_CALL seekg(pos_type _Pos)
		{	// set input stream position to _Pos
		if (!ios_base::fail()
			&& (off_type)_Myios::rdbuf()->pubseekpos(_Pos,
				ios_base::in) == _BADOFF)
			_Myios::setstate(ios_base::failbit);
		else
			_Myios::clear();	// clear eofbit if set
		return (*this);
		}

	_Myt& __CLR_OR_THIS_CALL seekg(off_type _Off, ios_base::seekdir _Way)
		{	// change input stream position by _Off, according to _Way
		if (!ios_base::fail()
			&& (off_type)_Myios::rdbuf()->pubseekoff(_Off, _Way,
				ios_base::in) == _BADOFF)
			_Myios::setstate(ios_base::failbit);
		else
			_Myios::clear();	// clear eofbit if set
		return (*this);
		}

	pos_type __CLR_OR_THIS_CALL tellg()
		{	// return input stream position
		if (!ios_base::fail())
			return (_Myios::rdbuf()->pubseekoff(0,
				ios_base::cur, ios_base::in));
		else
			return (pos_type(_BADOFF));
		}

private:
	streamsize _Chcount;	// the character count
	};

#ifndef _NATIVE_WCHAR_T_DEFINED
/*
This explicit template specialisation reads a single unicode character from the stream.

By default, the compiler treats wchar_t as if it were a typedef for unsigned short. This means
that we cannot distinguish between an unsigned short and a wchar_t in the library. To be most
consistent with previous practice, we add this explicit specialisation to ensure that a single
unsigned short is read and written as a character.

If you wish to read and write unsigned shorts as integers, we recommend you consider making
wchar_t a native type by using the /Zc:wchar_t compiler switch.
*/
template <> inline
	basic_istream<unsigned short, char_traits<unsigned short> >&__CLR_OR_THIS_CALL
	basic_istream<unsigned short, char_traits<unsigned short> >::operator>>(
		unsigned short& _Ch)
	{	// extract a character
	typedef basic_istream<unsigned short, char_traits<unsigned short> > _Myis;
	typedef char_traits<unsigned short> _Traits;
	_Myis::int_type _Meta;
	_Myis &_Istr=*this;
	ios_base::iostate _State = ios_base::goodbit;
	const _Myis::sentry _Ok(_Istr);

	if (_Ok)
		{	// state okay, extract characters
		_TRY_IO_BEGIN
		_Meta = _Istr.rdbuf()->sbumpc();
		if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			_State |= ios_base::eofbit | ios_base::failbit;	// end of file
		else
			_Ch = _Traits::to_char_type(_Meta);	// got a character
		_CATCH_IO_(_Istr)
		}

	_Istr.setstate(_State);
	return (_Istr);
	}
#endif

 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

template class _CRTIMP2_PURE basic_istream<char, char_traits<char> >;
template class _CRTIMP2_PURE basic_istream<wchar_t, char_traits<wchar_t> >;



 #endif /* _DLL_CPPLIB */

		// TEMPLATE CLASS basic_iostream
template<class _Elem,
	class _Traits>
	class basic_iostream
	: public basic_istream<_Elem, _Traits>,
		public basic_ostream<_Elem, _Traits>
	{	// control insertions and extractions from a stream buffer
public:
	typedef _Elem char_type;
	typedef _Traits traits_type;
	typedef typename _Traits::int_type int_type;
	typedef typename _Traits::pos_type pos_type;
	typedef typename _Traits::off_type off_type;

	explicit __CLR_OR_THIS_CALL basic_iostream(basic_streambuf<_Elem, _Traits> *_Strbuf)
		: basic_istream<_Elem, _Traits>(_Strbuf, false),
			basic_ostream<_Elem, _Traits>(_Noinit, false)
		{	// construct from stream buffer pointer
		}

	virtual __CLR_OR_THIS_CALL ~basic_iostream()
		{	// destroy the object
		}
	};

 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

template class _CRTIMP2_PURE basic_iostream<char, char_traits<char> >;
template class _CRTIMP2_PURE basic_iostream<wchar_t, char_traits<wchar_t> >;



 #endif /* _DLL_CPPLIB */

		// EXTRACTORS
template<class _Elem,
	class _Traits> inline
	basic_istream<_Elem, _Traits>& __CLRCALL_OR_CDECL operator>>(
		basic_istream<_Elem, _Traits>& _Istr, _Elem *_Str)
	{	// extract NTBS
	_DEBUG_POINTER(_Str);
	typedef basic_istream<_Elem, _Traits> _Myis;
	typedef ctype<_Elem> _Ctype;
	ios_base::iostate _State = ios_base::goodbit;
	_Elem *_Str0 = _Str;
	const typename _Myis::sentry _Ok(_Istr);

	if (_Ok)
		{	// state okay, extract characters
		const _Ctype& _Ctype_fac = _USE(_Istr.getloc(), _Ctype);

		_TRY_IO_BEGIN
		streamsize _Count = 0 < _Istr.width() ? _Istr.width() : INT_MAX;
		typename _Myis::int_type _Meta = _Istr.rdbuf()->sgetc();
		_Elem _Ch;
		for (; 0 < --_Count; _Meta = _Istr.rdbuf()->snextc())
			if (_Traits::eq_int_type(_Traits::eof(), _Meta))
				{	// end of file, quit
				_State |= ios_base::eofbit;
				break;
				}
			else if (_Ctype_fac.is(_Ctype::space,
				_Ch = _Traits::to_char_type(_Meta))
					|| _Ch == _Elem())
				break;	// whitespace or nul, quit
			else
				*_Str++ = _Traits::to_char_type(_Meta);	// add it to string
		_CATCH_IO_(_Istr)
		}

	*_Str = _Elem();	// add terminating null character
	_Istr.width(0);
	_Istr.setstate(_Str == _Str0 ? _State | ios_base::failbit : _State);
	return (_Istr);
	}

template<class _Elem,
	class _Traits> inline
	basic_istream<_Elem, _Traits>& __CLRCALL_OR_CDECL  operator>>(
		basic_istream<_Elem, _Traits>& _Istr, _Elem& _Ch)
	{	// extract a character
	typedef basic_istream<_Elem, _Traits> _Myis;
	typename _Myis::int_type _Meta;
	ios_base::iostate _State = ios_base::goodbit;
	const typename _Myis::sentry _Ok(_Istr);

	if (_Ok)
		{	// state okay, extract characters
		_TRY_IO_BEGIN
		_Meta = _Istr.rdbuf()->sbumpc();
		if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			_State |= ios_base::eofbit | ios_base::failbit;	// end of file
		else
			_Ch = _Traits::to_char_type(_Meta);	// got a character
		_CATCH_IO_(_Istr)
		}

	_Istr.setstate(_State);
	return (_Istr);
	}

#ifdef _MSC_VER
template<class _Traits> inline
	basic_istream<char, _Traits>& __CLRCALL_OR_CDECL  operator>>(
		basic_istream<char, _Traits>& _Istr, signed char *_Str)
	{	// extract a signed char NTBS
	return (_Istr >> (char *)_Str);
	}

template<class _Traits> inline
	basic_istream<char, _Traits>& __CLRCALL_OR_CDECL  operator>>(
		basic_istream<char, _Traits>& _Istr, signed char& _Ch)
	{	// extract a signed char
	return (_Istr >> (char&)_Ch);
	}

template<class _Traits> inline
	basic_istream<char, _Traits>& __CLRCALL_OR_CDECL  operator>>(
		basic_istream<char, _Traits>& _Istr, unsigned char *_Str)
	{	// extract an unsigned char NTBS
	return (_Istr >> (char *)_Str);
	}

template<class _Traits> inline
	basic_istream<char, _Traits>& __CLRCALL_OR_CDECL  operator>>(
		basic_istream<char, _Traits>& _Istr, unsigned char& _Ch)
	{	// extract an unsigned char
	return (_Istr >> (char&)_Ch);
	}

#endif

		// MANIPULATORS
template<class _Elem,
	class _Traits> inline
	basic_istream<_Elem, _Traits>&
		__CLRCALL_OR_CDECL ws(basic_istream<_Elem, _Traits>& _Istr)
	{	// consume whitespace
	typedef basic_istream<_Elem, _Traits> _Myis;
	typedef ctype<_Elem> _Ctype;

	if (!_Istr.eof())
		{	// not at eof, okay to construct sentry and skip
		ios_base::iostate _State = ios_base::goodbit;
		const typename _Myis::sentry _Ok(_Istr, true);

		if (_Ok)
			{	// state okay, extract characters
			const _Ctype& _Ctype_fac = _USE(_Istr.getloc(), _Ctype);

			_TRY_IO_BEGIN
			for (typename _Traits::int_type _Meta = _Istr.rdbuf()->sgetc(); ;
				_Meta = _Istr.rdbuf()->snextc())
				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else if (!_Ctype_fac.is(_Ctype::space,
					_Traits::to_char_type(_Meta)))
					break;	// not whitespace, quit
			_CATCH_IO_(_Istr)
			}

		_Istr.setstate(_State);
		}
	return (_Istr);
	}

_CRTIMP2_PURE inline basic_istream<char, char_traits<char> >&
	__CLRCALL_OR_CDECL ws(basic_istream<char, char_traits<char> >& _Istr)
	{	// consume whitespace
	typedef char _Elem;
	typedef char_traits<_Elem> _Traits;

	if (!_Istr.eof())
		{	// not at eof, okay to construct sentry and skip
		ios_base::iostate _State = ios_base::goodbit;
		const basic_istream<_Elem, _Traits>::sentry _Ok(_Istr, true);

		if (_Ok)
			{	// state okay, use facet to extract
			const ctype<_Elem>& _Ctype_fac =
				_USE(_Istr.getloc(), ctype<_Elem>);

			_TRY_IO_BEGIN
			for (_Traits::int_type _Meta = _Istr.rdbuf()->sgetc(); ;
				_Meta = _Istr.rdbuf()->snextc())
				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else if (!_Ctype_fac.is(ctype<_Elem>::space,
					_Traits::to_char_type(_Meta)))
					break;	// not whitespace, quit
			_CATCH_IO_(_Istr)
			}

		_Istr.setstate(_State);
		}
	return (_Istr);
	}

_CRTIMP2_PURE inline basic_istream<wchar_t, char_traits<wchar_t> >&
	__CLRCALL_OR_CDECL ws(basic_istream<wchar_t, char_traits<wchar_t> >& _Istr)
	{	// consume whitespace
	typedef wchar_t _Elem;
	typedef char_traits<_Elem> _Traits;

	if (!_Istr.eof())
		{	// not at eof, okay to construct sentry and skip
		ios_base::iostate _State = ios_base::goodbit;
		const basic_istream<_Elem, _Traits>::sentry _Ok(_Istr, true);

		if (_Ok)
			{	// state okay, use facet to extract
			const ctype<_Elem>& _Ctype_fac =
				_USE(_Istr.getloc(), ctype<_Elem>);

			_TRY_IO_BEGIN
			for (_Traits::int_type _Meta = _Istr.rdbuf()->sgetc(); ;
				_Meta = _Istr.rdbuf()->snextc())
				if (_Traits::eq_int_type(_Traits::eof(), _Meta))
					{	// end of file, quit
					_State |= ios_base::eofbit;
					break;
					}
				else if (!_Ctype_fac.is(ctype<_Elem>::space,
					_Traits::to_char_type(_Meta)))
					break;	// not whitespace, quit
			_CATCH_IO_(_Istr)
			}

		_Istr.setstate(_State);
		}
	return (_Istr);
	}



 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)
template _CRTIMP2_PURE basic_istream<char, char_traits<char> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<char, char_traits<char> >&, char *);
template _CRTIMP2_PURE basic_istream<char, char_traits<char> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<char, char_traits<char> >&, char&);
template _CRTIMP2_PURE basic_istream<char, char_traits<char> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<char, char_traits<char> >&, signed char *);
template _CRTIMP2_PURE basic_istream<char, char_traits<char> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<char, char_traits<char> >&, signed char&);
template _CRTIMP2_PURE basic_istream<char, char_traits<char> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<char, char_traits<char> >&, unsigned char *);
template _CRTIMP2_PURE basic_istream<char, char_traits<char> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<char, char_traits<char> >&, unsigned char&);
template _CRTIMP2_PURE basic_istream<wchar_t, char_traits<wchar_t> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<wchar_t, char_traits<wchar_t> >&, wchar_t *);
template _CRTIMP2_PURE basic_istream<wchar_t, char_traits<wchar_t> >& __CLRCALL_OR_CDECL
	operator>>(basic_istream<wchar_t, char_traits<wchar_t> >&, wchar_t&);



 #endif /* _DLL_CPPLIB */
_STD_END

#ifdef _MSC_VER
 #pragma warning(pop)
 #pragma pack(pop)
#endif  /* _MSC_VER */

#endif /* RC_INVOKED */
#endif /* _ISTREAM_ */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.02:0009 */

//#include <istream>

#ifdef _MSC_VER
 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
#endif  /* _MSC_VER */
_STD_BEGIN

		// OBJECTS
#if !defined(_M_CEE_PURE)
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 istream *_Ptr_cin;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream *_Ptr_cout;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream *_Ptr_cerr;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream *_Ptr_clog;
#endif // !defined(_M_CEE_PURE)

#if !defined(_M_CEE_PURE)
		// CLASS _Winit
class _CRTIMP2_PURE _Winit {
public:
	__thiscall _Winit();
	__thiscall ~_Winit();
private:
	__PURE_APPDOMAIN_GLOBAL static int _Init_cnt;
	};
#endif

		// WIDE OBJECTS
#if !defined(_M_CEE_PURE)
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wistream *_Ptr_wcin;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream *_Ptr_wcout;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream *_Ptr_wcerr;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream *_Ptr_wclog;
#endif // !defined(_M_CEE_PURE)

#ifdef _M_CEE_PURE
extern istream &cin;
extern ostream &cout;
extern ostream &cerr;
extern ostream &clog;

extern wistream &wcin;
extern wostream &wcout;
extern wostream &wcerr;
extern wostream &wclog;
#else
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 istream cin;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream cout;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream cerr;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream clog;

__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wistream wcin;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream wcout;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream wcerr;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream wclog;
#endif
_STD_END
#ifdef _MSC_VER
 #pragma warning(pop)
 #pragma pack(pop)
#endif  /* _MSC_VER */

#endif /* RC_INVOKED */
#endif /* _IOSTREAM_ */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.02:0009 */
/***
*stdio.h - definitions/declarations for standard I/O routines
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file defines the structures, values, macros, and functions
*       used by the level 2 I/O ("standard I/O") routines.
*       [ANSI/System V]
*
*       [Public]
*
****/

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_STDIO
#define _INC_STDIO

#include <crtdefs.h>
#ifdef  _MSC_VER
/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

#ifdef  __cplusplus
extern "C" {
#endif


/* Buffered I/O macros */

#define BUFSIZ  512


/*
 * Default number of supported streams. _NFILE is confusing and obsolete, but
 * supported anyway for backwards compatibility.
 */
#define _NFILE      _NSTREAM_

#define _NSTREAM_   512

/*
 * Number of entries in _iob[] (declared below). Note that _NSTREAM_ must be
 * greater than or equal to _IOB_ENTRIES.
 */
#define _IOB_ENTRIES 20

#define EOF     (-1)


#ifndef _FILE_DEFINED
struct _iobuf {
        char *_ptr;
        int   _cnt;
        char *_base;
        int   _flag;
        int   _file;
        int   _charbuf;
        int   _bufsiz;
        char *_tmpfname;
        };
typedef struct _iobuf FILE;
#define _FILE_DEFINED
#endif


/* Directory where temporary files may be created. */

#ifdef  _POSIX_
#define _P_tmpdir   "/"
#define _wP_tmpdir  L"/"
#else
#define _P_tmpdir   "\\"
#define _wP_tmpdir  L"\\"
#endif

/* L_tmpnam = length of string _P_tmpdir
 *            + 1 if _P_tmpdir does not end in "/" or "\", else 0
 *            + 12 (for the filename string)
 *            + 1 (for the null terminator)
 * L_tmpnam_s = length of string _P_tmpdir
 *            + 1 if _P_tmpdir does not end in "/" or "\", else 0
 *            + 16 (for the filename string)
 *            + 1 (for the null terminator)
 */
#define L_tmpnam   (sizeof(_P_tmpdir) + 12)
#if __STDC_WANT_SECURE_LIB__
#define L_tmpnam_s (sizeof(_P_tmpdir) + 16)
#endif

#ifdef  _POSIX_
#define L_ctermid   9
#define L_cuserid   32
#endif


/* Seek method constants */

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0


#define FILENAME_MAX    260
#define FOPEN_MAX       20
#define _SYS_OPEN       20
#define TMP_MAX         32767  /* SHRT_MAX */
#if __STDC_WANT_SECURE_LIB__
#define TMP_MAX_S       _TMP_MAX_S
#define _TMP_MAX_S      2147483647 /* INT_MAX */
#endif

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/* Declare _iob[] array */

#ifndef _STDIO_DEFINED
_CRTIMP FILE * __cdecl __iob_func(void);
#endif  /* _STDIO_DEFINED */


/* Define file position type */

#ifndef _FPOS_T_DEFINED
#undef _FPOSOFF

#if     defined (_POSIX_)
typedef long fpos_t;
#define _FPOSOFF(fp) ((long)(fp))
#else   /* _POSIX_ */

#if     !__STDC__
/* At this point we could switch both to long long, but we won't do that till next version to avoid any potential compat issues */
typedef __int64 fpos_t;
#define _FPOSOFF(fp) ((long)(fp))
#else
typedef long long fpos_t;
#define _FPOSOFF(fp) ((long)(fp))
#endif
#endif  /* _POSIX_ */

#define _FPOS_T_DEFINED
#endif

#ifndef _STDSTREAM_DEFINED
#define stdin  (&__iob_func()[0])
#define stdout (&__iob_func()[1])
#define stderr (&__iob_func()[2])
#define _STDSTREAM_DEFINED
#endif

#define _IOREAD         0x0001
#define _IOWRT          0x0002

#define _IOFBF          0x0000
#define _IOLBF          0x0040
#define _IONBF          0x0004

#define _IOMYBUF        0x0008
#define _IOEOF          0x0010
#define _IOERR          0x0020
#define _IOSTRG         0x0040
#define _IORW           0x0080
#ifdef  _POSIX_
#define _IOAPPEND       0x0200
#endif

/* constants used by _set_output_format */
#define _TWO_DIGIT_EXPONENT 0x1

/* Function prototypes */

#ifndef _STDIO_DEFINED

_Check_return_ _CRTIMP int __cdecl _filbuf(_Inout_ FILE * _File );
_Check_return_opt_ _CRTIMP int __cdecl _flsbuf(_In_ int _Ch, _Inout_ FILE * _File);

#ifdef  _POSIX_
_Check_return_ _CRTIMP FILE * __cdecl _fsopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode);
#else
_Check_return_ _CRTIMP FILE * __cdecl _fsopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode, _In_ int _ShFlag);
#endif

_CRTIMP void __cdecl clearerr(_Inout_ FILE * _File);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl clearerr_s(_Inout_ FILE * _File );
#endif
_Check_return_opt_ _CRTIMP int __cdecl fclose(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fcloseall(void);

#ifdef  _POSIX_
_Check_return_ _CRTIMP FILE * __cdecl fdopen( _In_ int _FileHandle, _In_z_ const char * _Mode);
#else
_Check_return_ _CRTIMP FILE * __cdecl _fdopen(_In_ int _FileHandle, _In_z_ const char * _Mode);
#endif

_Check_return_ _CRTIMP int __cdecl feof(_In_ FILE * _File);
_Check_return_ _CRTIMP int __cdecl ferror(_In_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl fflush(_Inout_opt_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl fgetc(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fgetchar(void);
_Check_return_opt_ _CRTIMP int __cdecl fgetpos(_Inout_ FILE * _File , _Out_ fpos_t * _Pos);
_Check_return_opt_ _CRTIMP char * __cdecl fgets(_Out_z_cap_(_MaxCount) char * _Buf, _In_ int _MaxCount, _Inout_ FILE * _File);

#ifdef  _POSIX_
_Check_return_ _CRTIMP int __cdecl fileno(_In_ FILE * _File);
#else
_Check_return_ _CRTIMP int __cdecl _fileno(_In_ FILE * _File);
#endif

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_tempnam")
#undef _tempnam
#endif

_Check_return_ _CRTIMP char * __cdecl _tempnam(_In_opt_z_ const char * _DirName, _In_opt_z_ const char * _FilePrefix);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_tempnam")
#endif

_Check_return_opt_ _CRTIMP int __cdecl _flushall(void);
_Check_return_ _CRT_INSECURE_DEPRECATE(fopen_s) _CRTIMP FILE * __cdecl fopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl fopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode);
#endif
_Check_return_opt_ _CRTIMP int __cdecl fprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl fputc(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fputchar(_In_ int _Ch);
_Check_return_opt_ _CRTIMP int __cdecl fputs(_In_z_ const char * _Str, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl fread(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP size_t __cdecl fread_s(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _DstSize, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
#endif
_Check_return_ _CRT_INSECURE_DEPRECATE(freopen_s) _CRTIMP FILE * __cdecl freopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode, _Inout_ FILE * _File);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl freopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode, _Inout_ FILE * _OldFile);
#endif
_Check_return_ _CRT_INSECURE_DEPRECATE(fscanf_s) _CRTIMP int __cdecl fscanf(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_fscanf_s_l) _CRTIMP int __cdecl _fscanf_l(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fscanf_s(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl _fscanf_s_l(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl fsetpos(_Inout_ FILE * _File, _In_ const fpos_t * _Pos);
_Check_return_opt_ _CRTIMP int __cdecl fseek(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP long __cdecl ftell(_Inout_ FILE * _File);

_Check_return_opt_ _CRTIMP int __cdecl _fseeki64(_Inout_ FILE * _File, _In_ __int64 _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP __int64 __cdecl _ftelli64(_Inout_ FILE * _File);

_Check_return_opt_ _CRTIMP size_t __cdecl fwrite(_In_count_x_(_Size*_Count) const void * _Str, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_ _CRTIMP int __cdecl getc(_Inout_ FILE * _File);
_Check_return_ _CRTIMP int __cdecl getchar(void);
_Check_return_ _CRTIMP int __cdecl _getmaxstdio(void);
#if __STDC_WANT_SECURE_LIB__
_CRTIMP char * __cdecl gets_s(_Out_z_cap_(_Size) char * _Buf, _In_ rsize_t _Size);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(char *, gets_s, char, _Buffer)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(char *, __RETURN_POLICY_SAME, _CRTIMP, gets, _Pre_notnull_ _Post_z_ _Out_z_cap_c_(((size_t)-1)), char, _Buffer)
_Check_return_ int __cdecl _getw(_Inout_ FILE * _File);
#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED
_CRTIMP void __cdecl perror(_In_opt_z_ const char * _ErrMsg);
#endif
_Check_return_opt_ _CRTIMP int __cdecl _pclose(_Inout_ FILE * _File);
_Check_return_ _CRTIMP FILE * __cdecl _popen(_In_z_ const char * _Command, _In_z_ const char * _Mode);
_Check_return_opt_ _CRTIMP int __cdecl printf(_In_z_ _Printf_format_string_ const char * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl printf_s(_In_z_ _Printf_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl putc(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl putchar(_In_ int _Ch);
_Check_return_opt_ _CRTIMP int __cdecl puts(_In_z_ const char * _Str);
_Check_return_opt_ _CRTIMP int __cdecl _putw(_In_ int _Word, _Inout_ FILE * _File);
#ifndef _CRT_DIRECTORY_DEFINED
#define _CRT_DIRECTORY_DEFINED
_Check_return_ _CRTIMP int __cdecl remove(_In_z_ const char * _Filename);
_Check_return_ _CRTIMP int __cdecl rename(_In_z_ const char * _OldFilename, _In_z_ const char * _NewFilename);
_Check_return_ _CRTIMP int __cdecl _unlink(_In_z_ const char * _Filename);
#if !__STDC__
_Check_return_ _CRT_NONSTDC_DEPRECATE(_unlink) _CRTIMP int __cdecl unlink(_In_z_ const char * _Filename);
#endif
#endif
_CRTIMP void __cdecl rewind(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _rmtmp(void);
_Check_return_ _CRT_INSECURE_DEPRECATE(scanf_s) _CRTIMP int __cdecl scanf(_In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_scanf_s_l) _CRTIMP int __cdecl _scanf_l(_In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl scanf_s(_In_z_ _Scanf_s_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _scanf_s_l(_In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_CRT_INSECURE_DEPRECATE(setvbuf) _CRTIMP void __cdecl setbuf(_Inout_ FILE * _File, _Inout_opt_cap_c_(BUFSIZ) _Post_count_c_(0) char * _Buffer);
_Check_return_opt_ _CRTIMP int __cdecl _setmaxstdio(_In_ int _Max);
_Check_return_opt_ _CRTIMP unsigned int __cdecl _set_output_format(_In_ unsigned int _Format);
_Check_return_opt_ _CRTIMP unsigned int __cdecl _get_output_format(void);
_Check_return_opt_ _CRTIMP int __cdecl setvbuf(_Inout_ FILE * _File, _Inout_opt_z_bytecap_(_Size) char * _Buf, _In_ int _Mode, _In_ size_t _Size);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snprintf_s(_Out_z_bytecap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, ...);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(int, _snprintf_s, _vsnprintf_s, char, _Dest, _In_ size_t, _MaxCount, _In_z_ _Printf_format_string_ const char *,_Format)
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl sprintf_s(_Out_z_bytecap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_z_ _Printf_format_string_ const char * _Format, ...);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(int, sprintf_s, vsprintf_s, char, _Dest, _In_z_ _Printf_format_string_ const char *, _Format)
_Check_return_ _CRTIMP int __cdecl _scprintf(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_ _CRT_INSECURE_DEPRECATE(sscanf_s) _CRTIMP int __cdecl sscanf(_In_z_ const char * _Src, _In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_sscanf_s_l) _CRTIMP int __cdecl _sscanf_l(_In_z_ const char * _Src, _In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl sscanf_s(_In_z_ const char * _Src, _In_z_ _Scanf_s_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _sscanf_s_l(_In_z_ const char * _Src, _In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snscanf_s) _CRTIMP int __cdecl _snscanf(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snscanf_s_l) _CRTIMP int __cdecl _snscanf_l(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snscanf_s(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snscanf_s_l(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRT_INSECURE_DEPRECATE(tmpfile_s) _CRTIMP FILE * __cdecl tmpfile(void);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl tmpfile_s(_Out_opt_ _Deref_post_valid_ FILE ** _File);
_Check_return_wat_ _CRTIMP errno_t __cdecl tmpnam_s(_Out_z_cap_(_Size) char * _Buf, _In_ rsize_t _Size);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, tmpnam_s, _Deref_post_z_ char, _Buf)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(char *, __RETURN_POLICY_DST, _CRTIMP, tmpnam, _Pre_maybenull_ _Post_z_, char, _Buffer)
_Check_return_opt_ _CRTIMP int __cdecl ungetc(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl vfprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vfprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#endif
_Check_return_opt_ _CRTIMP int __cdecl vprintf(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vprintf_s(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#endif
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(vsnprintf_s) _CRTIMP int __cdecl vsnprintf(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vsnprintf_s(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsnprintf_s(_Out_z_cap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(int, _vsnprintf_s, char, _Dest, _In_ size_t, _MaxCount, _In_z_ _Printf_format_string_ const char *, _Format, va_list, _Args)
#pragma warning(push)
#pragma warning(disable:4793)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(int, __RETURN_POLICY_SAME, _CRTIMP, _snprintf, _vsnprintf, _Pre_notnull_ _Post_maybez_ char, _Out_cap_(_Count) _Post_maybez_, char, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const char *, _Format)
#pragma warning(pop)
#if __STDC_WANT_SECURE_LIB__
_CRTIMP_ALTERNATIVE int __cdecl vsprintf_s(_Out_z_cap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(int, vsprintf_s, char, _Dest, _In_z_ _Printf_format_string_ const char *, _Format, va_list, _Args)
#pragma warning(push)
#pragma warning(disable:4793)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST(int, __RETURN_POLICY_SAME, _CRTIMP, sprintf, vsprintf, _Pre_notnull_ _Post_z_, char, _Dest, _In_z_ _Printf_format_string_ const char *, _Format)
#pragma warning(pop)
_Check_return_ _CRTIMP int __cdecl _vscprintf(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _snprintf_c(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vsnprintf_c(_Out_cap_(_MaxCount) char *_DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _fprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _printf_p(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _sprintf_p(_Out_z_cap_(_MaxCount) char * _Dst, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_p(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsprintf_p(_Out_z_cap_(_MaxCount) char * _Dst, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_ _CRTIMP int __cdecl _scprintf_p(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_ _CRTIMP int __cdecl _vscprintf_p(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_CRTIMP int __cdecl _set_printf_count_output(_In_ int _Value);
_CRTIMP int __cdecl _get_printf_count_output();

_Check_return_opt_ _CRTIMP int __cdecl _printf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _printf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _printf_s_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_s_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _fprintf_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fprintf_p_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fprintf_s_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_l(_Inout_ FILE * _File, _In_z_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_p_l(_Inout_ FILE * _File, _In_z_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_s_l(_Inout_ FILE * _File, _In_z_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_sprintf_s_l) _CRTIMP int __cdecl _sprintf_l(_Pre_notnull_ _Post_z_ char * _DstBuf, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _sprintf_p_l(_Out_z_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _sprintf_s_l(_Out_z_bytecap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_vsprintf_s_l) _CRTIMP int __cdecl _vsprintf_l(_Pre_notnull_ _Post_z_ char * _DstBuf, _In_z_ const char * _Format, _In_opt_ _locale_t, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsprintf_p_l(_Out_z_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char* _Format, _In_opt_ _locale_t _Locale,  va_list _ArgList);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsprintf_s_l(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _scprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _scprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vscprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vscprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snprintf_s_l) _CRTIMP int __cdecl _snprintf_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _snprintf_c_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snprintf_s_l(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_vsnprintf_s_l) _CRTIMP int __cdecl _vsnprintf_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsnprintf_c_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, const char *, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsnprintf_s_l(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char* _Format,_In_opt_ _locale_t _Locale, va_list _ArgList);

#ifndef _WSTDIO_DEFINED

/* wide function prototypes, also declared in wchar.h  */

#ifndef WEOF
#define WEOF (wint_t)(0xFFFF)
#endif

#ifdef  _POSIX_
_Check_return_ _CRTIMP FILE * __cdecl _wfsopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode);
#else
_Check_return_ _CRTIMP FILE * __cdecl _wfsopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode, _In_ int _ShFlag);
#endif

_Check_return_opt_ _CRTIMP wint_t __cdecl fgetwc(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _fgetwchar(void);
_Check_return_opt_ _CRTIMP wint_t __cdecl fputwc(_In_ wchar_t _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _fputwchar(_In_ wchar_t _Ch);
_Check_return_ _CRTIMP wint_t __cdecl getwc(_Inout_ FILE * _File);
_Check_return_ _CRTIMP wint_t __cdecl getwchar(void);
_Check_return_opt_ _CRTIMP wint_t __cdecl putwc(_In_ wchar_t _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl putwchar(_In_ wchar_t _Ch);
_Check_return_opt_ _CRTIMP wint_t __cdecl ungetwc(_In_ wint_t _Ch, _Inout_ FILE * _File);

_Check_return_opt_ _CRTIMP wchar_t * __cdecl fgetws(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ int _SizeInWords, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl fputws(_In_z_ const wchar_t * _Str, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wchar_t * __cdecl _getws_s(_Out_z_cap_(_SizeInWords) wchar_t * _Str, _In_ size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(wchar_t *, _getws_s, wchar_t, _String)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(wchar_t *, __RETURN_POLICY_SAME, _CRTIMP, _getws, _Pre_notnull_ _Post_z_, wchar_t, _String)
_Check_return_opt_ _CRTIMP int __cdecl _putws(_In_z_ const wchar_t * _Str);

_Check_return_opt_ _CRTIMP int __cdecl fwprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fwprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl wprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl wprintf_s(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_ _CRTIMP int __cdecl _scwprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl vfwprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vfwprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#endif
_Check_return_opt_ _CRTIMP int __cdecl vwprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vwprintf_s(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#endif

#if __STDC_WANT_SECURE_LIB__
_CRTIMP_ALTERNATIVE int __cdecl swprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(int, swprintf_s, vswprintf_s, wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
#if __STDC_WANT_SECURE_LIB__
_CRTIMP_ALTERNATIVE int __cdecl vswprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(int, vswprintf_s, wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format, va_list, _Args)

_Check_return_opt_ _CRTIMP int __cdecl _swprintf_c(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_c(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(int, _snwprintf_s, _vsnwprintf_s, wchar_t, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsnwprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(int, _vsnwprintf_s, wchar_t, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const wchar_t *, _Format, va_list, _Args)
#pragma warning(push)
#pragma warning(disable:4793)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(int, __RETURN_POLICY_SAME, _CRTIMP, _snwprintf, _vsnwprintf, _Pre_notnull_ _Post_maybez_ wchar_t, _Out_cap_(_Count) _Post_maybez_, wchar_t, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
#pragma warning(pop)

_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _wprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _swprintf_p(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_p(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_ _CRTIMP int __cdecl _scwprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_ _CRTIMP int __cdecl _vscwprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _wprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _wprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _wprintf_s_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_s_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_p_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_s_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_p_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_s_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _swprintf_c_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _swprintf_p_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _swprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_c_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_p_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vswprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_ _CRTIMP int __cdecl _scwprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRTIMP int __cdecl _scwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRTIMP int __cdecl _vscwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snwprintf_s_l) _CRTIMP int __cdecl _snwprintf_l(_Out_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_vsnwprintf_s_l) _CRTIMP int __cdecl _vsnwprintf_l(_Out_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsnwprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);


#ifndef _CRT_NON_CONFORMING_SWPRINTFS

#define _SWPRINTFS_DEPRECATED _CRT_DEPRECATE_TEXT("swprintf has been changed to conform with the ISO C standard, adding an extra character count parameter. To use traditional Microsoft swprintf, set _CRT_NON_CONFORMING_SWPRINTFS.")

#else

#define _SWPRINTFS_DEPRECATED

#endif /* ifndef _CRT_NON_CONFORMING_SWPRINTFS */

/* we could end up with a double deprecation, disable warnings 4141 and 4996 */
#pragma warning(push)
#pragma warning(disable:4141 4996 4793)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(int, __RETURN_POLICY_SAME, _SWPRINTFS_DEPRECATED _CRTIMP, _swprintf, _swprintf_s, _vswprintf, vswprintf_s, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(int, __RETURN_POLICY_SAME, _SWPRINTFS_DEPRECATED _CRTIMP, __swprintf_l, __vswprintf_l, _vswprintf_s_l, _Pre_notnull_ _Post_z_ wchar_t, , wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format, _locale_t, _Plocinfo)
#pragma warning(pop)

#if !defined(RC_INVOKED) && !defined(__midl)
#include <swprintf.inl>
#endif

#ifdef _CRT_NON_CONFORMING_SWPRINTFS
#ifndef __cplusplus
#define swprintf _swprintf
#define vswprintf _vswprintf
#define _swprintf_l __swprintf_l
#define _vswprintf_l __vswprintf_l
#endif
#endif

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wtempnam")
#undef _wtempnam
#endif

_Check_return_ _CRTIMP wchar_t * __cdecl _wtempnam(_In_opt_z_ const wchar_t * _Directory, _In_opt_z_ const wchar_t * _FilePrefix);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wtempnam")
#endif

_Check_return_ _CRTIMP int __cdecl _vscwprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_ _CRTIMP int __cdecl _vscwprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_ _CRT_INSECURE_DEPRECATE(fwscanf_s) _CRTIMP int __cdecl fwscanf(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_fwscanf_s_l) _CRTIMP int __cdecl _fwscanf_l(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fwscanf_s(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl _fwscanf_s_l(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRT_INSECURE_DEPRECATE(swscanf_s) _CRTIMP int __cdecl swscanf(_In_z_ const wchar_t * _Src, _In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_swscanf_s_l) _CRTIMP int __cdecl _swscanf_l(_In_z_ const wchar_t * _Src, _In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl swscanf_s(_In_z_ const wchar_t *_Src, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _swscanf_s_l(_In_z_ const wchar_t * _Src, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snwscanf_s) _CRTIMP int __cdecl _snwscanf(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snwscanf_s_l) _CRTIMP int __cdecl _snwscanf_l(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwscanf_s(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwscanf_s_l(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRT_INSECURE_DEPRECATE(wscanf_s) _CRTIMP int __cdecl wscanf(_In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_wscanf_s_l) _CRTIMP int __cdecl _wscanf_l(_In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl wscanf_s(_In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _wscanf_s_l(_In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(pop)

_Check_return_ _CRTIMP FILE * __cdecl _wfdopen(_In_ int _FileHandle , _In_z_ const wchar_t * _Mode);
_Check_return_ _CRT_INSECURE_DEPRECATE(_wfopen_s) _CRTIMP FILE * __cdecl _wfopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wfopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode);
_Check_return_ _CRT_INSECURE_DEPRECATE(_wfreopen_s) _CRTIMP FILE * __cdecl _wfreopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode, _Inout_ FILE * _OldFile);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wfreopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode, _Inout_ FILE * _OldFile);

#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED
_CRTIMP void __cdecl _wperror(_In_opt_z_ const wchar_t * _ErrMsg);
#endif
_Check_return_ _CRTIMP FILE * __cdecl _wpopen(_In_z_ const wchar_t *_Command, _In_z_ const wchar_t * _Mode);
_Check_return_ _CRTIMP int __cdecl _wremove(_In_z_ const wchar_t * _Filename);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wtmpnam_s(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _wtmpnam_s, _Deref_post_z_ wchar_t, _Buffer)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wtmpnam, _Pre_maybenull_ _Post_z_, wchar_t, _Buffer)

_Check_return_opt_ _CRTIMP wint_t __cdecl _fgetwc_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _fputwc_nolock(_In_ wchar_t _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _ungetwc_nolock(_In_ wint_t _Ch, _Inout_ FILE * _File);

#undef _CRT_GETPUTWCHAR_NOINLINE

#if !defined(__cplusplus) || defined(_M_CEE_PURE) || defined(_CRT_GETPUTWCHAR_NOINLINE)
#define getwchar()      fgetwc(stdin)
#define putwchar(_c)    fputwc((_c),stdout)
#else   /* __cplusplus */
inline wint_t __CRTDECL getwchar()
        {return (fgetwc(stdin)); }   /* stdin */
inline wint_t __CRTDECL putwchar(wchar_t _C)
        {return (fputwc(_C, stdout)); }       /* stdout */
#endif  /* __cplusplus */

#define getwc(_stm)             fgetwc(_stm)
#define putwc(_c,_stm)          fputwc(_c,_stm)
#define _putwc_nolock(_c,_stm)     _fputwc_nolock(_c,_stm)
#define _getwc_nolock(_stm)        _fgetwc_nolock(_stm)

#if defined(_CRT_DISABLE_PERFCRIT_LOCKS) && !defined(_DLL)
#define fgetwc(_stm)            _getwc_nolock(_stm)
#define fputwc(_c,_stm)         _putwc_nolock(_c,_stm)
#define ungetwc(_c,_stm)        _ungetwc_nolock(_c,_stm)
#endif

#define _WSTDIO_DEFINED
#endif  /* _WSTDIO_DEFINED */

#define _STDIO_DEFINED
#endif  /* _STDIO_DEFINED */


/* Macro definitions */

#if defined(_CRT_DISABLE_PERFCRIT_LOCKS) && !defined(_DLL)
#define feof(_stream)     ((_stream)->_flag & _IOEOF)
#define ferror(_stream)   ((_stream)->_flag & _IOERR)
#define _fileno(_stream)  ((_stream)->_file)
#define fgetc(_stream)     (--(_stream)->_cnt >= 0 \
                ? 0xff & *(_stream)->_ptr++ : _filbuf(_stream))
#define putc(_c,_stream)  (--(_stream)->_cnt >= 0 \
                ? 0xff & (*(_stream)->_ptr++ = (char)(_c)) :  _flsbuf((_c),(_stream)))
#define getc(_stream)    fgetc(_stream)
#define getchar()         getc(stdin)
#define putchar(_c)       putc((_c),stdout)
#endif


#define _fgetc_nolock(_stream)       (--(_stream)->_cnt >= 0 ? 0xff & *(_stream)->_ptr++ : _filbuf(_stream))
#define _fputc_nolock(_c,_stream)    (--(_stream)->_cnt >= 0 ? 0xff & (*(_stream)->_ptr++ = (char)(_c)) :  _flsbuf((_c),(_stream)))
#define _getc_nolock(_stream)       _fgetc_nolock(_stream)
#define _putc_nolock(_c, _stream)   _fputc_nolock(_c, _stream)
#define _getchar_nolock()           _getc_nolock(stdin)
#define _putchar_nolock(_c)         _putc_nolock((_c),stdout)
#define _getwchar_nolock()          _getwc_nolock(stdin)
#define _putwchar_nolock(_c)        _putwc_nolock((_c),stdout)

#ifdef _MT
_CRTIMP void __cdecl _lock_file(_Inout_ FILE * _File);
_CRTIMP void __cdecl _unlock_file(_Inout_ FILE * _File);
#else
#define _lock_file(c)
#define _unlock_file(c)
#endif


_Check_return_opt_ _CRTIMP int __cdecl _fclose_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fflush_nolock(_Inout_opt_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl _fread_nolock(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl _fread_nolock_s(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _DstSize, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fseek_nolock(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP long __cdecl _ftell_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fseeki64_nolock(_Inout_ FILE * _File, _In_ __int64 _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP __int64 __cdecl _ftelli64_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl _fwrite_nolock(_In_bytecount_x_(_Size*_Count) const void * _DstBuf, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _ungetc_nolock(_In_ int _Ch, _Inout_ FILE * _File);

#if defined(_CRT_DISABLE_PERFCRIT_LOCKS) && !defined(_DLL)
#define fclose(_stm)                                            _fclose_nolock(_stm)
#define fflush(_stm)                                            _fflush_nolock(_stm)
#define fread(_DstBuf, _ElementSize, _Count, _File)             _fread_nolock(_DstBuf, _ElementSize, _Count, _File)
#define fread_s(_DstBuf, _DstSize, _ElementSize, _Count, _File) _fread_nolock_s(_DstBuf, _DstSize, _ElementSize, _Count, _File)
#define fseek(_stm,_offset,_origin)                             _fseek_nolock(_stm,_offset,_origin)
#define ftell(_stm)                                             _ftell_nolock(_stm)
#define _fseeki64(_stm,_offset,_origin)                         _fseeki64_nolock(_stm,_offset,_origin)
#define _ftelli64(_stm)                                         _ftelli64_nolock(_stm)
#define fwrite(_buf,_siz,_cnt,_stm)                             _fwrite_nolock(_buf,_siz,_cnt,_stm)
#define ungetc(_c,_stm)                                         _ungetc_nolock(_c,_stm)
#endif

#if     !__STDC__ && !defined(_POSIX_)

/* Non-ANSI names for compatibility */

#define P_tmpdir  _P_tmpdir
#define SYS_OPEN  _SYS_OPEN

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("tempnam")
#undef tempnam
#endif

_CRT_NONSTDC_DEPRECATE(_tempnam) _CRTIMP char * __cdecl tempnam(_In_opt_z_ const char * _Directory, _In_opt_z_ const char * _FilePrefix);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("tempnam")
#endif

_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_fcloseall) _CRTIMP int __cdecl fcloseall(void);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_fdopen) _CRTIMP FILE * __cdecl fdopen(_In_ int _FileHandle, _In_z_ const char * _Format);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_fgetchar) _CRTIMP int __cdecl fgetchar(void);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_fileno) _CRTIMP int __cdecl fileno(_In_ FILE * _File);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_flushall) _CRTIMP int __cdecl flushall(void);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_fputchar) _CRTIMP int __cdecl fputchar(_In_ int _Ch);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_getw) _CRTIMP int __cdecl getw(_Inout_ FILE * _File);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_putw) _CRTIMP int __cdecl putw(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_rmtmp) _CRTIMP int __cdecl rmtmp(void);

#endif  /* __STDC__ */

#ifdef  __cplusplus
}
#endif

#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_STDIO */
/***
*stdlib.h - declarations/definitions for commonly used library functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This include file contains the function declarations for commonly
*       used library functions which either don't fit somewhere else, or,
*       cannot be declared in the normal place for other reasons.
*       [ANSI]
*
*       [Public]
*
****/

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_STDLIB
#define _INC_STDLIB

#include <crtdefs.h>
#include <limits.h>

#ifdef  _MSC_VER
/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

#ifdef  __cplusplus
extern "C" {
#endif

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/* Definition of the argument values for the exit() function */

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1


#ifndef _ONEXIT_T_DEFINED

#if !defined (_M_CEE_PURE)
typedef int (__cdecl * _onexit_t)(void);
#else
typedef int (__clrcall * _onexit_t)(void);
typedef _onexit_t _onexit_m_t;
#endif

#if defined (_M_CEE_MIXED)
typedef int (__clrcall * _onexit_m_t)(void);
#endif

#if     !__STDC__
/* Non-ANSI name for compatibility */
#define onexit_t _onexit_t
#endif

#define _ONEXIT_T_DEFINED
#endif


/* Data structure definitions for div and ldiv runtimes. */

#ifndef _DIV_T_DEFINED

typedef struct _div_t {
        int quot;
        int rem;
} div_t;

typedef struct _ldiv_t {
        long quot;
        long rem;
} ldiv_t;

#define _DIV_T_DEFINED
#endif

/*
 * structs used to fool the compiler into not generating floating point
 * instructions when copying and pushing [long] double values
 */

#ifndef _CRT_DOUBLE_DEC

#ifndef _LDSUPPORT

#pragma pack(4)
typedef struct {
    unsigned char ld[10];
} _LDOUBLE;
#pragma pack()

#define _PTR_LD(x) ((unsigned char  *)(&(x)->ld))

#else

/* push and pop long, which is #defined as __int64 by a spec2k test */
#pragma push_macro("long")
#undef long
typedef long double _LDOUBLE;
#pragma pop_macro("long")

#define _PTR_LD(x) ((unsigned char  *)(x))

#endif

typedef struct {
        double x;
} _CRT_DOUBLE;

typedef struct {
    float f;
} _CRT_FLOAT;

/* push and pop long, which is #defined as __int64 by a spec2k test */
#pragma push_macro("long")
#undef long

typedef struct {
        /*
         * Assume there is a long double type
         */
        long double x;
} _LONGDOUBLE;

#pragma pop_macro("long")

#pragma pack(4)
typedef struct {
    unsigned char ld12[12];
} _LDBL12;
#pragma pack()

#define _CRT_DOUBLE_DEC
#endif

/* Maximum value that can be returned by the rand function. */

#define RAND_MAX 0x7fff

/*
 * Maximum number of bytes in multi-byte character in the current locale
 * (also defined in ctype.h).
 */
#ifndef MB_CUR_MAX
#ifdef _MT
#define MB_CUR_MAX ___mb_cur_max_func()
#else
#define MB_CUR_MAX __mb_cur_max
#endif
#if !defined(_M_CEE_PURE)
_CRTIMP extern int __mb_cur_max;
#else
_CRTIMP int* __cdecl __p___mb_cur_max();
#define __mb_cur_max (*__p___mb_cur_max())
#endif /* !defined(_M_CEE_PURE) */
_CRTIMP int __cdecl ___mb_cur_max_func(void);
_CRTIMP int __cdecl ___mb_cur_max_l_func(_locale_t);
#endif  /* MB_CUR_MAX */

/* Minimum and maximum macros */

#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

/*
 * Sizes for buffers used by the _makepath() and _splitpath() functions.
 * note that the sizes include space for 0-terminator
 */
#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */

/*
 * Argument values for _set_error_mode().
 */
#define _OUT_TO_DEFAULT 0
#define _OUT_TO_STDERR  1
#define _OUT_TO_MSGBOX  2
#define _REPORT_ERRMODE 3

/*
 * Argument values for _set_abort_behavior().
 */
#define _WRITE_ABORT_MSG    0x1
#define _CALL_REPORTFAULT   0x2

/*
 * Sizes for buffers used by the getenv/putenv family of functions.
 */
#define _MAX_ENV 32767

#if !defined(_M_CEE_PURE)
/* a purecall handler procedure. Never returns normally */
typedef void (__cdecl *_purecall_handler)(void);

/* establishes a purecall handler for the process */
_CRTIMP _purecall_handler __cdecl _set_purecall_handler(_In_opt_ _purecall_handler _Handler);
_CRTIMP _purecall_handler __cdecl _get_purecall_handler();
#endif

#if defined(__cplusplus)
extern "C++"
{
#if defined(_M_CEE_PURE)
    typedef void (__clrcall *_purecall_handler)(void);
    typedef _purecall_handler _purecall_handler_m;
    _MRTIMP _purecall_handler __cdecl _set_purecall_handler(_In_opt_ _purecall_handler _Handler);
#endif

#if defined(_M_CEE_MIXED)
    typedef void (__clrcall *_purecall_handler_m)(void);

    _MRTIMP _purecall_handler_m __cdecl _set_purecall_handler(_In_opt_ _purecall_handler_m _Handler);

    _MRTIMP _purecall_handler __cdecl _set_purecall_handler(_In_ int _Handler); /* To disambiguate NULL/0 */
#endif
}
#endif

#if !defined(_M_CEE_PURE)
/* a invalid_arg handler procedure. */
typedef void (__cdecl *_invalid_parameter_handler)(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t);

/* establishes a invalid_arg handler for the process */
_CRTIMP _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(_In_opt_ _invalid_parameter_handler _Handler);
_CRTIMP _invalid_parameter_handler __cdecl _get_invalid_parameter_handler(void);
#endif

#if defined(__cplusplus)
extern "C++"
{
#if defined(_M_CEE_PURE)
    typedef void (__clrcall *_invalid_parameter_handler)(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t);
    typedef _invalid_parameter_handler _invalid_parameter_handler_m;
    _MRTIMP _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(_In_opt_ _invalid_parameter_handler _Handlerh);
#endif

#if defined(_M_CEE_MIXED)
    typedef void (__clrcall *_invalid_parameter_handler_m)(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t);
    _MRTIMP _invalid_parameter_handler_m __cdecl _set_invalid_parameter_handler(_In_opt_ _invalid_parameter_handler_m _Handlerh);

    _MRTIMP _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(_In_ int _Handler); /* To disambiguate NULL/0, only when we have both */
#endif
}
#endif

/* External variable declarations */
#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED
_CRTIMP extern int * __cdecl _errno(void);
#define errno   (*_errno())

errno_t __cdecl _set_errno(_In_ int _Value);
errno_t __cdecl _get_errno(_Out_ int * _Value);
#endif

_CRTIMP unsigned long * __cdecl __doserrno(void);
#define _doserrno   (*__doserrno())

errno_t __cdecl _set_doserrno(_In_ unsigned long _Value);
errno_t __cdecl _get_doserrno(_Out_ unsigned long * _Value);

/* you can't modify this, but it is non-const for backcompat */
_CRTIMP _CRT_INSECURE_DEPRECATE(strerror) char ** __cdecl __sys_errlist(void);
#define _sys_errlist (__sys_errlist())

_CRTIMP _CRT_INSECURE_DEPRECATE(strerror) int * __cdecl __sys_nerr(void);
#define _sys_nerr (*__sys_nerr())

#if     defined(_DLL) && defined(_M_IX86)

_CRTIMP int *          __cdecl __p___argc(void);
_CRTIMP char ***       __cdecl __p___argv(void);
_CRTIMP wchar_t ***    __cdecl __p___wargv(void);
_CRTIMP char ***       __cdecl __p__environ(void);
_CRTIMP wchar_t ***    __cdecl __p__wenviron(void);
_CRTIMP char **        __cdecl __p__pgmptr(void);
_CRTIMP wchar_t **     __cdecl __p__wpgmptr(void);


#endif  /* _M_IX86 && _DLL */

#if !defined(_M_CEE_PURE)
_CRTIMP extern int __argc;          /* count of cmd line args */
_CRTIMP extern char ** __argv;      /* pointer to table of cmd line args */
_CRTIMP extern wchar_t ** __wargv;  /* pointer to table of wide cmd line args */
#else
_CRTIMP int* __cdecl __p___argc();
_CRTIMP char*** __cdecl __p___argv();
_CRTIMP wchar_t*** __cdecl __p___wargv();
#define __argv (*__p___argv())
#define __argc (*__p___argc())
#define __wargv (*__p___wargv())
#endif

#if !defined(_M_CEE_PURE)
#ifdef  _POSIX_
extern char ** environ;             /* pointer to environment table */
#else
_CRTIMP extern char ** _environ;    /* pointer to environment table */
_CRTIMP extern wchar_t ** _wenviron;    /* pointer to wide environment table */
#endif  /* _POSIX_ */

_CRT_INSECURE_DEPRECATE_GLOBALS(_get_pgmptr) _CRTIMP extern char * _pgmptr;      /* points to the module (EXE) name */
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_wpgmptr) _CRTIMP extern wchar_t * _wpgmptr;  /* points to the module (EXE) wide name */


#else

_CRTIMP char*** __cdecl __p__environ();
_CRTIMP wchar_t*** __cdecl __p__wenviron();
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_pgmptr) _CRTIMP char** __cdecl __p__pgmptr();
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_wpgmptr) _CRTIMP wchar_t** __cdecl __p__wpgmptr();

#define _environ   (*__p__environ())
#define _wenviron  (*__p__wenviron())
#define _pgmptr    (*__p__pgmptr())
#define _wpgmptr   (*__p__wpgmptr())

#endif /* !defined(_M_CEE_PURE) */

errno_t __cdecl _get_pgmptr(_Deref_out_z_ char ** _Value);
errno_t __cdecl _get_wpgmptr(_Deref_out_z_ wchar_t ** _Value);


#if !defined(_M_CEE_PURE)
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_fmode) _CRTIMP extern int _fmode;          /* default file translation mode */
#else
_CRTIMP int* __cdecl __p__fmode();
#define _fmode (*__p__fmode())
#endif /* !defined(_M_CEE_PURE) */

_CRTIMP errno_t __cdecl _set_fmode(_In_ int _Mode);
_CRTIMP errno_t __cdecl _get_fmode(_Out_ int * _PMode);

/* _countof helper */
#if !defined(_countof)
#if !defined(__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
template <typename _CountofType, size_t _SizeOfArray>
char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) sizeof(*__countof_helper(_Array))
}
#endif
#endif

/* function prototypes */

#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED
_CRTIMP __declspec(noreturn) void __cdecl exit(_In_ int _Code);
_CRTIMP __declspec(noreturn) void __cdecl _exit(_In_ int _Code);
_CRTIMP void __cdecl abort(void);
#endif

_CRTIMP unsigned int __cdecl _set_abort_behavior(_In_ unsigned int _Flags, _In_ unsigned int _Mask);

#ifndef _CRT_ABS_DEFINED
#define _CRT_ABS_DEFINED
        int     __cdecl abs(_In_ int _X);
        long    __cdecl labs(_In_ long _X);
#endif

        __int64    __cdecl _abs64(__int64);
#if _MSC_VER >= 1400 && defined(_M_CEE)
#pragma warning (suppress: 4985)
        _Check_return_ int    __clrcall _atexit_m_appdomain(_In_opt_ void (__clrcall * _Func)(void));
#if defined(_M_CEE_MIXED)
#pragma warning (suppress: 4985)
        _Check_return_ int    __clrcall _atexit_m(_In_opt_ void (__clrcall * _Func)(void));
#else
        _Check_return_ inline int __clrcall _atexit_m(_In_opt_ void (__clrcall *_Function)(void))
#pragma warning (suppress: 4985)
        {
            return _atexit_m_appdomain(_Function);
        }
#endif
#endif
#if defined(_M_CEE_PURE)
        /* In pure mode, atexit is the same as atexit_m_appdomain */
extern "C++"
{
inline  int    __clrcall atexit
(
    void (__clrcall *_Function)(void)
)
{
    return _atexit_m_appdomain(_Function);
}
}
#else
        int    __cdecl atexit(void (__cdecl *)(void));
#endif
#ifndef _CRT_ATOF_DEFINED
#define _CRT_ATOF_DEFINED
_Check_return_ _CRTIMP double  __cdecl atof(_In_z_ const char *_String);
_Check_return_ _CRTIMP double  __cdecl _atof_l(_In_z_ const char *_String, _In_opt_ _locale_t _Locale);
#endif
_Check_return_ _CRTIMP _CRT_JIT_INTRINSIC int    __cdecl atoi(_In_z_ const char *_Str);
_Check_return_ _CRTIMP int    __cdecl _atoi_l(_In_z_ const char *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long   __cdecl atol(_In_z_ const char *_Str);
_Check_return_ _CRTIMP long   __cdecl _atol_l(_In_z_ const char *_Str, _In_opt_ _locale_t _Locale);
#ifndef _CRT_ALGO_DEFINED
#define _CRT_ALGO_DEFINED
#if __STDC_WANT_SECURE_LIB__
_Check_return_ _CRTIMP void * __cdecl bsearch_s(_In_ const void * _Key, _In_bytecount_x_(_NumOfElements * _SizeOfElements) const void * _Base,
        _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
_Check_return_ _CRTIMP void * __cdecl bsearch(_In_ const void * _Key, _In_bytecount_x_(_NumOfElements * _SizeOfElements) const void * _Base,
        _In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(const void *, const void *));

#if __STDC_WANT_SECURE_LIB__
_CRTIMP void __cdecl qsort_s(_Inout_bytecap_x_(_NumOfElements* _SizeOfElements) void * _Base,
        _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(void *, const void *, const void *), void *_Context);
#endif
_CRTIMP void __cdecl qsort(_Inout_bytecap_x_(_NumOfElements * _SizeOfElements) void * _Base,
	_In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(const void *, const void *));
#endif
        _Check_return_ unsigned short __cdecl _byteswap_ushort(_In_ unsigned short _Short);
        _Check_return_ unsigned long  __cdecl _byteswap_ulong (_In_ unsigned long _Long);
        _Check_return_ unsigned __int64 __cdecl _byteswap_uint64(_In_ unsigned __int64 _Int64);
_Check_return_ _CRTIMP div_t  __cdecl div(_In_ int _Numerator, _In_ int _Denominator);
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_dupenv_s) char * __cdecl getenv(_In_z_ const char * _VarName);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP errno_t __cdecl getenv_s(_Out_ size_t * _ReturnSize, _Out_z_cap_(_DstSize) char * _DstBuf, _In_ rsize_t _DstSize, _In_z_ const char * _VarName);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, getenv_s, _Out_ size_t *, _ReturnSize, char, _Dest, _In_z_ const char *, _VarName)
#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_dupenv_s")
#undef _dupenv_s
#endif

_Check_return_opt_ _CRTIMP errno_t __cdecl _dupenv_s(_Out_ _Deref_post_opt_z_cap_(*_PBufferSizeInBytes) char **_PBuffer, _Out_opt_ size_t * _PBufferSizeInBytes, _In_z_ const char * _VarName);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_dupenv_s")
#endif

_Check_return_opt_ _CRTIMP errno_t __cdecl _itoa_s(_In_ int _Value, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _itoa_s, _In_ int, _Value, char, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _itoa, _In_ int, _Value, _Pre_notnull_ _Post_z_, char, _Dest, _In_ int, _Radix)
_Check_return_opt_ _CRTIMP errno_t __cdecl _i64toa_s(_In_ __int64 _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_i64toa_s) char * __cdecl _i64toa(_In_ __int64 _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_Check_return_opt_ _CRTIMP errno_t __cdecl _ui64toa_s(_In_ unsigned __int64 _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_ui64toa_s) char * __cdecl _ui64toa(_In_ unsigned __int64 _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_Check_return_ _CRTIMP __int64 __cdecl _atoi64(_In_z_ const char * _String);
_Check_return_ _CRTIMP __int64 __cdecl _atoi64_l(_In_z_ const char * _String, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP __int64 __cdecl _strtoi64(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP __int64 __cdecl _strtoi64_l(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned __int64 __cdecl _strtoui64(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP unsigned __int64 __cdecl _strtoui64_l(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int  _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP ldiv_t __cdecl ldiv(_In_ long _Numerator, _In_ long _Denominator);
#ifdef __cplusplus
extern "C++"
{
    inline ldiv_t  div(_In_ long _A1, _In_ long _A2)
    {
        return ldiv(_A1, _A2);
    }
}
#endif
_Check_return_opt_ _CRTIMP errno_t __cdecl _ltoa_s(_In_ long _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ltoa_s, _In_ long, _Value, char, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _ltoa, _In_ long, _Value, _Pre_notnull_ _Post_z_, char, _Dest, _In_ int, _Radix)
_Check_return_ _CRTIMP int    __cdecl mblen(_In_opt_bytecount_(_MaxCount) _Pre_opt_z_ const char * _Ch, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int    __cdecl _mblen_l(_In_opt_bytecount_(_MaxCount) _Pre_opt_z_ const char * _Ch, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP size_t __cdecl _mbstrlen(_In_z_ const char * _Str);
_Check_return_ _CRTIMP size_t __cdecl _mbstrlen_l(_In_z_ const char *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP size_t __cdecl _mbstrnlen(_In_z_ const char *_Str, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP size_t __cdecl _mbstrnlen_l(_In_z_ const char *_Str, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_CRTIMP int    __cdecl mbtowc(_Pre_notnull_ _Post_z_ wchar_t * _DstCh, _In_opt_bytecount_(_SrcSizeInBytes) _Pre_opt_z_ const char * _SrcCh, _In_ size_t _SrcSizeInBytes);
_CRTIMP int    __cdecl _mbtowc_l(_Pre_notnull_ _Post_z_ wchar_t * _DstCh, _In_opt_bytecount_(_SrcSizeInBytes) _Pre_opt_z_ const char * _SrcCh, _In_ size_t _SrcSizeInBytes, _In_opt_ _locale_t _Locale);
_Check_return_opt_ _CRTIMP errno_t __cdecl mbstowcs_s(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_cap_post_count_(_SizeInWords, *_PtNumOfCharConverted) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_count_(_MaxCount) _Pre_z_ const char * _SrcBuf, _In_ size_t _MaxCount );
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(errno_t, mbstowcs_s, _Out_opt_ size_t *, _PtNumOfCharConverted, _Deref_post_z_ wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_CRTIMP, mbstowcs, _Out_opt_z_cap_(_MaxCount), wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount)

_Check_return_opt_ _CRTIMP errno_t __cdecl _mbstowcs_s_l(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_cap_post_count_(_SizeInWords, *_PtNumOfCharConverted) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_count_(_MaxCount) _Pre_z_ const char * _SrcBuf, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(errno_t, _mbstowcs_s_l, _Out_opt_ size_t *, _PtNumOfCharConverted, wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_CRTIMP, _mbstowcs_l, _mbstowcs_s_l, _Out_opt_z_cap_(_Size) wchar_t, _Out_z_cap_(_MaxCount), wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)

_Check_return_ _CRTIMP int    __cdecl rand(void);
#if defined(_CRT_RAND_S)
_CRTIMP errno_t __cdecl rand_s ( _Out_ unsigned int *_RandomValue);
#endif

_Check_return_opt_ _CRTIMP int    __cdecl _set_error_mode(_In_ int _Mode);

_CRTIMP void   __cdecl srand(_In_ unsigned int _Seed);
_Check_return_ _CRTIMP double __cdecl strtod(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr);
_Check_return_ _CRTIMP double __cdecl _strtod_l(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long   __cdecl strtol(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix );
_Check_return_ _CRTIMP long   __cdecl _strtol_l(_In_z_ const char *_Str, _Out_opt_ _Deref_post_z_ char **_EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned long __cdecl strtoul(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP unsigned long __cdecl _strtoul_l(const char * _Str, _Out_opt_ _Deref_post_z_ char **_EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
#ifndef _CRT_SYSTEM_DEFINED
#define _CRT_SYSTEM_DEFINED
_CRTIMP int __cdecl system(_In_opt_z_ const char * _Command);
#endif
_Check_return_opt_ _CRTIMP errno_t __cdecl _ultoa_s(_In_ unsigned long _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ultoa_s, _In_ unsigned long, _Value, char, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _ultoa, _In_ unsigned long, _Value, _Pre_notnull_ _Post_z_, char, _Dest, _In_ int, _Radix)
_CRTIMP _CRT_INSECURE_DEPRECATE(wctomb_s) int    __cdecl wctomb(_Out_opt_z_bytecap_c_(MB_LEN_MAX) char * _MbCh, _In_ wchar_t _WCh);
_CRTIMP _CRT_INSECURE_DEPRECATE(_wctomb_s_l) int    __cdecl _wctomb_l(_Pre_maybenull_ _Post_z_ char * _MbCh, _In_ wchar_t _WCh, _In_opt_ _locale_t _Locale);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl wctomb_s(_Out_opt_ int * _SizeConverted, _Out_opt_bytecap_post_bytecount_(_SizeInBytes, *_SizeConverted) char * _MbCh, _In_ rsize_t _SizeInBytes, _In_ wchar_t _WCh);
#endif
_Check_return_wat_ _CRTIMP errno_t __cdecl _wctomb_s_l(_Out_opt_ int * _SizeConverted, _Out_opt_z_bytecap_(_SizeInBytes) char * _MbCh, _In_ size_t _SizeInBytes, _In_ wchar_t _WCh, _In_opt_ _locale_t _Locale);
_Check_return_wat_ _CRTIMP errno_t __cdecl wcstombs_s(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_bytecap_post_bytecount_(_DstSizeInBytes, *_PtNumOfCharConverted) char * _Dst, _In_ size_t _DstSizeInBytes, _In_z_ const wchar_t * _Src, _In_ size_t _MaxCountInBytes);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(errno_t, wcstombs_s, _Out_opt_ size_t *, _PtNumOfCharConverted, _Out_opt_bytecap_(_Size) char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_CRTIMP, wcstombs, _Out_opt_z_cap_(_MaxCount), char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount)
_Check_return_wat_ _CRTIMP errno_t __cdecl _wcstombs_s_l(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_bytecap_post_bytecount_(_DstSizeInBytes, *_PtNumOfCharConverted) char * _Dst, _In_ size_t _DstSizeInBytes, _In_z_ const wchar_t * _Src, _In_ size_t _MaxCountInBytes, _In_opt_ _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(errno_t, _wcstombs_s_l, _Out_opt_ size_t *,_PtNumOfCharConverted, _Out_opt_cap_(_Size) char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_CRTIMP, _wcstombs_l, _wcstombs_s_l, _Out_opt_z_cap_(_Size) char, _Out_z_cap_(_MaxCount), char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)

#if _MSC_VER >= 1400 && defined(__cplusplus) && defined(_M_CEE)
/*
 * Managed search routines. Note __cplusplus, this is because we only support
 * managed C++.
 */
extern "C++"
{
#if __STDC_WANT_SECURE_LIB__
_Check_return_ void * __clrcall bsearch_s(_In_ const void * _Key, _In_bytecount_x_(_NumOfElements*_SizeOfElements) const void * _Base, _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElements,
        _In_ int (__clrcall * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
_Check_return_ void * __clrcall bsearch  (_In_ const void * _Key, _In_bytecount_x_(_NumOfElements*_SizeOfElements) const void * _Base, _In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__clrcall * _PtFuncCompare)(const void *, const void *));

#if __STDC_WANT_SECURE_LIB__
void __clrcall qsort_s(_Inout_bytecap_x_(_NumOfElements*_SizeOfElements) _Post_bytecount_x_(_NumOfElements*_SizeOfElements) void * _Base,
        _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElment,
        _In_ int (__clrcall * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
void __clrcall qsort(_Inout_bytecap_x_(_NumOfElements*_SizeOfElements) _Post_bytecount_x_(_NumOfElements*_SizeOfElements) void * _Base,
        _In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__clrcall * _PtFuncCompare)(const void *, const void *));

}
#endif

#ifndef _CRT_ALLOCATION_DEFINED
#define _CRT_ALLOCATION_DEFINED

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma push_macro("calloc")
#pragma push_macro("free")
#pragma push_macro("malloc")
#pragma push_macro("realloc")
#pragma push_macro("_recalloc")
#pragma push_macro("_aligned_free")
#pragma push_macro("_aligned_malloc")
#pragma push_macro("_aligned_offset_malloc")
#pragma push_macro("_aligned_realloc")
#pragma push_macro("_aligned_recalloc")
#pragma push_macro("_aligned_offset_realloc")
#pragma push_macro("_aligned_offset_recalloc")
#pragma push_macro("_aligned_msize")

#undef calloc
#undef free
#undef malloc
#undef realloc
#undef _recalloc
#undef _aligned_free
#undef _aligned_malloc
#undef _aligned_offset_malloc
#undef _aligned_realloc
#undef _aligned_recalloc
#undef _aligned_offset_realloc
#undef _aligned_offset_recalloc
#undef _aligned_msize

#endif
_Check_return_ _Ret_opt_bytecap_x_(_NumOfElements* _SizeOfElements) _CRTIMP _CRT_JIT_INTRINSIC _CRTNOALIAS _CRTRESTRICT    void * __cdecl calloc(_In_ size_t _NumOfElements, _In_ size_t _SizeOfElements);
_CRTIMP                     _CRTNOALIAS                                                                             void   __cdecl free(_Inout_opt_ void * _Memory);
_Check_return_ _Ret_opt_bytecap_(_Size) _CRTIMP _CRT_JIT_INTRINSIC _CRTNOALIAS _CRTRESTRICT                              void * __cdecl malloc(_In_ size_t _Size);
_Check_return_ _Ret_opt_bytecap_(_NewSize) _CRTIMP _CRTNOALIAS _CRTRESTRICT                           void * __cdecl realloc(_In_opt_ void * _Memory, _In_ size_t _NewSize);
_Check_return_ _Ret_opt_bytecap_x_(_Count*_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                       void * __cdecl _recalloc(_In_opt_ void * _Memory, _In_ size_t _Count, _In_ size_t _Size);
_CRTIMP                     _CRTNOALIAS                                                                             void   __cdecl _aligned_free(_Inout_opt_ void * _Memory);
_Check_return_ _Ret_opt_bytecap_(_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_malloc(_In_ size_t _Size, _In_ size_t _Alignment);
_Check_return_ _Ret_opt_bytecap_(_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_offset_malloc(_In_ size_t _Size, _In_ size_t _Alignment, _In_ size_t _Offset);
_Check_return_ _Ret_opt_bytecap_(_NewSize) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_realloc(_In_opt_ void * _Memory, _In_ size_t _NewSize, _In_ size_t _Alignment);
_Check_return_ _Ret_opt_bytecap_x_(_Count*_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                       void * __cdecl _aligned_recalloc(_In_opt_ void * _Memory, _In_ size_t _Count, _In_ size_t _Size, _In_ size_t _Alignment);
_Check_return_ _Ret_opt_bytecap_(_NewSize) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_offset_realloc(_In_opt_ void * _Memory, _In_ size_t _NewSize, _In_ size_t _Alignment, _In_ size_t _Offset);
_Check_return_ _Ret_opt_bytecap_x_(_Count*_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                       void * __cdecl _aligned_offset_recalloc(_In_opt_ void * _Memory, _In_ size_t _Count, _In_ size_t _Size, _In_ size_t _Alignment, _In_ size_t _Offset);
_Check_return_ _CRTIMP                                                  size_t __cdecl _aligned_msize(_In_ void * _Memory, _In_ size_t _Alignment, _In_ size_t _Offset);


#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma pop_macro("_aligned_msize")
#pragma pop_macro("_aligned_offset_recalloc")
#pragma pop_macro("_aligned_offset_realloc")
#pragma pop_macro("_aligned_recalloc")
#pragma pop_macro("_aligned_realloc")
#pragma pop_macro("_aligned_offset_malloc")
#pragma pop_macro("_aligned_malloc")
#pragma pop_macro("_aligned_free")
#pragma pop_macro("_recalloc")
#pragma pop_macro("realloc")
#pragma pop_macro("malloc")
#pragma pop_macro("free")
#pragma pop_macro("calloc")

#endif

#endif /*_CRT_ALLOCATION_DEFINED */

#ifndef _WSTDLIB_DEFINED

/* wide function prototypes, also declared in wchar.h  */

_Check_return_wat_ _CRTIMP errno_t __cdecl _itow_s (_In_ int _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _itow_s, _In_ int, _Value, wchar_t, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _itow, _In_ int, _Value, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_ int, _Radix)
_Check_return_wat_ _CRTIMP errno_t __cdecl _ltow_s (_In_ long _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ltow_s, _In_ long, _Value, wchar_t, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _ltow, _In_ long, _Value, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_ int, _Radix)
_Check_return_wat_ _CRTIMP errno_t __cdecl _ultow_s (_In_ unsigned long _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ultow_s, _In_ unsigned long, _Value, wchar_t, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _ultow, _In_ unsigned long, _Value, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_ int, _Radix)
_Check_return_ _CRTIMP double __cdecl wcstod(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr);
_Check_return_ _CRTIMP double __cdecl _wcstod_l(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long   __cdecl wcstol(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, int _Radix);
_Check_return_ _CRTIMP long   __cdecl _wcstol_l(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t **_EndPtr, int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned long __cdecl wcstoul(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, int _Radix);
_Check_return_ _CRTIMP unsigned long __cdecl _wcstoul_l(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t **_EndPtr, int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_wdupenv_s) wchar_t * __cdecl _wgetenv(_In_z_ const wchar_t * _VarName);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wgetenv_s(_Out_ size_t * _ReturnSize, _Out_z_cap_(_DstSizeInWords) wchar_t * _DstBuf, _In_ size_t _DstSizeInWords, _In_z_ const wchar_t * _VarName);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _wgetenv_s, _Out_ size_t *, _ReturnSize, wchar_t, _Dest, _In_z_ const wchar_t *, _VarName)

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wdupenv_s")
#undef _wdupenv_s
#endif

_Check_return_wat_ _CRTIMP errno_t __cdecl _wdupenv_s(_Out_ _Deref_post_opt_z_cap_(*_BufferSizeInWords) wchar_t **_Buffer, _Out_opt_ size_t *_BufferSizeInWords, _In_z_ const wchar_t *_VarName);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wdupenv_s")
#endif

#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED
_CRTIMP int __cdecl _wsystem(_In_opt_z_ const wchar_t * _Command);
#endif
_Check_return_ _CRTIMP double __cdecl _wtof(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP double __cdecl _wtof_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _wtoi(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP int __cdecl _wtoi_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long __cdecl _wtol(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP long __cdecl _wtol_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);

_Check_return_wat_ _CRTIMP errno_t __cdecl _i64tow_s(_In_ __int64 _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_i64tow_s) wchar_t * __cdecl _i64tow(_In_ __int64 _Val, _Pre_notnull_ _Post_z_ wchar_t * _DstBuf, _In_ int _Radix);
_Check_return_wat_ _CRTIMP errno_t __cdecl _ui64tow_s(_In_ unsigned __int64 _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_ui64tow_s) wchar_t * __cdecl _ui64tow(_In_ unsigned __int64 _Val, _Pre_notnull_ _Post_z_ wchar_t * _DstBuf, _In_ int _Radix);
_Check_return_ _CRTIMP __int64   __cdecl _wtoi64(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP __int64   __cdecl _wtoi64_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP __int64   __cdecl _wcstoi64(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP __int64   __cdecl _wcstoi64_l(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned __int64  __cdecl _wcstoui64(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP unsigned __int64  __cdecl _wcstoui64_l(_In_z_ const wchar_t *_Str , _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);

#define _WSTDLIB_DEFINED
#endif


#ifndef _POSIX_

/*
Buffer size required to be passed to _gcvt, fcvt and other fp conversion routines
*/
#define _CVTBUFSIZE (309+40) /* # of digits in max. dp value + slop */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma push_macro("_fullpath")
#undef _fullpath

#endif

_Check_return_ _CRTIMP char * __cdecl _fullpath(_Out_opt_z_cap_(_SizeInBytes) char * _FullPath, _In_z_ const char * _Path, _In_ size_t _SizeInBytes);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma pop_macro("_fullpath")

#endif

_Check_return_wat_ _CRTIMP errno_t __cdecl _ecvt_s(_Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ double _Val, _In_ int _NumOfDights, _Out_ int * _PtDec, _Out_ int * _PtSign);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _ecvt_s, char, _Dest, _In_ double, _Value, _In_ int, _NumOfDigits, _Out_ int *, _PtDec, _Out_ int *, _PtSign)
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_ecvt_s) char * __cdecl _ecvt(_In_ double _Val, _In_ int _NumOfDigits, _Out_ int * _PtDec, _Out_ int * _PtSign);
_Check_return_wat_ _CRTIMP errno_t __cdecl _fcvt_s(_Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ double _Val, _In_ int _NumOfDec, _Out_ int * _PtDec, _Out_ int * _PtSign);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _fcvt_s, char, _Dest, _In_ double, _Value, _In_ int, _NumOfDigits, _Out_ int *, _PtDec, _Out_ int *, _PtSign)
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_fcvt_s) char * __cdecl _fcvt(_In_ double _Val, _In_ int _NumOfDec, _Out_ int * _PtDec, _Out_ int * _PtSign);
_CRTIMP errno_t __cdecl _gcvt_s(_Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ double _Val, _In_ int _NumOfDigits);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _gcvt_s, char, _Dest, _In_ double, _Value, _In_ int, _NumOfDigits)
_CRTIMP _CRT_INSECURE_DEPRECATE(_gcvt_s) char * __cdecl _gcvt(_In_ double _Val, _In_ int _NumOfDigits, _Pre_notnull_ _Post_z_ char * _DstBuf);

_Check_return_ _CRTIMP int __cdecl _atodbl(_Out_ _CRT_DOUBLE * _Result, _In_z_ char * _Str);
_Check_return_ _CRTIMP int __cdecl _atoldbl(_Out_ _LDOUBLE * _Result, _In_z_ char * _Str);
_Check_return_ _CRTIMP int __cdecl _atoflt(_Out_ _CRT_FLOAT * _Result, _In_z_ char * _Str);
_Check_return_ _CRTIMP int __cdecl _atodbl_l(_Out_ _CRT_DOUBLE * _Result, _In_z_ char * _Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _atoldbl_l(_Out_ _LDOUBLE * _Result, _In_z_ char * _Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _atoflt_l(_Out_ _CRT_FLOAT * _Result, _In_z_ char * _Str, _In_opt_ _locale_t _Locale);
        _Check_return_ unsigned long __cdecl _lrotl(_In_ unsigned long _Val, _In_ int _Shift);
        _Check_return_ unsigned long __cdecl _lrotr(_In_ unsigned long _Val, _In_ int _Shift);
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t   __cdecl _makepath_s(_Out_z_cap_(_SizeInWords) char * _PathResult, _In_ size_t _SizeInWords, _In_opt_z_ const char * _Drive, _In_opt_z_ const char * _Dir, _In_opt_z_ const char * _Filename,
        _In_opt_z_ const char * _Ext);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _makepath_s, char, _Path, _In_opt_z_ const char *, _Drive, _In_opt_z_ const char *, _Dir, _In_opt_z_ const char *, _Filename, _In_opt_z_ const char *, _Ext)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(void, __RETURN_POLICY_VOID, _CRTIMP, _makepath, _Pre_notnull_ _Post_z_, char, _Path, _In_opt_z_ const char *, _Drive, _In_opt_z_ const char *, _Dir, _In_opt_z_ const char *, _Filename, _In_opt_z_ const char *, _Ext)

#if _MSC_VER >= 1400 && defined(_M_CEE)
		_onexit_m_t    __clrcall _onexit_m_appdomain(_onexit_m_t _Function);
	#if defined(_M_CEE_MIXED)
		_onexit_m_t    __clrcall _onexit_m(_onexit_m_t _Function);
	#else
		inline _onexit_m_t    __clrcall _onexit_m(_onexit_t _Function)
		{
			return _onexit_m_appdomain(_Function);
		}
	#endif

#endif
#if defined(_M_CEE_PURE)
        /* In pure mode, _onexit is the same as _onexit_m_appdomain */
extern "C++"
{
inline  _onexit_t    __clrcall _onexit
(
    _onexit_t _Function
)
{
    return _onexit_m_appdomain(_Function);
}
}
#else
        _onexit_t __cdecl _onexit(_In_opt_ _onexit_t _Func);
#endif

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED
_CRTIMP void __cdecl perror(_In_opt_z_ const char * _ErrMsg);
#endif

#pragma warning (push)
#pragma warning (disable:6540) // the functions below have declspecs in their declarations in the windows headers, causing PREfast to fire 6540 here
_Check_return_ _CRTIMP int    __cdecl _putenv(_In_z_ const char * _EnvString);
_Check_return_wat_ _CRTIMP errno_t __cdecl _putenv_s(_In_z_ const char * _Name, _In_z_ const char * _Value);
        _Check_return_ unsigned int __cdecl _rotl(_In_ unsigned int _Val, _In_ int _Shift);
        _Check_return_ unsigned __int64 __cdecl _rotl64(_In_ unsigned __int64 _Val, _In_ int _Shift);
        _Check_return_ unsigned int __cdecl _rotr(_In_ unsigned int _Val, _In_ int _Shift);
        _Check_return_ unsigned __int64 __cdecl _rotr64(_In_ unsigned __int64 _Val, _In_ int _Shift);
#pragma warning (pop)

_CRTIMP errno_t __cdecl _searchenv_s(_In_z_ const char * _Filename, _In_z_ const char * _EnvVar, _Out_z_cap_(_SizeInBytes) char * _ResultPath, _In_ size_t _SizeInBytes);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(errno_t, _searchenv_s, _In_z_ const char *, _Filename, _In_z_ const char *, _EnvVar, char, _ResultPath)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(void, __RETURN_POLICY_VOID, _CRTIMP, _searchenv, _In_z_ const char *, _Filename, _In_z_ const char *, _EnvVar, _Pre_notnull_ _Post_z_, char, _ResultPath)

_CRT_INSECURE_DEPRECATE(_splitpath_s) _CRTIMP void   __cdecl _splitpath(_In_z_ const char * _FullPath, _Pre_maybenull_ _Post_z_ char * _Drive, _Pre_maybenull_ _Post_z_ char * _Dir, _Pre_maybenull_ _Post_z_ char * _Filename, _Pre_maybenull_ _Post_z_ char * _Ext);
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t  __cdecl _splitpath_s(_In_z_ const char * _FullPath,
		_Out_opt_z_cap_(_DriveSize) char * _Drive, _In_ size_t _DriveSize,
		_Out_opt_z_cap_(_DirSize) char * _Dir, _In_ size_t _DirSize,
		_Out_opt_z_cap_(_FilenameSize) char * _Filename, _In_ size_t _FilenameSize,
		_Out_opt_z_cap_(_ExtSize) char * _Ext, _In_ size_t _ExtSize);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(errno_t, _splitpath_s,  char, _Dest)

_CRTIMP void   __cdecl _swab(_Inout_cap_(_SizeInBytes) _Post_count_(_SizeInBytes) char * _Buf1, _Inout_cap_(_SizeInBytes) _Post_count_(_SizeInBytes) char * _Buf2, int _SizeInBytes);

#ifndef _WSTDLIBP_DEFINED

/* wide function prototypes, also declared in wchar.h  */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wfullpath")
#undef _wfullpath
#endif

_Check_return_ _CRTIMP wchar_t * __cdecl _wfullpath(_Out_opt_z_cap_(_SizeInWords) wchar_t * _FullPath, _In_z_ const wchar_t * _Path, _In_ size_t _SizeInWords);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wfullpath")
#endif

_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl _wmakepath_s(_Out_z_cap_(_SIZE) wchar_t * _PathResult, _In_ size_t _SIZE, _In_opt_z_ const wchar_t * _Drive, _In_opt_z_ const wchar_t * _Dir, _In_opt_z_ const wchar_t * _Filename,
        _In_opt_z_ const wchar_t * _Ext);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _wmakepath_s, wchar_t, _ResultPath, _In_opt_z_ const wchar_t *, _Drive, _In_opt_z_ const wchar_t *, _Dir, _In_opt_z_ const wchar_t *, _Filename, _In_opt_z_ const wchar_t *, _Ext)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(void, __RETURN_POLICY_VOID, _CRTIMP, _wmakepath, _Pre_notnull_ _Post_z_, wchar_t, _ResultPath, _In_opt_z_ const wchar_t *, _Drive, _In_opt_z_ const wchar_t *, _Dir, _In_opt_z_ const wchar_t *, _Filename, _In_opt_z_ const wchar_t *, _Ext)
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED
_CRTIMP void __cdecl _wperror(_In_opt_z_ const wchar_t * _ErrMsg);
#endif
_Check_return_ _CRTIMP int    __cdecl _wputenv(_In_z_ const wchar_t * _EnvString);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wputenv_s(_In_z_ const wchar_t * _Name, _In_z_ const wchar_t * _Value);
_CRTIMP errno_t __cdecl _wsearchenv_s(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _EnvVar, _Out_z_cap_(_SizeInWords) wchar_t * _ResultPath, _In_ size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(errno_t, _wsearchenv_s, _In_z_ const wchar_t *, _Filename, _In_z_ const wchar_t *, _EnvVar, wchar_t, _ResultPath)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(void, __RETURN_POLICY_VOID, _CRTIMP, _wsearchenv, _In_z_ const wchar_t *, _Filename, _In_z_ const wchar_t *, _EnvVar, _Pre_notnull_ _Post_z_, wchar_t, _ResultPath)
_CRT_INSECURE_DEPRECATE(_wsplitpath_s) _CRTIMP void   __cdecl _wsplitpath(_In_z_ const wchar_t * _FullPath, _Pre_maybenull_ _Post_z_ wchar_t * _Drive, _Pre_maybenull_ _Post_z_ wchar_t * _Dir, _Pre_maybenull_ _Post_z_ wchar_t * _Filename, _Pre_maybenull_ _Post_z_ wchar_t * _Ext);
_CRTIMP_ALTERNATIVE errno_t __cdecl _wsplitpath_s(_In_z_ const wchar_t * _FullPath,
		_Out_opt_z_cap_(_DriveSize) wchar_t * _Drive, _In_ size_t _DriveSize,
		_Out_opt_z_cap_(_DirSize) wchar_t * _Dir, _In_ size_t _DirSize,
		_Out_opt_z_cap_(_FilenameSize) wchar_t * _Filename, _In_ size_t _FilenameSize,
		_Out_opt_z_cap_(_ExtSize) wchar_t * _Ext, _In_ size_t _ExtSize);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(errno_t, _wsplitpath_s, wchar_t, _Path)

#define _WSTDLIBP_DEFINED
#endif

/* The Win32 API SetErrorMode, Beep and Sleep should be used instead. */
_CRT_OBSOLETE(SetErrorMode) _CRTIMP void __cdecl _seterrormode(_In_ int _Mode);
_CRT_OBSOLETE(Beep) _CRTIMP void __cdecl _beep(_In_ unsigned _Frequency, _In_ unsigned _Duration);
_CRT_OBSOLETE(Sleep) _CRTIMP void __cdecl _sleep(_In_ unsigned long _Duration);

#endif  /* _POSIX_ */

#if     !__STDC__

#ifndef _POSIX_

/* Non-ANSI names for compatibility */

#ifndef __cplusplus
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#define sys_errlist _sys_errlist
#define sys_nerr    _sys_nerr
#define environ     _environ

#pragma warning(push)
#pragma warning(disable: 4141) /* Using deprecated twice */
_Check_return_ _CRT_NONSTDC_DEPRECATE(_ecvt) _CRT_INSECURE_DEPRECATE(_ecvt_s) _CRTIMP char * __cdecl ecvt(_In_ double _Val, _In_ int _NumOfDigits, _Out_ int * _PtDec, _Out_ int * _PtSign);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_fcvt) _CRT_INSECURE_DEPRECATE(_fcvt_s) _CRTIMP char * __cdecl fcvt(_In_ double _Val, _In_ int _NumOfDec, _Out_ int * _PtDec, _Out_ int * _PtSign);
_CRT_NONSTDC_DEPRECATE(_gcvt) _CRT_INSECURE_DEPRECATE(_fcvt_s)		_CRTIMP char * __cdecl gcvt(_In_ double _Val, _In_ int _NumOfDigits, _Pre_notnull_ _Post_z_ char * _DstBuf);
_CRT_NONSTDC_DEPRECATE(_itoa) _CRT_INSECURE_DEPRECATE(_itoa_s)		_CRTIMP char * __cdecl itoa(_In_ int _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_CRT_NONSTDC_DEPRECATE(_ltoa) _CRT_INSECURE_DEPRECATE(_ltoa_s)		_CRTIMP char * __cdecl ltoa(_In_ long _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_putenv) _CRTIMP int    __cdecl putenv(_In_z_ const char * _EnvString);
_CRT_NONSTDC_DEPRECATE(_swab)										_CRTIMP void   __cdecl swab(_Inout_z_bytecap_(_SizeInBytes) char * _Buf1,_Inout_z_bytecap_(_SizeInBytes) char * _Buf2, _In_ int _SizeInBytes);
_CRT_NONSTDC_DEPRECATE(_ultoa) _CRT_INSECURE_DEPRECATE(_ultoa_s)	_CRTIMP char * __cdecl ultoa(_In_ unsigned long _Val, _Pre_notnull_ _Post_z_ char * _Dstbuf, _In_ int _Radix);
#pragma warning(pop)
onexit_t __cdecl onexit(_In_opt_ onexit_t _Func);

#endif  /* _POSIX_ */

#endif  /* __STDC__ */

#ifdef  __cplusplus
}

#endif

#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_STDLIB */
/***
*conio.h - console and port I/O declarations
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This include file contains the function declarations for
*       the MS C V2.03 compatible console I/O routines.
*
*       [Public]
*
****/

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_CONIO
#define _INC_CONIO

#include <crtdefs.h>
#ifdef __cplusplus
extern "C" {
#endif

/* Function prototypes */

_Check_return_wat_ _CRTIMP errno_t __cdecl _cgets_s(_Out_z_cap_(_Size)                char * _Buffer, size_t _Size, _Out_ size_t * _SizeRead);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _cgets_s, _Deref_post_count_(*_Buffer) char, _Buffer, _Out_ size_t *, _Size)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(char *, _CRTIMP, _cgets, _Pre_notnull_ _Post_z_, char, _Buffer)
_Check_return_opt_ _CRTIMP int __cdecl _cprintf(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cprintf_s(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cputs(_In_z_ const char * _Str);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_cscanf_s) _CRTIMP int __cdecl _cscanf(_In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_cscanf_s_l) _CRTIMP int __cdecl _cscanf_l(_In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cscanf_s(_In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cscanf_s_l(_In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRTIMP int __cdecl _getch(void);
_Check_return_ _CRTIMP int __cdecl _getche(void);
_Check_return_opt_ _CRTIMP int __cdecl _vcprintf(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vcprintf_s(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _cprintf_p(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vcprintf_p(_In_z_ const char * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _cprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cprintf_s_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vcprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vcprintf_s_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _cprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vcprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

#ifdef  _M_IX86
int __cdecl _inp(unsigned short);
unsigned short __cdecl _inpw(unsigned short);
unsigned long __cdecl _inpd(unsigned short);
#endif  /* _M_IX86 */
_CRTIMP int __cdecl _kbhit(void);
#ifdef  _M_IX86
int __cdecl _outp(unsigned short, int);
unsigned short __cdecl _outpw(unsigned short, unsigned short);
unsigned long __cdecl _outpd(unsigned short, unsigned long);
#endif  /* _M_IX86 */
_CRTIMP int __cdecl _putch(_In_ int _Ch);
_CRTIMP int __cdecl _ungetch(_In_ int _Ch);

_Check_return_ _CRTIMP int __cdecl _getch_nolock(void);
_Check_return_ _CRTIMP int __cdecl _getche_nolock(void);
_CRTIMP int __cdecl _putch_nolock(_In_ int _Ch);
_CRTIMP int __cdecl _ungetch_nolock(_In_ int _Ch);

#if !defined(_MT)
#define _getch()                _getch_nolock()
#define _getche()               _getche_nolock()
#define _putch(c)               _putch_nolock(c)
#define _ungetch(c)             _ungetch_nolock(c)
#endif


#ifndef _WCONIO_DEFINED

/* wide function prototypes, also declared in wchar.h */

#ifndef WEOF
#define WEOF (wint_t)(0xFFFF)
#endif

_Check_return_wat_ _CRTIMP errno_t __cdecl _cgetws_s(_Out_cap_post_count_(_SizeInWords, *_SizeRead) wchar_t * _Buffer, size_t _SizeInWords, _Out_ size_t * _SizeRead);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _cgetws_s, _Deref_post_count_(*_Buffer) wchar_t, _Buffer, size_t *, _Size)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(wchar_t *, _CRTIMP, _cgetws, _Pre_notnull_ _Post_z_, wchar_t, _Buffer)
_Check_return_ _CRTIMP wint_t __cdecl _getwch(void);
_Check_return_ _CRTIMP wint_t __cdecl _getwche(void);
_Check_return_ _CRTIMP wint_t __cdecl _putwch(wchar_t _WCh);
_Check_return_ _CRTIMP wint_t __cdecl _ungetwch(wint_t _WCh);
_Check_return_opt_ _CRTIMP int __cdecl _cputws(_In_z_ const wchar_t * _String);
_Check_return_opt_ _CRTIMP int __cdecl _cwprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cwprintf_s(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_cwscanf_s) _CRTIMP int __cdecl _cwscanf(_In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_cwscanf_s_l) _CRTIMP int __cdecl _cwscanf_l(_In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cwscanf_s(_In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _cwscanf_s_l(_In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vcwprintf(_In_z_ _Printf_format_string_ const wchar_t *_Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vcwprintf_s(_In_z_ _Printf_format_string_ const wchar_t *_Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _cwprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vcwprintf_p(_In_z_ _Printf_format_string_ const wchar_t*  _Format, va_list _ArgList);

_CRTIMP int __cdecl _cwprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_CRTIMP int __cdecl _cwprintf_s_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_CRTIMP int __cdecl _vcwprintf_l(_In_z_ _Printf_format_string_ const wchar_t *_Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_CRTIMP int __cdecl _vcwprintf_s_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_CRTIMP int __cdecl _cwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_CRTIMP int __cdecl _vcwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP wint_t __cdecl _putwch_nolock(wchar_t _WCh);
_Check_return_ _CRTIMP wint_t __cdecl _getwch_nolock(void);
_Check_return_ _CRTIMP wint_t __cdecl _getwche_nolock(void);
_Check_return_opt_ _CRTIMP wint_t __cdecl _ungetwch_nolock(wint_t _WCh);

#if !defined(_MT)
#define _putwch()               _putwch_nolock()
#define _getwch()               _getwch_nolock()
#define _getwche()              _getwche_nolock()
#define _ungetwch()             _ungetwch_nolock()
#endif

#define _WCONIO_DEFINED
#endif  /* _WCONIO_DEFINED */

#if     !__STDC__

/* Non-ANSI names for compatibility */

#pragma warning(push)
#pragma warning(disable: 4141) /* Using deprecated twice */
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_cgets) _CRT_INSECURE_DEPRECATE(_cgets_s) _CRTIMP char * __cdecl cgets(_Out_z_cap_x_(*_Buffer+2) char * _Buffer);
#pragma warning(pop)
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_cprintf) _CRTIMP int __cdecl cprintf(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_cputs) _CRTIMP int __cdecl cputs(_In_z_ const char * _Str);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_cscanf) _CRTIMP int __cdecl cscanf(_In_z_ _Scanf_format_string_ const char * _Format, ...);
#ifdef  _M_IX86
_CRT_NONSTDC_DEPRECATE(_inp) int __cdecl inp(unsigned short);
_CRT_NONSTDC_DEPRECATE(_inpw) unsigned short __cdecl inpw(unsigned short);
#endif  /* _M_IX86 */
_Check_return_ _CRT_NONSTDC_DEPRECATE(_getch) _CRTIMP int __cdecl getch(void);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_getche) _CRTIMP int __cdecl getche(void);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_kbhit) _CRTIMP int __cdecl kbhit(void);
#ifdef  _M_IX86
_CRT_NONSTDC_DEPRECATE(_outp) int __cdecl outp(unsigned short, int);
_CRT_NONSTDC_DEPRECATE(_outpw) unsigned short __cdecl outpw(unsigned short, unsigned short);
#endif  /* _M_IX86 */
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_putch) _CRTIMP int __cdecl putch(int _Ch);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_ungetch) _CRTIMP int __cdecl ungetch(int _Ch);

#endif  /* __STDC__ */

#ifdef  __cplusplus
}
#endif

#endif  /* _INC_CONIO */
/***
*string.h - declarations for string manipulation functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains the function declarations for the string
*       manipulation functions.
*       [ANSI/System V]
*
*       [Public]
*
****/

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_STRING
#define _INC_STRING

#include <crtdefs.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _NLSCMP_DEFINED
#define _NLSCMPERROR    2147483647  /* currently == INT_MAX */
#define _NLSCMP_DEFINED
#endif

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/* For backwards compatibility */
#define _WConst_return _CONST_RETURN

/* Function prototypes */
#ifndef _CRT_MEMORY_DEFINED
#define _CRT_MEMORY_DEFINED
_CRTIMP void *  __cdecl _memccpy( _Out_opt_bytecap_(_MaxCount) void * _Dst, _In_ const void * _Src, _In_ int _Val, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP _CONST_RETURN void *  __cdecl memchr( _In_opt_bytecount_(_MaxCount) const void * _Buf , _In_ int _Val, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int     __cdecl _memicmp(_In_opt_bytecount_(_Size) const void * _Buf1, _In_opt_bytecount_(_Size) const void * _Buf2, _In_ size_t _Size);
_Check_return_ _CRTIMP int     __cdecl _memicmp_l(_In_opt_bytecount_(_Size) const void * _Buf1, _In_opt_bytecount_(_Size) const void * _Buf2, _In_ size_t _Size, _In_opt_ _locale_t _Locale);
        _Check_return_ int     __cdecl memcmp(_In_opt_bytecount_(_Size) const void * _Buf1, _In_opt_bytecount_(_Size) const void * _Buf2, _In_ size_t _Size);
        _CRT_INSECURE_DEPRECATE_MEMORY(memcpy_s) void *  __cdecl memcpy(_Out_opt_bytecapcount_(_Size) void * _Dst, _In_opt_bytecount_(_Size) const void * _Src, _In_ size_t _Size);
#if __STDC_WANT_SECURE_LIB__
_CRTIMP errno_t  __cdecl memcpy_s(_Out_opt_bytecap_post_bytecount_(_DstSize, _MaxCount) void * _Dst, _In_ rsize_t _DstSize, _In_opt_bytecount_(_MaxCount) const void * _Src, _In_ rsize_t _MaxCount);
#endif
        void *  __cdecl memset(_Out_opt_bytecapcount_(_Size) void * _Dst, _In_ int _Val, _In_ size_t _Size);

#if     !__STDC__
/* Non-ANSI names for compatibility */
_CRT_NONSTDC_DEPRECATE(_memccpy) _CRTIMP void * __cdecl memccpy(_Out_opt_bytecap_(_Size) void * _Dst, _In_opt_bytecount_(_Size) const void * _Src, _In_ int _Val, _In_ size_t _Size);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_memicmp) _CRTIMP int __cdecl memicmp(_In_opt_bytecount_(_Size) const void * _Buf1, _In_opt_bytecount_(_Size) const void * _Buf2, _In_ size_t _Size);
#endif  /* __STDC__ */

#endif

_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl _strset_s(_Inout_z_cap_(_DstSize) char * _Dst, _In_ size_t _DstSize, _In_ int _Value);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _strset_s, _Deref_prepost_z_ char, _Dest, _In_ int, _Value)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(char *, __RETURN_POLICY_DST, __EMPTY_DECLSPEC, _strset, _Inout_z_, char, _Dest, _In_ int, _Value)
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl strcpy_s(_Out_z_cap_(_SizeInBytes) char * _Dst, _In_ rsize_t _SizeInBytes, _In_z_ const char * _Src);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, strcpy_s, _Deref_post_z_ char, _Dest, _In_z_ const char *, _Source)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(char *, __RETURN_POLICY_DST, __EMPTY_DECLSPEC, strcpy, _Pre_cap_for_(_Source) _Post_z_, char, _Dest, _In_z_ const char *, _Source)
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl strcat_s(_Inout_z_cap_(_SizeInBytes) char * _Dst, _In_ rsize_t _SizeInBytes, _In_z_ const char * _Src);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, strcat_s, _Deref_prepost_z_ char, _Dest, _In_z_ const char *, _Source)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(char *, __RETURN_POLICY_DST, __EMPTY_DECLSPEC, strcat, _Pre_cap_for_(_Source) _Prepost_z_, char, _Dest, _In_z_ const char *, _Source)
        _Check_return_ int     __cdecl strcmp(_In_z_ const char * _Str1, _In_z_ const char * _Str2);
        _Check_return_ size_t  __cdecl strlen(_In_z_ const char * _Str);
_Check_return_ _CRTIMP size_t  __cdecl strnlen(_In_z_ const char * _Str, _In_ size_t _MaxCount);
#if __STDC_WANT_SECURE_LIB__ && !defined (__midl)
_Check_return_ static __inline size_t  __CRTDECL strnlen_s(_In_z_  const char * _Str, _In_ size_t _MaxCount)
{
    return (_Str==0) ? 0 : strnlen(_Str, _MaxCount);
}
#endif
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl memmove_s(_Out_opt_bytecap_post_bytecount_(_DstSize,_MaxCount) void * _Dst, _In_ rsize_t _DstSize, _In_opt_bytecount_(_MaxCount) const void * _Src, _In_ rsize_t _MaxCount);
#endif

#if     defined(_M_IA64)
        _CRT_INSECURE_DEPRECATE_MEMORY(memmove_s) void *  __cdecl memmove(_Out_opt_bytecapcount_(_Size) void * _Dst, _In_opt_bytecount_(_Size) const void * _Src, _In_ size_t _Size);
#else  /* defined (_M_IA64) */
_CRTIMP _CRT_INSECURE_DEPRECATE_MEMORY(memmove_s) void *  __cdecl memmove(_Out_opt_bytecapcount_(_Size) void * _Dst, _In_opt_bytecount_(_Size) const void * _Src, _In_ size_t _Size);
#endif  /* defined (_M_IA64) */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_strdup")
#undef _strdup
#endif

_Check_return_ _CRTIMP char *  __cdecl _strdup(_In_opt_z_ const char * _Src);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_strdup")
#endif

_Check_return_ _CRTIMP _CONST_RETURN char *  __cdecl strchr(_In_z_ const char * _Str, _In_ int _Val);
_Check_return_ _CRTIMP int     __cdecl _stricmp(_In_z_  const char * _Str1, _In_z_  const char * _Str2);
_Check_return_ _CRTIMP int     __cdecl _strcmpi(_In_z_  const char * _Str1, _In_z_  const char * _Str2);
_Check_return_ _CRTIMP int     __cdecl _stricmp_l(_In_z_  const char * _Str1, _In_z_  const char * _Str2, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int     __cdecl strcoll(_In_z_  const char * _Str1, _In_z_  const  char * _Str2);
_Check_return_ _CRTIMP int     __cdecl _strcoll_l(_In_z_  const char * _Str1, _In_z_  const char * _Str2, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int     __cdecl _stricoll(_In_z_  const char * _Str1, _In_z_  const char * _Str2);
_Check_return_ _CRTIMP int     __cdecl _stricoll_l(_In_z_  const char * _Str1, _In_z_  const char * _Str2, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int     __cdecl _strncoll  (_In_z_ const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int     __cdecl _strncoll_l(_In_z_ const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int     __cdecl _strnicoll (_In_z_ const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int     __cdecl _strnicoll_l(_In_z_ const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP size_t  __cdecl strcspn(_In_z_  const char * _Str, _In_z_  const char * _Control);
_Check_return_ _CRT_INSECURE_DEPRECATE(_strerror_s) _CRTIMP char *  __cdecl _strerror(_In_opt_z_ const char * _ErrMsg);
_Check_return_wat_ _CRTIMP errno_t __cdecl _strerror_s(_Out_z_cap_(_SizeInBytes) char * _Buf, _In_ size_t _SizeInBytes, _In_opt_z_ const char * _ErrMsg);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _strerror_s, char, _Buffer, _In_opt_z_ const char *, _ErrorMessage)
_Check_return_ _CRT_INSECURE_DEPRECATE(strerror_s) _CRTIMP char *  __cdecl strerror(_In_ int);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl strerror_s(_Out_z_cap_(_SizeInBytes) char * _Buf, _In_ size_t _SizeInBytes, _In_ int _ErrNum);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, strerror_s, char, _Buffer, _In_ int, _ErrorMessage)
_Check_return_wat_ _CRTIMP errno_t __cdecl _strlwr_s(_Inout_z_cap_(_Size) char * _Str, _In_ size_t _Size);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _strlwr_s, _Deref_prepost_z_ char, _String)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(char *, __RETURN_POLICY_DST, _CRTIMP, _strlwr, _Inout_z_, char, _String)
_Check_return_wat_ _CRTIMP errno_t __cdecl _strlwr_s_l(_Inout_z_cap_(_Size) char * _Str, _In_ size_t _Size, _In_opt_ _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _strlwr_s_l, _Deref_prepost_z_ char, _String, _In_opt_ _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _CRTIMP, _strlwr_l, _strlwr_s_l, _Deref_inout_z_cap_c_(_Size) char, _Inout_z_, char, _String, _In_opt_ _locale_t, _Locale)
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl strncat_s(_Inout_z_cap_(_SizeInBytes) char * _Dst, _In_ rsize_t _SizeInBytes, _In_z_ const char * _Src, _In_ rsize_t _MaxCount);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, strncat_s, _Deref_prepost_z_ char, _Dest, _In_z_ const char *, _Source, _In_ size_t, _Count)
#pragma warning(push)
#pragma warning(disable:6059)
/* prefast noise VSW 489802 */
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _CRTIMP, strncat, strncat_s, _Deref_inout_z_cap_c_(_Size) char, _Inout_z_cap_(_Count), char, _Dest, _In_z_ const char *, _Source, _In_ size_t, _Count)
#pragma warning(pop)
#if     defined(_M_IA64)
        _Check_return_ int     __cdecl strncmp(_In_z_  const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount);
#else
_Check_return_ _CRTIMP int     __cdecl strncmp(_In_z_ const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount);
#endif
_Check_return_ _CRTIMP int     __cdecl _strnicmp(_In_z_ const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int     __cdecl _strnicmp_l(_In_z_ const char * _Str1, _In_z_ const char * _Str2, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl strncpy_s(_Out_z_cap_(_SizeInBytes) char * _Dst, _In_ rsize_t _SizeInBytes, _In_z_ const char * _Src, _In_ rsize_t _MaxCount);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, strncpy_s, char, _Dest, _In_z_ const char *, _Source, _In_ size_t, _Count)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _CRTIMP_NOIA64, strncpy, strncpy_s, _Deref_out_z_cap_c_(_Size) char, _Out_cap_(_Count) _Post_maybez_, char, _Dest, _In_z_ const char *, _Source, _In_ size_t, _Count)
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl _strnset_s(_Inout_z_cap_(_SizeInBytes) char * _Str, _In_ size_t _SizeInBytes, _In_ int _Val, _In_ size_t _MaxCount);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _strnset_s, _Deref_prepost_z_ char, _Dest, _In_ int, _Val, _In_ size_t, _Count)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _CRTIMP, _strnset, _strnset_s, _Deref_inout_z_cap_c_(_Size) char, _Inout_z_cap_(_Count), char, _Dest, _In_ int, _Val, _In_ size_t, _Count)
_Check_return_ _CRTIMP _CONST_RETURN char *  __cdecl strpbrk(_In_z_ const char * _Str, _In_z_ const char * _Control);
_Check_return_ _CRTIMP _CONST_RETURN char *  __cdecl strrchr(_In_z_ const char * _Str, _In_ int _Ch);
_CRTIMP char *  __cdecl _strrev(_Inout_z_ char * _Str);
_Check_return_ _CRTIMP size_t  __cdecl strspn(_In_z_ const char * _Str, _In_z_ const char * _Control);
_Check_return_ _CRTIMP _CONST_RETURN char *  __cdecl strstr(_In_z_ const char * _Str, _In_z_ const char * _SubStr);
_Check_return_ _CRT_INSECURE_DEPRECATE(strtok_s) _CRTIMP char *  __cdecl strtok(_Inout_opt_z_ char * _Str, _In_z_ const char * _Delim);
#if __STDC_WANT_SECURE_LIB__
_Check_return_ _CRTIMP_ALTERNATIVE char *  __cdecl strtok_s(_Inout_opt_z_ char * _Str, _In_z_ const char * _Delim, _Inout_ _Deref_prepost_opt_z_ char ** _Context);
#endif
_Check_return_wat_ _CRTIMP errno_t __cdecl _strupr_s(_Inout_z_cap_(_Size) char * _Str, _In_ size_t _Size);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _strupr_s, _Deref_prepost_z_ char, _String)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(char *, __RETURN_POLICY_DST, _CRTIMP, _strupr, _Inout_z_, char, _String)
_Check_return_wat_ _CRTIMP errno_t __cdecl _strupr_s_l(_Inout_z_cap_(_Size) char * _Str, _In_ size_t _Size, _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _strupr_s_l, _Deref_prepost_z_ char, _String, _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _CRTIMP, _strupr_l, _strupr_s_l, _Deref_inout_z_cap_c_(_Size) char, _Inout_z_, char, _String, _In_opt_ _locale_t, _Locale)
_Check_return_opt_ _CRTIMP size_t  __cdecl strxfrm (_Out_opt_cap_(_MaxCount) _Post_maybez_ char * _Dst, _In_z_ const char * _Src, _In_ size_t _MaxCount);
_Check_return_opt_ _CRTIMP size_t  __cdecl _strxfrm_l(_Out_opt_cap_(_MaxCount) _Post_maybez_ char * _Dst, _In_z_ const char * _Src, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);

#ifdef __cplusplus
extern "C++" {
#ifndef _CPP_NARROW_INLINES_DEFINED
#define _CPP_NARROW_INLINES_DEFINED
_Check_return_ inline char * __CRTDECL strchr(_In_z_ char * _Str, _In_ int _Ch)
	{ return (char*)strchr((const char*)_Str, _Ch); }
_Check_return_ inline char * __CRTDECL strpbrk(_In_z_ char * _Str, _In_z_ const char * _Control)
	{ return (char*)strpbrk((const char*)_Str, _Control); }
_Check_return_ inline char * __CRTDECL strrchr(_In_z_ char * _Str, _In_ int _Ch)
	{ return (char*)strrchr((const char*)_Str, _Ch); }
_Check_return_ inline char * __CRTDECL strstr(_In_z_ char * _Str, _In_z_ const char * _SubStr)
	{ return (char*)strstr((const char*)_Str, _SubStr); }
#endif
#ifndef _CPP_MEMCHR_DEFINED
#define _CPP_MEMCHR_DEFINED
_Check_return_ inline void * __CRTDECL memchr(_In_opt_bytecount_(_N) void * _Pv, _In_ int _C, _In_ size_t _N)
	{ return (void*)memchr((const void*)_Pv, _C, _N); }
#endif
}
#endif

#if     !__STDC__

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("strdup")
#undef strdup
#endif

_Check_return_ _CRT_NONSTDC_DEPRECATE(_strdup) _CRTIMP char * __cdecl strdup(_In_opt_z_ const char * _Src);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("strdup")
#endif

/* prototypes for oldnames.lib functions */
_Check_return_ _CRT_NONSTDC_DEPRECATE(_strcmpi) _CRTIMP int __cdecl strcmpi(_In_z_ const char * _Str1, _In_z_ const char * _Str2);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_stricmp) _CRTIMP int __cdecl stricmp(_In_z_ const char * _Str1, _In_z_ const char * _Str2);
_CRT_NONSTDC_DEPRECATE(_strlwr) _CRTIMP char * __cdecl strlwr(_Inout_z_ char * _Str);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_strnicmp) _CRTIMP int __cdecl strnicmp(_In_z_ const char * _Str1, _In_z_ const char * _Str, _In_ size_t _MaxCount);
_CRT_NONSTDC_DEPRECATE(_strnset) _CRTIMP char * __cdecl strnset(_Inout_z_cap_(_MaxCount) char * _Str, _In_ int _Val, _In_ size_t _MaxCount);
_CRT_NONSTDC_DEPRECATE(_strrev) _CRTIMP char * __cdecl strrev(_Inout_z_ char * _Str);
_CRT_NONSTDC_DEPRECATE(_strset)         char * __cdecl strset(_Inout_z_ char * _Str, _In_ int _Val);
_CRT_NONSTDC_DEPRECATE(_strupr) _CRTIMP char * __cdecl strupr(_Inout_z_ char * _Str);

#endif  /* !__STDC__ */


#ifndef _WSTRING_DEFINED

/* wide function prototypes, also declared in wchar.h  */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wcsdup")
#undef _wcsdup
#endif

_Check_return_ _CRTIMP wchar_t * __cdecl _wcsdup(_In_z_ const wchar_t * _Str);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wcsdup")
#endif

#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl wcscat_s(_Inout_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ rsize_t _SizeInWords, _In_z_ const wchar_t * _Src);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, wcscat_s, _Deref_prepost_z_ wchar_t, _Dest, _In_z_ const wchar_t *, _Source)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, wcscat, _Pre_cap_for_(_Source) _Prepost_z_, wchar_t, _Dest, _In_z_ const wchar_t *, _Source)
_Check_return_ _CRTIMP _CONST_RETURN wchar_t * __cdecl wcschr(_In_z_ const wchar_t * _Str, wchar_t _Ch);
_Check_return_ _CRTIMP int __cdecl wcscmp(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl wcscpy_s(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ rsize_t _SizeInWords, _In_z_ const wchar_t * _Src);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, wcscpy_s, wchar_t, _Dest, _In_z_ const wchar_t *, _Source)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, wcscpy, _Pre_cap_for_(_Source) _Post_z_, wchar_t, _Dest, _In_z_ const wchar_t *, _Source)
_Check_return_ _CRTIMP size_t __cdecl wcscspn(_In_z_ const wchar_t * _Str, _In_z_ const wchar_t * _Control);
_Check_return_ _CRTIMP size_t __cdecl wcslen(_In_z_ const wchar_t * _Str);
_Check_return_ _CRTIMP size_t __cdecl wcsnlen(_In_z_ const wchar_t * _Src, _In_ size_t _MaxCount);
#if __STDC_WANT_SECURE_LIB__ && !defined (__midl)
_Check_return_ static __inline size_t __CRTDECL wcsnlen_s(_In_z_ const wchar_t * _Src, _In_ size_t _MaxCount)
{
    return (_Src == NULL) ? 0 : wcsnlen(_Src, _MaxCount);
}
#endif
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl wcsncat_s(_Inout_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ rsize_t _SizeInWords, _In_z_ const wchar_t * _Src, _In_ rsize_t _MaxCount);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, wcsncat_s, _Deref_prepost_z_ wchar_t, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _Count)
#pragma warning(push)
#pragma warning(disable:6059)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, wcsncat, wcsncat_s, _Deref_inout_z_cap_c_(_Size) wchar_t, _Inout_z_cap_(_Count), wchar_t, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _Count)
#pragma warning(pop)
_Check_return_ _CRTIMP int __cdecl wcsncmp(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl wcsncpy_s(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ rsize_t _SizeInWords, _In_z_ const wchar_t * _Src, _In_ rsize_t _MaxCount);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, wcsncpy_s, wchar_t, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _Count)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, wcsncpy, wcsncpy_s, _Pre_notnull_ _Post_maybez_ wchar_t, _Out_cap_(_Count) _Post_maybez_, wchar_t, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _Count)
_Check_return_ _CRTIMP _CONST_RETURN wchar_t * __cdecl wcspbrk(_In_z_ const wchar_t * _Str, _In_z_ const wchar_t * _Control);
_Check_return_ _CRTIMP _CONST_RETURN wchar_t * __cdecl wcsrchr(_In_z_ const wchar_t * _Str, _In_ wchar_t _Ch);
_Check_return_ _CRTIMP size_t __cdecl wcsspn(_In_z_ const wchar_t * _Str, _In_z_ const wchar_t * _Control);
_Check_return_ _CRTIMP _CONST_RETURN wchar_t * __cdecl wcsstr(_In_z_ const wchar_t * _Str, _In_z_ const wchar_t * _SubStr);
_Check_return_ _CRT_INSECURE_DEPRECATE(wcstok_s) _CRTIMP wchar_t * __cdecl wcstok(_Inout_opt_z_ wchar_t * _Str, _In_z_ const wchar_t * _Delim);
#if __STDC_WANT_SECURE_LIB__
_Check_return_ _CRTIMP_ALTERNATIVE wchar_t * __cdecl wcstok_s(_Inout_opt_z_ wchar_t * _Str, _In_z_ const wchar_t * _Delim, _Inout_ _Deref_prepost_opt_z_ wchar_t ** _Context);
#endif
_Check_return_ _CRT_INSECURE_DEPRECATE(_wcserror_s) _CRTIMP wchar_t * __cdecl _wcserror(_In_ int _ErrNum);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wcserror_s(_Out_opt_z_cap_(_SizeInWords) wchar_t * _Buf, _In_ size_t _SizeInWords, _In_ int _ErrNum);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _wcserror_s, wchar_t, _Buffer, _In_ int, _Error)
_Check_return_ _CRT_INSECURE_DEPRECATE(__wcserror_s) _CRTIMP wchar_t * __cdecl __wcserror(_In_opt_z_ const wchar_t * _Str);
_Check_return_wat_ _CRTIMP errno_t __cdecl __wcserror_s(_Out_opt_z_cap_(_SizeInWords) wchar_t * _Buffer, _In_ size_t _SizeInWords, _In_z_ const wchar_t * _ErrMsg);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, __wcserror_s, wchar_t, _Buffer, _In_z_ const wchar_t *, _ErrorMessage)

_Check_return_ _CRTIMP int __cdecl _wcsicmp(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2);
_Check_return_ _CRTIMP int __cdecl _wcsicmp_l(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _wcsnicmp(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int __cdecl _wcsnicmp_l(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl _wcsnset_s(_Inout_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ size_t _SizeInWords, _In_ wchar_t _Val, _In_ size_t _MaxCount);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _wcsnset_s, _Deref_prepost_z_ wchar_t, _Dst, wchar_t, _Val, _In_ size_t, _MaxCount)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wcsnset, _wcsnset_s, _Deref_inout_z_cap_c_(_Size) wchar_t, _Inout_z_cap_(_MaxCount), wchar_t, _Str, wchar_t, _Val, _In_ size_t, _MaxCount)
_CRTIMP wchar_t * __cdecl _wcsrev(_Inout_z_ wchar_t * _Str);
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl _wcsset_s(_Inout_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ size_t _SizeInWords, _In_ wchar_t _Value);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _wcsset_s, _Deref_prepost_z_ wchar_t, _Str, wchar_t, _Val)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wcsset, _wcsset_s, _Deref_inout_z_cap_c_(_Size) wchar_t, _Inout_z_, wchar_t, _Str, wchar_t, _Val)

_Check_return_wat_ _CRTIMP errno_t __cdecl _wcslwr_s(_Inout_z_cap_(_SizeInWords) wchar_t * _Str, _In_ size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _wcslwr_s, _Deref_prepost_z_ wchar_t, _String)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wcslwr, _Inout_z_, wchar_t, _String)
_Check_return_wat_ _CRTIMP errno_t __cdecl _wcslwr_s_l(_Inout_z_cap_(_SizeInWords) wchar_t * _Str, _In_ size_t _SizeInWords, _In_opt_ _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _wcslwr_s_l, _Deref_prepost_z_ wchar_t, _String, _In_opt_ _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wcslwr_l, _wcslwr_s_l, _Deref_inout_z_cap_c_(_Size) wchar_t, _Inout_z_, wchar_t, _String, _In_opt_ _locale_t, _Locale)
_Check_return_wat_ _CRTIMP errno_t __cdecl _wcsupr_s(_Inout_z_cap_(_Size) wchar_t * _Str, _In_ size_t _Size);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _wcsupr_s, _Deref_prepost_z_ wchar_t, _String)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wcsupr, _Inout_z_, wchar_t, _String)
_Check_return_wat_ _CRTIMP errno_t __cdecl _wcsupr_s_l(_Inout_z_cap_(_Size) wchar_t * _Str, _In_ size_t _Size, _In_opt_ _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _wcsupr_s_l, _Deref_prepost_z_ wchar_t, _String, _In_opt_ _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wcsupr_l, _wcsupr_s_l, _Deref_inout_z_cap_c_(_Size) wchar_t, _Inout_z_, wchar_t, _String, _In_opt_ _locale_t, _Locale)
_Check_return_opt_ _CRTIMP size_t __cdecl wcsxfrm(_Out_opt_cap_(_MaxCount) _Post_maybez_ wchar_t * _Dst, _In_z_ const wchar_t * _Src, _In_ size_t _MaxCount);
_Check_return_opt_ _CRTIMP size_t __cdecl _wcsxfrm_l(_Out_opt_cap_(_MaxCount) _Post_maybez_ wchar_t * _Dst, _In_z_ const wchar_t *_Src, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl wcscoll(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2);
_Check_return_ _CRTIMP int __cdecl _wcscoll_l(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _wcsicoll(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2);
_Check_return_ _CRTIMP int __cdecl _wcsicoll_l(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t *_Str2, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _wcsncoll(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int __cdecl _wcsncoll_l(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _wcsnicoll(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int __cdecl _wcsnicoll_l(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);

#ifdef  __cplusplus
#ifndef _CPP_WIDE_INLINES_DEFINED
#define _CPP_WIDE_INLINES_DEFINED
extern "C++" {
_Check_return_ inline wchar_t * __CRTDECL wcschr(_In_z_ wchar_t *_Str, wchar_t _Ch)
        {return ((wchar_t *)wcschr((const wchar_t *)_Str, _Ch)); }
_Check_return_ inline wchar_t * __CRTDECL wcspbrk(_In_z_ wchar_t *_Str, _In_z_ const wchar_t *_Control)
        {return ((wchar_t *)wcspbrk((const wchar_t *)_Str, _Control)); }
_Check_return_ inline wchar_t * __CRTDECL wcsrchr(_In_z_ wchar_t *_Str, _In_ wchar_t _Ch)
        {return ((wchar_t *)wcsrchr((const wchar_t *)_Str, _Ch)); }
_Check_return_ inline wchar_t * __CRTDECL wcsstr(_In_z_ wchar_t *_Str, _In_z_ const wchar_t *_SubStr)
        {return ((wchar_t *)wcsstr((const wchar_t *)_Str, _SubStr)); }
}
#endif
#endif

#if     !__STDC__

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("wcsdup")
#undef wcsdup
#endif

_Check_return_ _CRT_NONSTDC_DEPRECATE(_wcsdup) _CRTIMP wchar_t * __cdecl wcsdup(_In_z_ const wchar_t * _Str);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("wcsdup")
#endif

/* old names */
#define wcswcs wcsstr

/* prototypes for oldnames.lib functions */
_Check_return_ _CRT_NONSTDC_DEPRECATE(_wcsicmp) _CRTIMP int __cdecl wcsicmp(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_wcsnicmp) _CRTIMP int __cdecl wcsnicmp(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2, _In_ size_t _MaxCount);
_CRT_NONSTDC_DEPRECATE(_wcsnset) _CRTIMP wchar_t * __cdecl wcsnset(_Inout_z_cap_(_MaxCount) wchar_t * _Str, _In_ wchar_t _Val, _In_ size_t _MaxCount);
_CRT_NONSTDC_DEPRECATE(_wcsrev) _CRTIMP wchar_t * __cdecl wcsrev(_Inout_z_ wchar_t * _Str);
_CRT_NONSTDC_DEPRECATE(_wcsset) _CRTIMP wchar_t * __cdecl wcsset(_Inout_z_ wchar_t * _Str, wchar_t _Val);
_CRT_NONSTDC_DEPRECATE(_wcslwr) _CRTIMP wchar_t * __cdecl wcslwr(_Inout_z_ wchar_t * _Str);
_CRT_NONSTDC_DEPRECATE(_wcsupr) _CRTIMP wchar_t * __cdecl wcsupr(_Inout_z_ wchar_t * _Str);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_wcsicoll) _CRTIMP int __cdecl wcsicoll(_In_z_ const wchar_t * _Str1, _In_z_ const wchar_t * _Str2);

#endif  /* !__STDC__ */

#define _WSTRING_DEFINED
#endif


#ifdef  __cplusplus
}
#endif

#endif  /* _INC_STRING */


/*++ BUILD Version: 0001    Increment this if a change has global effects

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:


    windows.h

Abstract:

    Master include file for Windows applications.

--*/

#ifndef _WINDOWS_
#define _WINDOWS_

/*

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    sdkddkver.h

Abstract:

    Master include file for versioning windows SDK/DDK.

*/

#ifndef _INC_SDKDDKVER
#define _INC_SDKDDKVER

#pragma once

//
// _WIN32_WINNT version constants
//
#define _WIN32_WINNT_NT4                    0x0400
#define _WIN32_WINNT_WIN2K                  0x0500
#define _WIN32_WINNT_WINXP                  0x0501
#define _WIN32_WINNT_WS03                   0x0502
#define _WIN32_WINNT_LONGHORN               0x0600

//
// _WIN32_IE_ version constants
//
#define _WIN32_IE_IE20                      0x0200
#define _WIN32_IE_IE30                      0x0300
#define _WIN32_IE_IE302                     0x0302
#define _WIN32_IE_IE40                      0x0400
#define _WIN32_IE_IE401                     0x0401
#define _WIN32_IE_IE50                      0x0500
#define _WIN32_IE_IE501                     0x0501
#define _WIN32_IE_IE55                      0x0550
#define _WIN32_IE_IE60                      0x0600
#define _WIN32_IE_IE60SP1                   0x0601
#define _WIN32_IE_IE60SP2                   0x0603
#define _WIN32_IE_IE70                      0x0700

//
// IE <-> OS version mapping
//
// NT4 supports IE versions 2.0 -> 6.0 SP1
#define _WIN32_IE_NT4                       _WIN32_IE_IE20
#define _WIN32_IE_NT4SP1                    _WIN32_IE_IE20
#define _WIN32_IE_NT4SP2                    _WIN32_IE_IE20
#define _WIN32_IE_NT4SP3                    _WIN32_IE_IE302
#define _WIN32_IE_NT4SP4                    _WIN32_IE_IE401
#define _WIN32_IE_NT4SP5                    _WIN32_IE_IE401
#define _WIN32_IE_NT4SP6                    _WIN32_IE_IE50
// Win98 supports IE versions 4.01 -> 6.0 SP1
#define _WIN32_IE_WIN98                     _WIN32_IE_IE401
// Win98SE supports IE versions 5.0 -> 6.0 SP1
#define _WIN32_IE_WIN98SE                   _WIN32_IE_IE50
// WinME supports IE versions 5.5 -> 6.0 SP1
#define _WIN32_IE_WINME                     _WIN32_IE_IE55
// Win2k supports IE versions 5.01 -> 6.0 SP1
#define _WIN32_IE_WIN2K                     _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP1                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP2                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP3                  _WIN32_IE_IE501
#define _WIN32_IE_WIN2KSP4                  _WIN32_IE_IE501
#define _WIN32_IE_XP                        _WIN32_IE_IE60
#define _WIN32_IE_XPSP1                     _WIN32_IE_IE60SP1
#define _WIN32_IE_XPSP2                     _WIN32_IE_IE60SP2
#define _WIN32_IE_WS03                      0x0602
#define _WIN32_IE_WS03SP1                   _WIN32_IE_IE60SP2
#define _WIN32_IE_LONGHORN                  _WIN32_IE_IE70


//
// NTDDI version constants
//
#define NTDDI_WIN2K                         0x05000000
#define NTDDI_WIN2KSP1                      0x05000100
#define NTDDI_WIN2KSP2                      0x05000200
#define NTDDI_WIN2KSP3                      0x05000300
#define NTDDI_WIN2KSP4                      0x05000400

#define NTDDI_WINXP                         0x05010000
#define NTDDI_WINXPSP1                      0x05010100
#define NTDDI_WINXPSP2                      0x05010200

#define NTDDI_WS03                          0x05020000
#define NTDDI_WS03SP1                       0x05020100

#define NTDDI_LONGHORN                      0x06000000

//
// masks for version macros
//
#define OSVERSION_MASK      0xFFFF0000
#define SPVERSION_MASK      0x0000FF00
#define SUBVERSION_MASK     0x000000FF


//
// macros to extract various version fields from the NTDDI version
//
#define OSVER(Version)  ((Version) & OSVERSION_MASK)
#define SPVER(Version)  (((Version) & SPVERSION_MASK) >> 8)
#define SUBVER(Version) (((Version) & SUBVERSION_MASK) )


#if defined(DECLSPEC_DEPRECATED_DDK)

// deprecate in 2k or later
#if (NTDDI_VERSION >= NTDDI_WIN2K)
#define DECLSPEC_DEPRECATED_DDK_WIN2K DECLSPEC_DEPRECATED_DDK
#else
#define DECLSPEC_DEPRECATED_DDK_WIN2K
#endif

// deprecate in XP or later
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define DECLSPEC_DEPRECATED_DDK_WINXP DECLSPEC_DEPRECATED_DDK
#else
#define DECLSPEC_DEPRECATED_DDK_WINXP
#endif

// deprecate in WS03 or later
#if (NTDDI_VERSION >= NTDDI_WS03)
#define DECLSPEC_DEPRECATED_DDK_WIN2003 DECLSPEC_DEPRECATED_DDK
#else
#define DECLSPEC_DEPRECATED_DDK_WIN2003
#endif

// deprecate in WS03 or later
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
#define DECLSPEC_DEPRECATED_DDK_LONGHORN DECLSPEC_DEPRECATED_DDK
#else
#define DECLSPEC_DEPRECATED_DDK_LONGHORN
#endif

#endif // defined(DECLSPEC_DEPRECATED_DDK)


//
// if versions aren't already defined, default to most current
//

#define NTDDI_VERSION_FROM_WIN32_WINNT2(ver)    ver##0000
#define NTDDI_VERSION_FROM_WIN32_WINNT(ver)     NTDDI_VERSION_FROM_WIN32_WINNT2(ver)

#if !defined(_WIN32_WINNT) && !defined(_CHICAGO_)
#define  _WIN32_WINNT   0x0600
#endif

#ifndef NTDDI_VERSION
#ifdef _WIN32_WINNT
// set NTDDI_VERSION based on _WIN32_WINNT
#define NTDDI_VERSION   NTDDI_VERSION_FROM_WIN32_WINNT(_WIN32_WINNT)
#else
#define NTDDI_VERSION   0x06000000
#endif
#endif

#ifndef WINVER
#ifdef _WIN32_WINNT
// set WINVER based on _WIN32_WINNT
#define WINVER          _WIN32_WINNT
#else
#define WINVER          0x0600
#endif
#endif

#ifndef _WIN32_IE
#ifdef _WIN32_WINNT
// set _WIN32_IE based on _WIN32_WINNT
#if (_WIN32_WINNT <= _WIN32_WINNT_NT4)
#define _WIN32_IE       _WIN32_IE_IE50
#elif (_WIN32_WINNT <= _WIN32_WINNT_WIN2K)
#define _WIN32_IE       _WIN32_IE_IE501
#elif (_WIN32_WINNT <= _WIN32_WINNT_WINXP)
#define _WIN32_IE       _WIN32_IE_IE60
#elif (_WIN32_WINNT <= _WIN32_WINNT_WS03)
#define _WIN32_IE       0x0602
#else
#define _WIN32_IE       0x0700
#endif
#else
#define _WIN32_IE       0x0700
#endif
#endif

//
// Sanity check for compatible versions
//
#if defined(_WIN32_WINNT) && !defined(MIDL_PASS) && !defined(RC_INVOKED)

#if (defined(WINVER) && (WINVER < 0x0400) && (_WIN32_WINNT > 0x0400))
#error WINVER setting conflicts with _WIN32_WINNT setting
#endif

#if (((OSVERSION_MASK & NTDDI_VERSION) == NTDDI_WIN2K) && (_WIN32_WINNT != _WIN32_WINNT_WIN2K))
#error NTDDI_VERSION setting conflicts with _WIN32_WINNT setting
#endif

#if (((OSVERSION_MASK & NTDDI_VERSION) == NTDDI_WINXP) && (_WIN32_WINNT != _WIN32_WINNT_WINXP))
#error NTDDI_VERSION setting conflicts with _WIN32_WINNT setting
#endif

#if (((OSVERSION_MASK & NTDDI_VERSION) == NTDDI_WS03) && (_WIN32_WINNT != _WIN32_WINNT_WS03))
#error NTDDI_VERSION setting conflicts with _WIN32_WINNT setting
#endif

#if (((OSVERSION_MASK & NTDDI_VERSION) == NTDDI_LONGHORN) && (_WIN32_WINNT != _WIN32_WINNT_LONGHORN))
#error NTDDI_VERSION setting conflicts with _WIN32_WINNT setting
#endif

#if ((_WIN32_WINNT < _WIN32_WINNT_WIN2K) && (_WIN32_IE > _WIN32_IE_IE60SP1))
#error _WIN32_WINNT settings conflicts with _WIN32_IE setting
#endif

#endif  // defined(_WIN32_WINNT) && !defined(MIDL_PASS) && !defined(_WINRESRC_)


#endif  // !_INC_SDKDDKVER



//#include <sdkddkver.h>

#ifndef _INC_WINDOWS
#define _INC_WINDOWS

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/*  If defined, the following flags inhibit definition
 *     of the indicated items.
 *
 *  NOGDICAPMASKS     - CC_*, LC_*, PC_*, CP_*, TC_*, RC_
 *  NOVIRTUALKEYCODES - VK_*
 *  NOWINMESSAGES     - WM_*, EM_*, LB_*, CB_*
 *  NOWINSTYLES       - WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
 *  NOSYSMETRICS      - SM_*
 *  NOMENUS           - MF_*
 *  NOICONS           - IDI_*
 *  NOKEYSTATES       - MK_*
 *  NOSYSCOMMANDS     - SC_*
 *  NORASTEROPS       - Binary and Tertiary raster ops
 *  NOSHOWWINDOW      - SW_*
 *  OEMRESOURCE       - OEM Resource values
 *  NOATOM            - Atom Manager routines
 *  NOCLIPBOARD       - Clipboard routines
 *  NOCOLOR           - Screen colors
 *  NOCTLMGR          - Control and Dialog routines
 *  NODRAWTEXT        - DrawText() and DT_*
 *  NOGDI             - All GDI defines and routines
 *  NOKERNEL          - All KERNEL defines and routines
 *  NOUSER            - All USER defines and routines
 *  NONLS             - All NLS defines and routines
 *  NOMB              - MB_* and MessageBox()
 *  NOMEMMGR          - GMEM_*, LMEM_*, GHND, LHND, associated routines
 *  NOMETAFILE        - typedef METAFILEPICT
 *  NOMINMAX          - Macros min(a,b) and max(a,b)
 *  NOMSG             - typedef MSG and associated routines
 *  NOOPENFILE        - OpenFile(), OemToAnsi, AnsiToOem, and OF_*
 *  NOSCROLL          - SB_* and scrolling routines
 *  NOSERVICE         - All Service Controller routines, SERVICE_ equates, etc.
 *  NOSOUND           - Sound driver routines
 *  NOTEXTMETRIC      - typedef TEXTMETRIC and associated routines
 *  NOWH              - SetWindowsHook and WH_*
 *  NOWINOFFSETS      - GWL_*, GCL_*, associated routines
 *  NOCOMM            - COMM driver routines
 *  NOKANJI           - Kanji support stuff.
 *  NOHELP            - Help engine interface.
 *  NOPROFILER        - Profiler interface.
 *  NODEFERWINDOWPOS  - DeferWindowPos routines
 *  NOMCX             - Modem Configuration Extensions
 */

#if defined(RC_INVOKED) && !defined(NOWINRES)

#include <winresrc.h>

#else

#if defined(RC_INVOKED)
/* Turn off a bunch of stuff to ensure that RC files compile OK. */
#define NOATOM
#define NOGDI
#define NOGDICAPMASKS
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NORASTEROPS
#define NOSCROLL
#define NOSOUND
#define NOSYSMETRICS
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOCRYPT
#define NOMCX
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_IX86)
#define _X86_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_AMD64)
#define _AMD64_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_M68K)
#define _68K_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_MPPC)
#define _MPPC_
#endif

#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_M_IX86) && !defined(_AMD64_) && defined(_M_IA64)
#if !defined(_IA64_)
#define _IA64_
#endif // !_IA64_
#endif

#ifndef _MAC
#if defined(_68K_) || defined(_MPPC_)
#define _MAC
#endif
#endif

#if defined (_MSC_VER)
#if ( _MSC_VER >= 800 )
#ifndef __cplusplus
#pragma warning(disable:4116)       // TYPE_ALIGNMENT generates this - move it
                                    // outside the warning push/pop scope.
#endif
#endif
#endif

#ifndef RC_INVOKED
#if     ( _MSC_VER >= 800 )
#pragma warning(disable:4514)
#ifndef __WINDOWS_DONT_DISABLE_PRAGMA_PACK_WARNING__
#pragma warning(disable:4103)
#endif
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4001)
#pragma warning(disable:4201)
#pragma warning(disable:4214)
#endif
/***
*excpt.h - defines exception values, types and routines
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains the definitions and prototypes for the compiler-
*       dependent intrinsics, support functions and keywords which implement
*       the structured exception handling extensions.
*
*       [Public]
*
****/

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_EXCPT
#define _INC_EXCPT

#include <crtdefs.h>

#ifdef  _MSC_VER
/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * Exception disposition return values.
 */
typedef enum _EXCEPTION_DISPOSITION {
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;


/*
 * Prototype for SEH support function.
 */

#ifdef  _M_IX86

/*
 * Declarations to keep MS C 8 (386/486) compiler happy
 */
struct _EXCEPTION_RECORD;
struct _CONTEXT;

EXCEPTION_DISPOSITION __cdecl _except_handler (
    _In_ struct _EXCEPTION_RECORD *_ExceptionRecord,
    _In_ void * _EstablisherFrame,
    _Inout_ struct _CONTEXT *_ContextRecord,
    _Inout_ void * _DispatcherContext
    );

#elif   defined(_M_IA64)

/*
 * Declarations to keep IA64 compiler happy
 */
typedef struct _EXCEPTION_POINTERS *Exception_info_ptr;
struct _EXCEPTION_RECORD;
struct _CONTEXT;
struct _DISPATCHER_CONTEXT;


_CRTIMP EXCEPTION_DISPOSITION __cdecl __C_specific_handler (
    _In_ struct _EXCEPTION_RECORD *_ExceptionRecord,
    _In_ unsigned __int64 _MemoryStackFp,
    _In_ unsigned __int64 _BackingStoreFp,
    _Inout_ struct _CONTEXT *_ContextRecord,
    _Inout_ struct _DISPATCHER_CONTEXT *_DispatcherContext,
    _In_ unsigned __int64 _GlobalPointer
    );

#elif   defined(_M_AMD64)

/*
 * Declarations to keep AMD64 compiler happy
 */
struct _EXCEPTION_RECORD;
struct _CONTEXT;

#endif


/*
 * Keywords and intrinsics for SEH
 */

#ifdef  _MSC_VER

#define GetExceptionCode            _exception_code
#define exception_code              _exception_code
#define GetExceptionInformation     (struct _EXCEPTION_POINTERS *)_exception_info
#define exception_info              (struct _EXCEPTION_POINTERS *)_exception_info
#define AbnormalTermination         _abnormal_termination
#define abnormal_termination        _abnormal_termination

unsigned long __cdecl _exception_code(void);
void *        __cdecl _exception_info(void);
int           __cdecl _abnormal_termination(void);

#endif


/*
 * Legal values for expression in except().
 */

#define EXCEPTION_EXECUTE_HANDLER       1
#define EXCEPTION_CONTINUE_SEARCH       0
#define EXCEPTION_CONTINUE_EXECUTION    -1



#ifdef  __cplusplus
}
#endif

#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_EXCPT */
/***
*stdarg.h - defines ANSI-style macros for variable argument functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file defines ANSI-style macros for accessing arguments
*       of functions which take a variable number of arguments.
*       [ANSI]
*
*       [Public]
*
****/

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_STDARG
#define _INC_STDARG

#if     !defined(_WIN32)
#error ERROR: Only Win32 target supported!
#endif


#include <vadefs.h>

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end

#endif  /* _INC_STDARG */

//#include <excpt.h>
//#include <stdarg.h>
#endif /* RC_INVOKED */
/****************************************************************************
*                                                                           *
* windef.h -- Basic Windows Type Definitions                                *
*                                                                           *
* Copyright (c) Microsoft Corporation. All rights reserved.                 *
*                                                                           *
****************************************************************************/


#ifndef _WINDEF_
#define _WINDEF_
#pragma once

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif /* NO_STRICT */

// Win32 defines _WIN32 automatically,
// but Macintosh doesn't, so if we are using
// Win32 Functions, we must do it here

#ifdef _MAC
#ifndef _WIN32
#define _WIN32
#endif
#endif //_MAC

#ifndef WIN32
#define WIN32
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINVER
#define WINVER 0x0500
#endif /* WINVER */

/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#define MAX_PATH          260

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near
#undef pascal

#define far
#define near
#if (!defined(_MAC)) && ((_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED))
#define pascal __stdcall
#else
#define pascal
#endif

#if defined(DOSWIN32) || defined(_MAC)
#define cdecl _cdecl
#ifndef CDECL
#define CDECL _cdecl
#endif
#else
#define cdecl
#ifndef CDECL
#define CDECL
#endif
#endif

#ifdef _MAC
#define CALLBACK    PASCAL
#define WINAPI      CDECL
#define WINAPIV     CDECL
#define APIENTRY    WINAPI
#define APIPRIVATE  CDECL
#ifdef _68K_
#define PASCAL      __pascal
#else
#define PASCAL
#endif
#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#else
#define CALLBACK
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
#define PASCAL      pascal
#endif

#ifdef _M_CEE_PURE
#define WINAPI_INLINE  __clrcall
#else
#define WINAPI_INLINE  WINAPI
#endif

#undef FAR
#undef  NEAR
#define FAR                 far
#define NEAR                near
#ifndef CONST
#define CONST               const
#endif

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

#ifndef NT_INCLUDED
#include <winnt.h>
#endif /* NT_INCLUDED */

#include <specstrings.h>

/* Types use for passing & returning polymorphic values */
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

#ifndef NOMINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  /* NOMINMAX */

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))


#ifndef WIN_INTERNAL
DECLARE_HANDLE            (HWND);
DECLARE_HANDLE            (HHOOK);
#ifdef WINABLE
DECLARE_HANDLE            (HEVENT);
#endif
#endif

typedef WORD                ATOM;

typedef HANDLE NEAR         *SPHANDLE;
typedef HANDLE FAR          *LPHANDLE;
typedef HANDLE              HGLOBAL;
typedef HANDLE              HLOCAL;
typedef HANDLE              GLOBALHANDLE;
typedef HANDLE              LOCALHANDLE;
#ifndef _MANAGED
#ifndef _MAC
#ifdef _WIN64
typedef INT_PTR (FAR WINAPI *FARPROC)();
typedef INT_PTR (NEAR WINAPI *NEARPROC)();
typedef INT_PTR (WINAPI *PROC)();
#else
typedef int (FAR WINAPI *FARPROC)();
typedef int (NEAR WINAPI *NEARPROC)();
typedef int (WINAPI *PROC)();
#endif  // _WIN64
#else
typedef int (CALLBACK *FARPROC)();
typedef int (CALLBACK *NEARPROC)();
typedef int (CALLBACK *PROC)();
#endif
#else
typedef INT_PTR (WINAPI *FARPROC)(void);
typedef INT_PTR (WINAPI *NEARPROC)(void);
typedef INT_PTR (WINAPI *PROC)(void);
#endif

#if !defined(_MAC) || !defined(GDI_INTERNAL)
#ifdef STRICT
typedef void NEAR* HGDIOBJ;
#else
DECLARE_HANDLE(HGDIOBJ);
#endif
#endif

DECLARE_HANDLE(HKEY);
typedef HKEY *PHKEY;

#if !defined(_MAC) || !defined(WIN_INTERNAL)
DECLARE_HANDLE(HACCEL);
#endif
#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HBRUSH);
#endif
#if(WINVER >= 0x0400)
DECLARE_HANDLE(HCOLORSPACE);
#endif /* WINVER >= 0x0400 */
#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HDC);
#endif
DECLARE_HANDLE(HGLRC);          // OpenGL
DECLARE_HANDLE(HDESK);
DECLARE_HANDLE(HENHMETAFILE);
#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HFONT);
#endif
DECLARE_HANDLE(HICON);
#if !defined(_MAC) || !defined(WIN_INTERNAL)
DECLARE_HANDLE(HMENU);
#endif
DECLARE_HANDLE(HMETAFILE);
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;      /* HMODULEs can be used in place of HINSTANCEs */
#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HPEN);
#endif
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HSPRITE);
DECLARE_HANDLE(HSTR);
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HWINSTA);
DECLARE_HANDLE(HKL);

#if(WINVER >= 0x0400)
DECLARE_HANDLE(HWINEVENTHOOK);
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#ifndef _MAC
DECLARE_HANDLE(HMONITOR);
#endif
DECLARE_HANDLE(HUMPD);
#endif /* WINVER >= 0x0500 */

#ifndef _MAC
typedef int HFILE;
typedef HICON HCURSOR;      /* HICONs & HCURSORs are polymorphic */
#else
typedef short HFILE;
DECLARE_HANDLE(HCURSOR);    /* HICONs & HCURSORs are not polymorphic */
#endif

typedef DWORD   COLORREF;
typedef DWORD   *LPCOLORREF;

#define HFILE_ERROR ((HFILE)-1)

typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;

typedef const RECT FAR* LPCRECT;

typedef struct _RECTL       /* rcl */
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECTL, *PRECTL, *LPRECTL;

typedef const RECTL FAR* LPCRECTL;

typedef struct tagPOINT
{
    LONG  x;
    LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

typedef struct _POINTL      /* ptl  */
{
    LONG  x;
    LONG  y;
} POINTL, *PPOINTL;

typedef struct tagSIZE
{
    LONG        cx;
    LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

typedef SIZE               SIZEL;
typedef SIZE               *PSIZEL, *LPSIZEL;

typedef struct tagPOINTS
{
#ifndef _MAC
    SHORT   x;
    SHORT   y;
#else
    SHORT   y;
    SHORT   x;
#endif
} POINTS, *PPOINTS, *LPPOINTS;

//
//  File System time stamps are represented with the following structure:
//

typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#define _FILETIME_


/* mode selections for the device mode function */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8

#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* device capabilities indices */
#define DC_FIELDS           1
#define DC_PAPERS           2
#define DC_PAPERSIZE        3
#define DC_MINEXTENT        4
#define DC_MAXEXTENT        5
#define DC_BINS             6
#define DC_DUPLEX           7
#define DC_SIZE             8
#define DC_EXTRA            9
#define DC_VERSION          10
#define DC_DRIVER           11
#define DC_BINNAMES         12
#define DC_ENUMRESOLUTIONS  13
#define DC_FILEDEPENDENCIES 14
#define DC_TRUETYPE         15
#define DC_PAPERNAMES       16
#define DC_ORIENTATION      17
#define DC_COPIES           18

#ifdef __cplusplus
}
#endif

#endif /* _WINDEF_ */



//#include <windef.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#if !defined(_MAC) || defined(_WIN32NLS)
#include <winnls.h>
#endif
#ifndef _MAC
#include <wincon.h>
#include <winver.h>
#endif
#if !defined(_MAC) || defined(_WIN32REG)
#include <winreg.h>
#endif
#ifndef _MAC
#include <winnetwk.h>
#endif

#ifndef WIN32_LEAN_AND_MEAN
#include <cderr.h>
#include <dde.h>
#include <ddeml.h>
#include <dlgs.h>
#ifndef _MAC
#include <lzexpand.h>
#include <mmsystem.h>
#include <nb30.h>
#include <rpc.h>
#endif
#include <shellapi.h>
#ifndef _MAC
#include <winperf.h>
#include <winsock.h>
#endif
#ifndef NOCRYPT
#include <wincrypt.h>
#include <winefs.h>
#include <winscard.h>
#endif

#ifndef NOGDI
#ifndef _MAC
#include <winspool.h>
#ifdef INC_OLE1
#include <ole.h>
#else
#include <ole2.h>
#endif /* !INC_OLE1 */
#endif /* !MAC */
#include <commdlg.h>
#endif /* !NOGDI */
#endif /* WIN32_LEAN_AND_MEAN */

#include <stralign.h>

#ifdef _MAC
#include <winwlm.h>
#endif


#ifdef INC_OLE2
#include <ole2.h>
#endif /* INC_OLE2 */

#ifndef _MAC
#ifndef NOSERVICE
#include <winsvc.h>
#endif

#if(WINVER >= 0x0400)
#ifndef NOMCX
#include <mcx.h>
#endif /* NOMCX */

#ifndef NOIME
#include <imm.h>
#endif
#endif /* WINVER >= 0x0400 */
#endif

#ifndef RC_INVOKED
#if     ( _MSC_VER >= 800 )
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4001)
#pragma warning(default:4201)
#pragma warning(default:4214)
/* Leave 4514 disabled.  It's an unneeded warning anyway. */
#endif
#endif
#endif /* RC_INVOKED */

#endif /* RC_INVOKED */

#endif /* _INC_WINDOWS */
#endif /* _WINDOWS_ */



//#include<iostream>
//#include<stdio.h>
//#include<stdlib.h>
//#include<conio.h>
//#include<string.h>
//#include<Windows.h>

using namespace std;

void gotoxy (int x,int y)
{
	COORD c = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//individual train have individual class
class train
{
	struct cargo
	{
		//Where the cargoes to be unloaded
		int deboarding;
		//Where the cargoes will be loaded
		int boarding;
		//content of each cargoes
		char content[14];
		//to check your booking
		int pnr;
		//pointer for next cargo
		cargo *next;
	};
	typedef struct cargo *CARGO;
public:
	//contructor to keep the first pointer NULL initially
	train()
	{
		engine =NULL;
	}
	int train_no,self;
	char station_list[7][5];
	CARGO engine;
	CARGO sorting(CARGO engine, CARGO present)
	{
		if (engine == NULL)
			return present;
		else if (engine->next == NULL)
		{
			if(engine->deboarding<present->deboarding)
			{
				present->next = engine;
				return present;
			}
			else
			{
				engine->next = present;
				return engine;
			}
		}
		if (engine->deboarding<present->deboarding)
		{
			present->next = engine;
			return present;
		}
		CARGO prev=engine,temp=engine->next;
		while (temp!= NULL)
		{
			if (present->deboarding>temp->deboarding)
			{
				prev->next= present;
				present->next = temp;
				return engine;
			}
			prev=temp;
			temp = temp->next;
		}
		prev->next = present;
		return engine;
	}
	CARGO unloading(CARGO engine, int st)
	{
		if(engine==NULL)
		{
			cout<<"\n\n\tNothing to be unloaded\n";
			return NULL;
		}
		if (engine->next == NULL)
		{
			if (engine->deboarding <= st)
			{
				cout<<"\n\t"<<engine->content<<" is unloaded.";
				return NULL;
			}
			else
				return engine;
		}
		CARGO temp = engine,prev=engine;
		if (st >= temp->deboarding)
			{
				while (temp!=NULL)
				{
				  cout<<"\n\t"<<temp->content<<" is unloaded.";
				  temp= temp->next;
				}
				prev->next=NULL;
				return NULL;
			}
		temp = engine->next,prev=engine;
		while (temp!=NULL)
		{
			if (st >= temp->deboarding)
			{
				while (temp!=NULL)
				{
				  cout<<"\n\t"<<temp->content<<" is unloaded.";
				  temp= temp->next;
				}
				prev->next=NULL;
				return engine;
			}
			prev=temp;
			temp= temp->next;
		}
		return NULL;
	}

	CARGO get_data(CARGO engine)
	{
		CARGO x;
		x = (CARGO)malloc(sizeof(struct cargo));
boarding_station:
		cout<<"\n\tEnter The Boarding Station:\t";
		cin>>x->boarding;
		if (x->boarding<1 || x->boarding >7)
		{
			cout<<"\n\tINVALID INPUT";
			goto boarding_station;
		}
		cout<<"\n\tYou have chosen "<<station_list[(x->boarding)-1]<<" as your boarding station";
		cout<<"\n\n\tEnter The Deboarding Station:\t";
		cin>>x->deboarding;
		if (x->deboarding<=x->boarding || x->deboarding >7)
		{
			cout<<"\n\tINVALID INPUT";
			goto boarding_station;
		}
		cout<<"\n\tYou have chosen "<<station_list[(x->deboarding)-1]<<" as your deboarding station";
content:
		cout<<"\n\n\tEnter The Content(upto 14 letters ,for space use '_'):\t";
		cin>>x->content;
		if(strlen(x->content)>13)
		{
			cout<<"\n\tEnter the short form of the content!!!";
			goto content;
		}
		x->next = NULL;
		engine = sorting(engine,x);
		//x->pnr = (self*100)+(x->deboarding*10)+(x->boarding);
		cout<<"\n\n\tBooking done sucessfully !!";
		//cout<<"Your pnr is";
		return engine;
	}

	void content_display(CARGO engine)
	{
		int x=2,y=4,len,count=0;
		//two arrays to
		char engine_art[20][20]={{"      000"},{"    .0  _______"},{"  _||___||___||"},{">(            |"},{" /''00-----00''"}};
	    char cargo_art[20][20]={{" ______________"},{" |            |"},{" |            |"},{"=''00------00''"}};
		if (engine == NULL)
		{
			cout<<"\n\tThere is no booking !!";
			return;
		}
		system("cls");
		cout<<"\t\t1.Content\n\t\t2. Deboarding staion number\t is displayed\nCoaches are arranged such a way that unloading of cargo can be done easily";
		for (int i=0; i<6; i++)
		{
			gotoxy(x,y+i);
			if (i==3)
			{
				cout<<">( "<<train_no<<"      |";
			}
			else
			cout<<engine_art[i];
		}
		CARGO temp=engine;
		//cout<<len;

		while(temp!=NULL)
		{
			count++;
			len=strlen(temp->content);
		    len=12-len;
		    len/=2;
			x+=15;
			for (int i=0; i<6; i++)
	        {
		      gotoxy(x,y+i+1);
			  if (i==1)
			  {
				cout<<" |";
				for (int i=0; i<len; i++)
					cout<<" ";
				cout<<temp->content;
				if (strlen(temp->content)%2 != 0)
				{
				for (int i=0 ; i<(len+1); i++)
					cout<<" ";
				cout<<"|";
				}
				else
				{
					for (int i=0 ; i<(len); i++)
					cout<<" ";
				cout<<"|";
				}
			  }
			  else
			  cout<<cargo_art[i];
	        }
			gotoxy(x+5,y+3);
			cout<<temp->deboarding;
			temp=temp->next;
			if(count >=4)
			{
				count =0;
				y+=5;
				x=2;
			}
			gotoxy(50,50);
		}
	}

}obj[5];

char menu();
void train_list();
void booking();
void content_display();
void unloading()
	{
		int i=0,train_no_t,a=99;
		cout<<"\n\t\tWelcome to the Unloading Counter";
	cout<<"\n\t\t##############################\n\n";
re_train_no:
	cout<<"\n\tEnter the train no.:\t";
	cin>>train_no_t;
	for (i=0 ; i<3; i++)
	{
		if(obj[i].train_no == train_no_t)
		{
			a=i;
			break;
		}
	}
	if(a!=i)
	{
		cout<<"\n\tINVALID TRAIN NUMBER..!!";
		goto re_train_no;
	}
retry:
	cout<<"\n\tEnter the station number reached:\t";
	cin>>train_no_t;
	if(train_no_t>7 || train_no_t<1)
	{
		cout<<"INVALID..!!";
		goto retry;
	}
	obj[a].self =a;
	obj[a].engine = obj[a].unloading(obj[a].engine,train_no_t);
	}

void train_list()
{
	system("cls");
	char a;
	cout<<"\n\tTrain List:\n\t##########\n\n\t1. 22451 QLN-HWH \n\n\t2. 22461 UBL-HWH \n\n\t3. 22471 UBL-QLN\n\tEnter your choice for station list:\t";
	cin>>a;
	switch (a)
	{
	case '1': for (int i=0; i<7; i++)
			  {
				  cout<<i+1<<". "<<obj[0].station_list[i]<<"\n\n";
			  }
			  break;
	case '2': for (int i=0; i<7; i++)
			  {
				  cout<<i+1<<". "<<obj[1].station_list[i]<<"\n\n";
			  }
			  break;
	case '3': for (int i=0; i<7; i++)
			  {
				  cout<<i+1<<". "<<obj[2].station_list[i]<<"\n\n";
			  }
			  break;
	default: cout<<"\n\tINVALID";
	}
}


void booking()
{
	int i=0,train_no_t,a=99;
	cout<<"\n\t\tWelcome to the Booking Counter";
	cout<<"\n\t\t##############################\n\n";
re_train_no:
	cout<<"\n\tEnter the train no.:\t";
	cin>>train_no_t;
	for (i=0 ; i<3; i++)
	{
		if(obj[i].train_no == train_no_t)
		{
			a=i;
			break;
		}
	}
	if(a!=i)
	{
		cout<<"\n\tINVALID TRAIN NUMBER..!!";
		goto re_train_no;
	}
	obj[a].self =a;
	obj[a].engine = obj[a].get_data(obj[a].engine);
}


char menu ()
{
	system("cls");
	char choice;
	cout<<"\n\tMenu:";
	cout<<"\n\t#####\n";
	cout<<"\n\n\t1. Train List\n\n\t2. Booking\n\n\t3. Content Display\n\n\t4. Unloading\n\n\t5.Exit\n\tEnter your choice:\t";
	cin>>choice;
	return choice;
}


void cont_display()
{
	int train_no_t,i,a=99;
r_train_no:
	cout<<"\n\tEnter the train no.:\t";
	cin>>train_no_t;
	for (i=0 ; i<3; i++)
	{
		if(obj[i].train_no == train_no_t)
		{
			a=i;
			break;
		}
	}
	if(a!=i)
	{
		cout<<"\n\tINVALID TRAIN NUMBER..!!";
		goto r_train_no;
	}
	obj[a].self = a;
	obj[a].content_display(obj[a].engine);
}
int main()
{
	obj[0].train_no = 22451;
	obj[1].train_no = 22461;
	obj[2].train_no = 22471;
	char station_list_t1[7][4] ={{"QLN"},{"JHK"},{"KHF"},{"HJF"},{"TYE"},{"ERT"},{"HWH"}};
	for (int i=0; i<7; i++)
	{
		for (int j=0; j<4; j++)
		{
			obj[0].station_list[i][j]= station_list_t1[i][j];
		}
	}
	char station_list_t2[7][4] = {{"UBL"},{"KHJ"},{"FHK"},{"FJH"},{"TYE"},{"ERT"},{"HWH"}};
	for (int i=0; i<7; i++)
	{
		for (int j=0; j<4; j++)
		{
			obj[1].station_list[i][j] = station_list_t2[i][j];
		}
	}
	char station_list_t3[7][4] = {{"UBL"},{"KHJ"},{"FHK"},{"JHK"},{"KHF"},{"HJF"},{"QLN"}};
	for (int i=0; i<7; i++)
	{
		for (int j=0; j<4; j++)
		{
			obj[2].station_list[i][j] = station_list_t3[i][j];
		}
	}
	system("cls");
	cout<<"\n\n\n\n\n\t\t############################################";
	cout<<"\n\n\t\tWelcome To Freight Train Manangement System";
	cout<<"\n\n\t\t############################################\n\n\n";
	getch();
	char ch;
	while(1)
	{
		//system("cls");
		ch = menu();
		system("cls");
		switch(ch)
		{
			case '1':train_list();
			break;
			case '2':booking();
			break;
			case '3':cont_display();
			break;
			case '4':unloading();
			break;
			case '5':exit(0);
			break;
			default : cout<<"\n\tINVALID...!!";
		}
		getch();
	}
}
