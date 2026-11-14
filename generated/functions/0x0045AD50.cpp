// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AD50 rf_multiplayer_chat_remove_last_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg,existing SEH chunks/prototype preserved. Query signed Cstring length of RFString6F2CDC. Length>1 creates inclusive
// substring indices0..length-2,assigns temporary back,then destroys temporary; removes ONE trailing byte. Length<=1 assigns empty original Cstring636072. No UTF8/codepoint
// processing,caret selection,active/init flag mutation,clock reset,sound or network send. Caller backspace handler subsequently runs ordinary key mapper as a distinct step;original
// shifted/unshifted maps both yield255 for14,so no extra byte is appended.
void __cdecl rf_multiplayer_chat_remove_last_byte()
{
  _DWORD *v0; // [esp+4h] [ebp-20h]
  _DWORD v1[2]; // [esp+Ch] [ebp-18h] BYREF
  signed int v2; // [esp+14h] [ebp-10h]
  int v3; // [esp+20h] [ebp-4h]

  v2 = rf_string_length_from_cstr((const char **)unk_6F2CDC);
  if ( v2 > 1 )
  {
    v0 = rf_string_substring_inclusive(unk_6F2CDC, v1, 0, v2 - 2);
    v3 = 0;
    rf_string_assign_from_object(unk_6F2CDC, (int)v0);
    v3 = -1;
    rf_string_destroy_buffer(v1);
  }
  else
  {
    rf_string_assign_from_cstr(unk_6F2CDC, (char *)&byte_636072);
  }
}

