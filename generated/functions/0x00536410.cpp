// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536410 rf_geomod_corner_pool_take_peak_and_reset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall pool plainRET. Read activePeakDWORD4200020(0x401654), replace with CURRENT activeDWORD4200024(0x401658), return priorpeakEAX. Numeric offsets render as loc_401654 in IDA but no code address dereference is intended. Does not return/free-count or leave peak unchanged; wrapper530630 shares this reset-on-read behavior.
int __thiscall rf_geomod_corner_pool_take_peak_and_reset(_DWORD *this)
{
  int v2; // [esp+4h] [ebp-4h]

  v2 = *(_DWORD *)((char *)&loc_401654 + (_DWORD)this);
  *(_DWORD *)((char *)&loc_401654 + (_DWORD)this) = *(this + 1050006);
  return v2;
}

