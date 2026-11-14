// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005920C0 rf_command_line_bool_option_is_enabled
// UNREALRED VERIFIED [voodoo3-compatibility-20260903]: Corrects a false concurrency-library signature. Returns byte +0x14 from RF's command-line Boolean-option record; callers use it for the registered -voodoo and -voodoo3 options.
char __thiscall rf_command_line_bool_option_is_enabled(_BYTE *this)
{
  return *(this + 20);
}

