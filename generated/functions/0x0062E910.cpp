// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062E910 rf_initialize_voodoo_option
// UNREALRED VERIFIED [voodoo3-compatibility-20260903]: Constructs the global Boolean command-line option record for -voodoo and registers its cleanup routine with atexit.
int rf_initialize_voodoo_option()
{
  rf_command_line_option_construct_and_register(rf_option_voodoo, (int)"-voodoo", (int)&unk_644210, 0);
  return atexit(rf_cleanup_voodoo_option);
}

