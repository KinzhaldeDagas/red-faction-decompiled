// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592100 rf_command_line_option_argument_as_float
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall option. Calls atof(argument pointer+16), explicitly stores result as32-bit float then reloads ST0. Numeric value therefore float-rounded rather than full atof double precision. No matched/default/NULL/range/whole-token validation. Prototype follows explicit float-width rounding; receiver value is owned argument string or NULL.
float __thiscall rf_command_line_option_argument_as_float(void *self)
{
  return atof((const char *)*((_DWORD *)self + 4));
}

