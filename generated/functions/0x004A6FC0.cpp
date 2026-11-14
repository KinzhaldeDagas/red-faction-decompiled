// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6FC0 rf_multiplayer_update_size_estimate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No arguments consumed (one caller leaves an unused pushed player DWORD). Counts circular player list87C324, D=max(count-1,1). Native wrapping32 arithmetic:
// S=662BEC+662BFC+662C14+662C24+5; B=D*S; Q=trunc_signed32((B+511)/512); result=B+30*Q-662BEC. For nonnegative nonoverflowing B this is30-byte overhead per512-byte chunk, but signed
// rounding/wrap must not be replaced unconditionally with unsigned ceiling. No mode/authority/state filter, packet send or input-table mutation; returns estimate in EAX.
int rf_multiplayer_update_size_estimate()
{
  _DWORD *v1; // [esp+0h] [ebp-18h]
  int v2; // [esp+4h] [ebp-14h]
  int v3; // [esp+4h] [ebp-14h]
  _DWORD *i; // [esp+10h] [ebp-8h]

  v2 = 0;
  for ( i = (_DWORD *)dword_87C324; i; i = v1 )
  {
    ++v2;
    if ( *i == dword_87C324 )
      v1 = nullptr;
    else
      v1 = (_DWORD *)*i;
  }
  v3 = v2 - 1;
  if ( v3 <= 0 )
    v3 = 1;
  return v3 * (dword_662C24 + dword_662C14 + dword_662BFC + dword_662BEC + 5)
       + 30 * ((v3 * (dword_662C24 + dword_662C14 + dword_662BFC + dword_662BEC + 5) + 511) / 512)
       - dword_662BEC;
}

