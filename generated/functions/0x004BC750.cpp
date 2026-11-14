// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC750 rf_object_add_life_upper_clamped
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Add supplied float to common object life+0x34. Select upper cap: runtime type0 uses descriptor+0x44, type4 descriptor+0x3C, other types float literal3.4028235e38. If resulting life>=cap store cap. No lower clamp, dead/alive test, type restriction before add, or damage/death-side-effect dispatch in this helper.
void __cdecl rf_object_add_life_upper_clamped(int a1, float a2)
{
  int v2; // [esp+0h] [ebp-8h]
  float v3; // [esp+4h] [ebp-4h]

  v3 = 3.4028235e38;
  *(float *)(a1 + 52) = *(float *)(a1 + 52) + a2;
  v2 = *(_DWORD *)(a1 + 36);
  if ( v2 )
  {
    if ( v2 == 4 )
      v3 = *(float *)(*(_DWORD *)(a1 + 660) + 60);
  }
  else
  {
    v3 = *(float *)(*(_DWORD *)(a1 + 660) + 68);
  }
  if ( v3 <= (double)*(float *)(a1 + 52) )
    *(float *)(a1 + 52) = v3;
}

