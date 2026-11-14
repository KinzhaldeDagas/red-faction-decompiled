// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510280 rf_weapon_fire_wait_milliseconds
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Negative weapon index returns0; no upper-bound check. Selector LOW BYTE EXACTLY1 selects F32 record+212, all other values+208. Loads float, multiplies by DOUBLE1000, adds DOUBLE0.5 in x87, then calls FTOL2SSE and returns low EAX. No intermediate F32 rounding before conversion, symmetric negative rounding, finite guard or clamp.
int __cdecl rf_weapon_fire_wait_milliseconds(int a1, char a2)
{
  if ( a1 < 0 )
    return 0;
  if ( a2 == 1 )
    return (int)(*((float *)&unk_9120D4 + 340 * a1) * 1000.0 + 0.5);
  return (int)(*((float *)&unk_9120D0 + 340 * a1) * 1000.0 + 0.5);
}

