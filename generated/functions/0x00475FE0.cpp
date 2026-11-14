// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475FE0 rf_cutscene_register_atexit_cleanup
// UNREALRED VERIFIED [cutscene-ui-20261028]: Registers0x476000 with atexit and clears active record pointer0x6FB24C. Does not initialize all registry/count globals; returns atexit result.
int rf_cutscene_register_atexit_cleanup()
{
  int result; // eax

  result = atexit(rf_cutscene_atexit_cleanup);
  unk_6FB24C = 0;
  return result;
}

