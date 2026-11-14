// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6100 rf_multiplayer_log_close_banner
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No-argument closing-banner emitter, not file closer. Calls time64(NULL),localtime64,strftime(max1024) using original Closing on/date format, then log_write_line(buffer,0). No own
// FILE/time/strftime-error guard; no FILE pointer mutation or fclose. No incoming x87 value or stack parameter.
void rf_multiplayer_log_close_banner()
{
  struct tm *v0; // eax
  char Buffer[1028]; // [esp+0h] [ebp-410h] BYREF
  __time64_t Time; // [esp+408h] [ebp-8h] BYREF

  Time = rf_crt_time64_forward(nullptr);
  v0 = rf_crt_localtime64_forward(&Time);
  strftime(Buffer, 0x400u, "\n\n----\n----\n----\nRed Faction Multi Log - Closing on %a, %b %d, %Y  at %I:%M%p", v0);
  rf_multiplayer_log_write_line(Buffer, 0);
}

