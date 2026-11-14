// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591E80 rf_command_line_fatal_on_unrecognized_dash_options
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl. Scans tokens against circular registered-option names with stricmp. Recognized option requiring argument blindly increments token index to skip next token, regardless of presence, leading minus or prior consumed flags. Otherwise unmatched token starting minus triggers sprintf into260-byte local and fatal cmdline.cpp340; unmatched positional tokens accepted. Does not consult consumed flags or validate required argument values. A recognized option can therefore cause the next dash option to be skipped by this validation pass.
void rf_command_line_fatal_on_unrecognized_dash_options()
{
  char Buffer[260]; // [esp+0h] [ebp-110h] BYREF
  _DWORD *j; // [esp+108h] [ebp-8h]
  int i; // [esp+10Ch] [ebp-4h]

  for ( i = 0; i < dword_1BA1EDC; ++i )
  {
    for ( j = dword_1BA1EE0; j != &dword_1BA1EE0; j = (_DWORD *)*j )
    {
      if ( !_stricmp((const char *)j[2], (const char *)dword_1BA1D48[2 * i]) )
      {
        if ( *((_BYTE *)j + 21) )
          ++i;
        break;
      }
    }
    if ( j == &dword_1BA1EE0 && *(_BYTE *)dword_1BA1D48[2 * i] == 45 )
    {
      sprintf(Buffer, "Unrecognized command line parameter %s", (const char *)dword_1BA1D48[2 * i]);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\os\\cmdline.cpp", 340, Buffer);
    }
  }
}

