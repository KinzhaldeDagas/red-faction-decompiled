// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A63F0 rf_multiplayer_log_close
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No arguments. If FILE pointer7B1530 nonnull, emits closing banner then fclose(pointer), and sets7B1530=NULL regardless fclose result. Null FILE skips all calls. No mode/authority
// admission or unlink/delete of log file. EAX is fclose result on nonnull path and incidental on null path; no incoming x87 argument.
int rf_multiplayer_log_close()
{
  int result; // eax

  if ( MEMORY[0x7B1530] )
  {
    rf_multiplayer_log_close_banner();
    result = fclose(MEMORY[0x7B1530]);
    MEMORY[0x7B1530] = nullptr;
  }
  return result;
}

