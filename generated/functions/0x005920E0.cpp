// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005920E0 rf_command_line_option_argument_as_int
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall option. Direct atoi(argument pointer+16), returns int. No matched/required check, default value, NULL guard, range checking or whole-token validation; accepts CRT numeric prefix semantics.
int __thiscall rf_command_line_option_argument_as_int(const char **this)
{
  return atoi(*(this + 4));
}

