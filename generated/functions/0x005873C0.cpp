// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005873C0 rf_character_instance_remove_action_record
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Finds first exact animation index, drops associated clip reference+116 through5BA420, decrements action count and shifts remaining12-byte records down. For tracked indices+7420,+7424,+7496: equal removed index becomes-1, greater indices decrement. Does not clear now-unused tail storage or free clip raw data. Missing index leaves state unchanged. No return-status contract, NULL or count validation.
_DWORD *__thiscall rf_character_instance_remove_action_record(_DWORD *this, int a2)
{
  _DWORD *v2; // edx
  _DWORD *result; // eax
  int j; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < *(this + 1204); ++i )
  {
    if ( *(this + 3 * i + 1205) == a2 )
    {
      rf_animation_clip_drop_instance_reference(*(_DWORD *)(*(this + 1876) + 4 * a2 + 3932));
      --*(this + 1204);
      for ( j = i; j < *(this + 1204); ++j )
      {
        v2 = this + 3 * j + 1205;
        *v2 = *(this + 3 * j + 1208);
        v2[1] = *(this + 3 * j + 1209);
        v2[2] = *(this + 3 * j + 1210);
      }
      if ( *(this + 1855) == i )
        *(this + 1855) = -1;
      if ( *(this + 1856) == i )
        *(this + 1856) = -1;
      if ( *(this + 1874) == i )
        *(this + 1874) = -1;
      if ( *(this + 1855) > i )
        --*(this + 1855);
      if ( *(this + 1856) > i )
        --*(this + 1856);
      result = this;
      if ( *(this + 1874) > i )
      {
        result = (_DWORD *)(*(this + 1874) - 1);
        *(this + 1874) = result;
      }
      return result;
    }
    result = (_DWORD *)(i + 1);
  }
  return result;
}

