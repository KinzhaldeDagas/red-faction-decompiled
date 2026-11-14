// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6050 rf_multiplayer_log_open_banner
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No-argument banner emitter, not file opener. Fetches CRT time64(NULL) in EDX:EAX, converts through localtime64, strftime(max1024) with original Opened/date/banner format, then
// log_write_line(buffer,timestamp0). No own FILE guard or strftime/time conversion error check; write delegate handles disabled FILE. Does not assign log FILE pointer. Caller-cleaned
// RET, no incoming floating-point parameter.
void rf_multiplayer_log_open_banner()
{
  struct tm *v0; // eax
  char Buffer[1028]; // [esp+0h] [ebp-410h] BYREF
  __time64_t Time; // [esp+408h] [ebp-8h] BYREF

  Time = rf_crt_time64_forward(nullptr);
  v0 = rf_crt_localtime64_forward(&Time);
  strftime(Buffer, 0x400u, "Red Faction Multi Log - Opened %a, %b %d, %Y  at %I:%M%p\n----\n----\n----\n\n", v0);
  rf_multiplayer_log_write_line(Buffer, 0);
}

