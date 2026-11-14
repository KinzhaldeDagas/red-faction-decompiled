// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062F680 rf_cleanup_voodoo3_option
// UNREALRED VERIFIED [voodoo3-compatibility-20260903]: Destroys the global -voodoo3 Boolean-option record during process exit.
void __cdecl rf_cleanup_voodoo3_option()
{
  rf_command_line_option_destruct_argument_and_unlink((void **)rf_option_voodoo3);
}

