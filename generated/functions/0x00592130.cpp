// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592130 rf_command_line_option_get_argument
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall option; returns borrowed argument cstring pointer at+16, possibly NULL. Same field consumed by atoi5920E0/atof592100, allocated by591CC0 and deleted592080. Does not copy/allocate or test matched flag. Prior Concurrency::_CancellationTokenRegistration::_GetToken label/type was false library identification; this record is RF command-line option.
const char *__thiscall rf_command_line_option_get_argument(void *self)
{
  return *((const char **)self + 4);
}

