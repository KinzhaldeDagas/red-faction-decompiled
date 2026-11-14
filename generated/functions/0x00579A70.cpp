// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579A70 rf_text_parser_read_unsigned_decimal_or_hex_integer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser; returns unchecked 32-bit accumulator in EAX. Skips full trivia, accepts decimal digits or 0x/0X hex, no plus/minus and no token-boundary check; leading zero alone is decimal. No counted digits invokes fatal expected a uint. Hex loop calls CRT strchr on charset without separate NUL guard: strchr(charset,0) succeeds, counts NUL as a digit, adds -55 and advances beyond source terminator; bare 0x at EOF can bypass the no-digit diagnostic. Arithmetic wraps modulo 2^32; signedness of stored prototype is not a range check.
int __thiscall rf_text_parser_read_unsigned_decimal_or_hex_integer(char **this)
{
  int v3; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  v3 = 0;
  v4 = 0;
  rf_text_parser_skip_trivia_and_cr_lines(this);
  if ( **(this + 1) == 48 && ((*(this + 1))[1] == 120 || (*(this + 1))[1] == 88) )
  {
    *(this + 1) += 2;
    while ( strchr("0123456789abcdefABCDEF", **(this + 1)) )
    {
      ++v3;
      if ( **(this + 1) < 48 || **(this + 1) > 57 )
      {
        if ( **(this + 1) < 97 || **(this + 1) > 102 )
          v4 = 16 * v4 + *(*(this + 1))++ - 55;
        else
          v4 = 16 * v4 + *(*(this + 1))++ - 87;
      }
      else
      {
        v4 = 16 * v4 + *(*(this + 1))++ - 48;
      }
    }
  }
  else
  {
    while ( **(this + 1) >= 48 && **(this + 1) <= 57 )
    {
      ++v3;
      v4 = 10 * v4 + *(*(this + 1))++ - 48;
    }
  }
  if ( !v3 )
    rf_text_parser_fatal_expected_with_context(this, "a uint");
  return v4;
}

