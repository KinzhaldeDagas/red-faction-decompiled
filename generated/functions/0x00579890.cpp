// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579890 rf_text_parser_read_signed_decimal_or_hex_integer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver,no stack args. Skips trivia,optional minus ONLY;no plus handling. Recognizes0x/0X then accumulates hex,otherwise decimal digits (leading0 is still decimal).32bit multiply/add/negate overflow unchecked;stops before non-digit,does not require delimiter/end. Zero digits invokes579200 expected an integer after any minus/prefix already consumed. CRITICAL HEX LOOP: tests only strchr(hexCharset,currentByte),without explicitNUL guard. CRT609480 returns terminator pointer for Val0,so NUL is counted as a hex iteration,processed as digit -55 and cursor advances past allocated string. Hex at EOF can overread;bare0x atEOF can bypass no-digit error due to countedNUL. Decimal loop explicitly checks0..9
// and stops atNUL. No errno/range/size validation.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Host cursor admission must use unsigned32 multiply/add/negate to reproduce unchecked native signed-wrap values safely. Minus-only sign (no plus), 0x/0X hex, leading0 otherwise decimal, no delimiter boundary. Hex atNUL follows strchr terminator bug and overreads; represent this input as host Unsupported, never emulate out-of-bounds or call it a native checked rejection.
int __thiscall rf_text_parser_read_signed_decimal_or_hex_integer(char **this)
{
  char v3; // [esp+7h] [ebp-9h]
  int v4; // [esp+8h] [ebp-8h]
  int v5; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v5 = 0;
  v4 = 0;
  rf_text_parser_skip_trivia_and_cr_lines(this);
  if ( **(this + 1) == 45 )
  {
    v3 = 1;
    ++*(this + 1);
  }
  if ( **(this + 1) == 48 && ((*(this + 1))[1] == 120 || (*(this + 1))[1] == 88) )
  {
    *(this + 1) += 2;
    while ( strchr("0123456789abcdefABCDEF", **(this + 1)) )
    {
      ++v4;
      if ( **(this + 1) < 48 || **(this + 1) > 57 )
      {
        if ( **(this + 1) < 97 || **(this + 1) > 102 )
          v5 = 16 * v5 + *(*(this + 1))++ - 55;
        else
          v5 = 16 * v5 + *(*(this + 1))++ - 87;
      }
      else
      {
        v5 = 16 * v5 + *(*(this + 1))++ - 48;
      }
    }
  }
  else
  {
    while ( **(this + 1) >= 48 && **(this + 1) <= 57 )
    {
      ++v4;
      v5 = 10 * v5 + *(*(this + 1))++ - 48;
    }
  }
  if ( v3 )
    v5 = -v5;
  if ( !v4 )
    rf_text_parser_fatal_expected_with_context(this, "an integer");
  return v5;
}

