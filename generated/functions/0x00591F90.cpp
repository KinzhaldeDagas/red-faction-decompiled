// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591F90 rf_command_line_option_construct_and_register
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall option record; name pointer, auxiliary DWORD, requires-argument byte. Stores borrowed name pointer at+8 and auxiliary DWORD at+12, requires byte+21, argument pointer+16=NULL, matched byte+20=0. Initializes circular global sentinel1BA1EE0 once using byte1BA1ED8, then appends named option to list tail. NULL name leaves receiver links+0/+4 untouched and does not register. Returns receiver. Does not copy/free name, interpret auxiliary DWORD, parse argv, allocate argument or set a default value.
_DWORD *__thiscall rf_command_line_option_construct_and_register(_DWORD *this, int a2, int a3, char a4)
{
  *(this + 2) = a2;
  *(this + 3) = a3;
  *((_BYTE *)this + 21) = a4;
  *(this + 4) = 0;
  *((_BYTE *)this + 20) = 0;
  if ( !unk_1BA1ED8 )
  {
    dword_1BA1EE0 = &dword_1BA1EE0;
    unk_1BA1EE4 = &dword_1BA1EE0;
    unk_1BA1ED8 = 1;
  }
  if ( a2 )
  {
    *(this + 1) = unk_1BA1EE4;
    *this = &dword_1BA1EE0;
    *unk_1BA1EE4 = this;
    unk_1BA1EE4 = this;
  }
  return this;
}

