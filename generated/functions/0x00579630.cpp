// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579630 rf_text_parser_try_consume_case_insensitive_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus keyword,RET4. Skips full trivia,requires nonzero current byte,compares exactly strlen(keyword) case-insensitively. On match advances by that length and returns1;otherwise0 with only trivia consumed. No word boundary,identifier grammar or trailing-delimiter requirement. Empty keyword at non-EOF succeeds without character progress;EOF fails.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Raw native optional probe consumes leading trivia even on mismatch, compares exactly prefix length case-insensitively without word/token boundary, then advances only if match. No line split, substring search, unknown-field skip or trim of quoted values.
bool __thiscall rf_text_parser_try_consume_case_insensitive_prefix(const char **this, char *String2)
{
  int v3; // eax
  unsigned int MaxCount; // [esp+18h] [ebp-4h]

  MaxCount = strlen(String2);
  rf_text_parser_skip_trivia_and_cr_lines(this);
  if ( !**(this + 1) )
    return 0;
  v3 = _strnicmp(*(this + 1), String2, MaxCount);
  if ( !v3 )
    *(this + 1) += MaxCount;
  return v3 == 0;
}

