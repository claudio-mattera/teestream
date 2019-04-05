#pragma once

#ifndef TEESTREAM_H
#define TEESTREAM_H

#include <ostream>

/**
  A stream buffer that tees everything written to it to two stream buffers.

  \author Thomas Guest (http://wordaligned.org/articles/cpp-streambufs)

  \tparam char_type The character type (char, wchar_t...).
  \tparam traits Defines the stream and string operation properties of a character type.

  \see basic_teestream, teebuf, wteebuf
  */
template <typename char_type,
          typename traits = std::char_traits<char_type> >
class basic_teebuf:
    public std::basic_streambuf<char_type, traits>
{
public:
    typedef typename traits::int_type int_type;

    /**
      Construct a stream buffer which tees output to the supplied stream buffers.

      \param[in] sb1 The first stream buffer.
      \param[in] sb2 The second stream buffer.
      */
    basic_teebuf(std::basic_streambuf<char_type, traits> * sb1,
                 std::basic_streambuf<char_type, traits> * sb2)
      : sb1(sb1),
        sb2(sb2)
    {
    }

private:
    virtual int sync()
    {
        int const r1 = sb1->pubsync();
        int const r2 = sb2->pubsync();
        return r1 == 0 && r2 == 0 ? 0 : -1;
    }

    virtual int_type overflow(int_type c)
    {
        int_type const eof = traits::eof();

        if (traits::eq_int_type(c, eof)) {
            return traits::not_eof(c);
        } else {
            char_type const ch = traits::to_char_type(c);
            int_type const r1 = sb1->sputc(ch);
            int_type const r2 = sb2->sputc(ch);

            return
                traits::eq_int_type(r1, eof) ||
                traits::eq_int_type(r2, eof) ? eof : c;
        }
    }

private:
    std::basic_streambuf<char_type, traits> * sb1;
    std::basic_streambuf<char_type, traits> * sb2;
};

typedef basic_teebuf<char> teebuf;
typedef basic_teebuf<wchar_t> wteebuf;


/**
  An output stream that tees everything written to it to two streams.

  This stream is created with two references to two existing output streams.
  Everything that is written to this stream is written to both the two output
  streams. It is very useful to replicate everything that is printed on screen
  to a log file.

  \code
    std::ofstream log;
    log.open("data.log");
    teestream stream(std::cout, log);
    stream << ...
  \endcode

  \author Thomas Guest (http://wordaligned.org/articles/cpp-streambufs)

  \author Claudio Mattera (minor improvements)

  \tparam char_type The character type (char, wchar_t...).
  \tparam traits Defines the stream and string operation properties of a character type.

  \see teestream, wteestream, basic_teebuf
  */
template <typename char_type,
          typename traits = std::char_traits<char_type> >
class basic_teestream : public std::basic_ostream<char_type, traits>
{
public:
    /**
      Construct an ostream which tees output to the supplied output streams.

      \param[in] o1 The first output stream.
      \param[in] o2 The second output stream.
      */
    basic_teestream(std::basic_ostream<char_type, traits> & o1,
                    std::basic_ostream<char_type, traits> & o2)
    : std::basic_ostream<char_type, traits>(&tbuf),
      tbuf(o1.rdbuf(), o2.rdbuf())
    {
    }

private:
    basic_teebuf<char_type, traits> tbuf;
};

typedef basic_teestream<char> teestream;
typedef basic_teestream<wchar_t> wteestream;

#endif // TEESTREAM_H
