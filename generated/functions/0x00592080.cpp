// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592080 rf_command_line_option_delete_argument
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall option. If argument pointer+16 nonnull calls scalar operator delete then sets it NULL. Does not unlink option, change matched flag or free borrowed name/receiver or modify auxiliary DWORD+12. No independent success return.
void __thiscall rf_command_line_option_delete_argument(void **this)
{
  if ( *(this + 4) )
  {
    operator delete(*(this + 4));
    *(this + 4) = nullptr;
  }
}

