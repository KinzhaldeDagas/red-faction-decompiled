// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045ADF0 rf_multiplayer_chat_append_mapped_key
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl keyDWORD,existing stored int argument prototype preserved;decompiler may narrow mapper input to16 bits,but native
// forwards original DWORD slot to58B980. Check signed current Cstring length FIRST: >256 plays sound2(0,0.0,1.0),skips mapping/append. Length EXACT256 still admits,so one valid byte
// can grow string to257. Then mapper returns DWORD; signed result<128 admits MOVZX lowBYTE to string_append_byte_in_place,otherwise no append. No explicit lower-bound or
// printable-only check in body; original mapper tables/enable gate determine values. Mapper255 sentinel rejected,zero is admitted to append helper but adds no visible Cstring
// character. Original shifted/unshifted tables contain values32..255 and map1/14/28 to255;normal original mappings therefore do not admit negative/control values. No own
// runtime/active/team,clipboard,payload-length,UTF8 or throttle logic. Does not send.
int __cdecl rf_multiplayer_chat_append_mapped_key(__int16 a1)
{
  int result; // eax

  if ( (int)rf_string_length_from_cstr((const char **)unk_6F2CDC) > 256 )
    return rf_gamesound_play_event(2, 0, 0.0, 1.0);
  result = rf_input_keycode_to_character(a1);
  if ( result < 128 )
    return (int)rf_string_append_byte_in_place(unk_6F2CDC, result);
  return result;
}

