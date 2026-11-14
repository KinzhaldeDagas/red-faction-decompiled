// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507BF0 rf_ammo_parse_record
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Corrected missing argument: cdecl one parser pointer, native caller507B00 pushes parser and ADD ESP4. Destination=911488+20*current signed ammo count911480, no index/capacity validation/count increment here. Requires ordered $Name: then quoted RFString+0; requires $HUD Icon Filename: then quoted RFString+8. If string-is-empty55F780 true writes bitmap DWORD+16=-1; native EAX remains1. Otherwise loads frame-zero HUD bitmap44ACC0 from filename and stores/returns loader EAX including failure. No duplicate-name checks, field reordering, bitmap-success requirement or cleanup.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Record at911488+20*count. Require$Name quotedRFString at+0 THEN$HUD Icon Filename quotedRFString at+8; each raw quoted payload max254 bytes. Empty icon stores handle-1, otherwise loader failure is stored and does not prevent next row/count. Empty/duplicate/raw whitespace/highbytes names remain ordinal-bearing. No generic line/document parsing or name filtering may determine indices.
int __cdecl rf_ammo_parse_record(void *parser)
{
  int result; // eax
  char *v2; // eax
  _DWORD *destination; // [esp+0h] [ebp-4h]

  destination = (_DWORD *)((char *)&unk_911488 + 20 * unk_911480);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$HUD Icon Filename:");
  rf_text_parser_read_delimited_rfstring(parser, destination + 2, 34, 34);
  result = rf_string_is_empty(destination + 2);
  if ( (_BYTE)result )
  {
    destination[4] = -1;
  }
  else
  {
    v2 = (char *)rf_string_object_c_str_or_empty(destination + 2);
    result = rf_hud_load_frame_zero_bitmap(v2);
    destination[4] = result;
  }
  return result;
}

