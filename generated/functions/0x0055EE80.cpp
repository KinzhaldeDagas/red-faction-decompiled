// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EE80 rf_advance_game_and_unpaused_clocks_milliseconds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl signed millisecond increment. If pause-depth17F1110==0, advances game clock663E90; always advances unpaused clock663E94. Each uses ifincrement<=period-current then current+=increment,else current=increment-(period-current), with period1072800000ms. Exact-period equality preserves period value; only a SINGLE wrap correction, no modulo loop. Negative increments can move clocks negative and oversized increments remain out of range. Return EAX is branch-dependent intermediate, not reliable time/status. No depth/overflow validation.
// UNREALRED VERIFIED [combat-emitter-clock-domain-20261112]: Original RF.exe raw .data bytes initialize BOTH wrapped counters663E90 and663E94 to signed1 (01000000), not zero. Pause depths17F1110 and18092F4 are in the unbacked virtual tail of .data and begin at loader zero; undefined IDB FF bytes are not runtime -1 initializers. Fresh direct-xref inventory finds only55EE80 writes to663E90/94, and55EF00/55EF20 writes to17F1110; this is a bounded direct-reference result, not a proof against aliased writes. Clock55EE80 preserves exact-period equality and is not reset by frame-history reset56CF30. Do not reinterpret a retained emitter+340 deadline using actor-local age0 or reset these counters on a host level import. Same-version PE mappings, full writer ASM and reference inventory are saved in combat_emitter_pool_20261112/clock_decode.
int __cdecl rf_advance_game_and_unpaused_clocks_milliseconds(int a1)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-4h]

  if ( !unk_17F1110 )
  {
    result = 1072800000 - dword_663E90;
    if ( a1 <= 1072800000 - dword_663E90 )
    {
      result = a1 + dword_663E90;
      dword_663E90 += a1;
    }
    else
    {
      dword_663E90 = a1 - (1072800000 - dword_663E90);
    }
  }
  v2 = 1072800000 - dword_663E94;
  if ( a1 <= 1072800000 - dword_663E94 )
  {
    dword_663E94 += a1;
  }
  else
  {
    dword_663E94 = a1 - v2;
    return a1 - v2;
  }
  return result;
}

