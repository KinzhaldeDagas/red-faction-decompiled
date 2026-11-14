// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460FF0 rf_console_simultaneous_ping
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg console callback. Nonzero parsed-count1809818 ->read_argument_validate_type_mask(8,0),IGNORE return,copy global numeric slot180981C into661F98,clamp
// signed1..32,registry_write_dword(NULL,original key661FEC->"ServerListSimultaneous_ping",clamped value). Nonzero diagnostic/help flag1809814 then prints localized Usage and literal
// "     simultaneous_ping <n>\n",independently of count branch. No display of current value,loop/drain of further args,network query or rollback on persistence failure. No own
// runtime gate. EAX undefined/residual when neither branch does work;not uniform success.
int rf_console_simultaneous_ping()
{
  int result; // eax

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(8, 0);
    *(_DWORD *)&dword_661F98 = dword_180981C;
    rf_integer_clamp_in_place(&dword_661F98, 1, 32);
    result = rf_registry_write_dword(nullptr, off_661FEC, *(_DWORD *)&dword_661F98);
  }
  if ( dword_1809814 )
  {
    rf_console_output_append_text_lines(dword_88E210, nullptr);
    return rf_console_output_append_text_lines("     simultaneous_ping <n>\n", nullptr);
  }
  return result;
}

