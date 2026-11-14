// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579C20 rf_text_parser_read_number_with_optional_decimal_fraction
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser; numeric result in ST0. Skips trivia, consumes an outer minus, then either accepts leading dot with integer zero or calls signed decimal/hex integer reader579890, which can consume another minus and skip more trivia. Optional decimal fraction accumulates digit*weight into float, weight initially float0.1 and repeatedly multiplied by double0.1 then stored to float. Fraction digits are optional: dot alone accepted. Outer minus negates integer and fractional parts separately. Fraction branch stores final sum to float before ST0 return; integer-only branch returns FILD integer without that float rounding. No exponent or plus grammar. Double minus is accepted: --5 returns5; --5.2 returns
// approximately4.8. Hex integer portion inherits579890 NUL overread. No normalization, finite/range or token-boundary check.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Numeric reader reconfirmed from ASM: outerminus then leadingdot or signed int reader (which skips trivia and allows secondminus). Fraction accumulator and weight stored binary32 every iteration; weight multiplied by double at630FC0 then storedfloat. Final fraction sum storedfloat; integer-only FILD returned then caller stores. Dot alone allowed; --5=>5, --5.2 approx4.8. No exponent/plus or positivity validation.
double __thiscall rf_text_parser_read_number_with_optional_decimal_fraction(char **this)
{
  int signed_decimal_or_hex_integer; // [esp+Ch] [ebp-10h]
  char v5; // [esp+13h] [ebp-9h]
  float v6; // [esp+14h] [ebp-8h]
  float v7; // [esp+18h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines(this);
  v5 = 0;
  if ( **(this + 1) == 45 )
  {
    v5 = 1;
    ++*(this + 1);
  }
  if ( **(this + 1) == 46 )
  {
    signed_decimal_or_hex_integer = 0;
    goto LABEL_9;
  }
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(this);
  if ( **(this + 1) == 46 )
  {
LABEL_9:
    ++*(this + 1);
    v6 = 0.0;
    v7 = 0.1;
    while ( **(this + 1) >= 48 && **(this + 1) <= 57 )
    {
      v6 = (double)(*(*(this + 1))++ - 48) * v7 + v6;
      v7 = v7 * 0.1000000014901161;
    }
    if ( v5 )
    {
      signed_decimal_or_hex_integer = -signed_decimal_or_hex_integer;
      v6 = -v6;
    }
    return (float)((double)signed_decimal_or_hex_integer + v6);
  }
  if ( v5 )
    return (double)-signed_decimal_or_hex_integer;
  return (double)signed_decimal_or_hex_integer;
}

