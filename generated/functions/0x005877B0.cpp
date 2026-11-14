// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005877B0 rf_character_instance_reset_cyclic_action_mixes
// UNREALRED VERIFIED [mission-play-animation-20261013] VMesh type2 cyclic reset: clears instance animation-to-freeze index and global frozen byte, then sets mix0 only on records whose definition cyclic byte is1. Distinct from the action reset reached through0x565020; do not interchange the two wrappers.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Writes instance freeze-animation index7420=-1 and frozen byte7500=0. Loops action count4816; for each whose referenced definition byte at base7504+recordID+4620 equals1, writes mix4828+12*i=0. Other records unchanged. No action-list/count reset, resource release or all-action reset; returns receiver.
// UNREALRED VERIFIED [combat-speech-eye-phase-20261111]: Bounded writer proof: only7420=-1,7500byte0,and cyclic==1 record mixes+4828=0. No write to7428 sharedphase. This preserves phase across42F6C0 stand->crouch cache sampling and later restoration; a fixedtime.2 sampler would miss this dependency.
int __thiscall rf_character_instance_reset_cyclic_action_mixes(int this)
{
  int result; // eax
  int i; // [esp+8h] [ebp-4h]

  *(_DWORD *)(this + 7420) = -1;
  *(_BYTE *)(this + 7500) = 0;
  for ( i = 0; ; ++i )
  {
    result = this;
    if ( i >= *(_DWORD *)(this + 4816) )
      break;
    if ( *(_BYTE *)(*(_DWORD *)(this + 7504) + *(_DWORD *)(this + 12 * i + 4820) + 4620) == 1 )
      *(float *)(this + 12 * i + 4828) = 0.0;
  }
  return result;
}

