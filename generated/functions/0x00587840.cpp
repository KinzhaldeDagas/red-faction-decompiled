// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587840 rf_character_instance_reset_actions
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Thiscall no stack args. Unconditionally sets freeze designation7420=-1,animation-alone owner7424=-1,global hold BYTE7500=0. Iterates existing record count4816 and zeros mix at4828+12*i only when base classification BYTE[4620+recordAnimationIndex]==0. State records(any nonzero class) remain untouched. Does NOT immediately remove records/drop clip references,reset phase7428,clear7444/7448/7452/delta vectors/events,reset count or change record ticks. Next advance performs zero-weight removal if entry gates permit. EAX is receiver when loop never runs,otherwise loop count residue; not success/record pointer. No count/index/base validation.
int __thiscall rf_character_instance_reset_actions(int this)
{
  int result; // eax
  int i; // [esp+8h] [ebp-4h]

  result = this;
  *(_DWORD *)(this + 7420) = -1;
  *(_DWORD *)(this + 7424) = -1;
  *(_BYTE *)(this + 7500) = 0;
  for ( i = 0; i < *(_DWORD *)(this + 4816); ++i )
  {
    if ( !*(_BYTE *)(*(_DWORD *)(this + 7504) + *(_DWORD *)(this + 12 * i + 4820) + 4620) )
      *(float *)(this + 12 * i + 4828) = 0.0;
    result = i + 1;
  }
  return result;
}

