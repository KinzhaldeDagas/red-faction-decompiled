// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6170 rf_multiplayer_log_uptime
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl NO arguments; prior saved incoming double@ST0 prototype is false. Sign-extends startup Time2 DWORD to64, gets current time64(NULL), calls difftime64_forward(now,start), then
// truncates the INTERNALLY PRODUCED x87 result through __ftol2_sse and uses low signed32-bit seconds. Signed division/remainders split hours,minutes,seconds with truncation toward
// zero; no clamp for negative/overflowed elapsed. Calls variadic log formatter with original active-for h/m/s text. No own FILE guard (delegate checks); void semantic result. Native
// RET has no stack pop and caller pushes no uptime arguments.
void __cdecl rf_multiplayer_log_uptime()
{
  __time64_t v0; // rax
  __time64_t v1; // [esp-8h] [ebp-18h]
  int v2; // [esp+0h] [ebp-10h]

  v1 = (int)Time2;
  v0 = rf_crt_time64_forward(nullptr);
  v2 = (int)rf_crt_difftime64_forward(v0, v1);
  rf_multiplayer_log_printf(
    "Red Faction has been active for %d hours, %d minutes, and %d seconds",
    v2 / 3600,
    v2 % 3600 / 60,
    v2 % 3600 % 60);
}

