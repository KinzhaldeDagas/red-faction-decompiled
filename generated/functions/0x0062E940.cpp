// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062E940 rf_initialize_voodoo3_option
// UNREALRED VERIFIED [voodoo3-compatibility-20260903]: Constructs the global Boolean command-line option record for -voodoo3 and registers its cleanup routine with atexit.
int rf_initialize_voodoo3_option()
{
  rf_command_line_option_construct_and_register(rf_option_voodoo3, (int)"-voodoo3", (int)&unk_644211, 0);
  return atexit(rf_cleanup_voodoo3_option);
}

