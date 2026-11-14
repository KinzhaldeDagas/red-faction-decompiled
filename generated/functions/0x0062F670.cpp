// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062F670 rf_cleanup_voodoo_option
// UNREALRED VERIFIED [voodoo3-compatibility-20260903]: Destroys the global -voodoo Boolean-option record during process exit.
void __cdecl rf_cleanup_voodoo_option()
{
  rf_command_line_option_destruct_argument_and_unlink((void **)rf_option_voodoo);
}

