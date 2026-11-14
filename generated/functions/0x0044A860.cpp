// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A860 rf_hud_layout_profile_parse_coordinates
// UNREALRED VERIFIED [hud-layout-profile] Parses sparse HUD coordinate records as index, x, y triples into one 48-pair destination block, stopping at #End or when the next index is at least 48.
int __cdecl rf_hud_layout_profile_parse_coordinates(const char **a1, int a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_text_parser_try_consume_case_insensitive_prefix(a1, "#End");
    if ( (_BYTE)result )
      break;
    result = rf_text_parser_read_signed_decimal_or_hex_integer(a1);
    v3 = result;
    if ( result >= 48 )
      break;
    *(_DWORD *)(a2 + 8 * result) = rf_text_parser_read_signed_decimal_or_hex_integer(a1);
    *(_DWORD *)(a2 + 8 * v3 + 4) = rf_text_parser_read_signed_decimal_or_hex_integer(a1);
  }
  return result;
}

