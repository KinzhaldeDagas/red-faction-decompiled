// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041EF60 rf_corpse_apply_explosive_damage
// UNREALRED VERIFIED [corpse-lifecycle-decode]: Accepts only verified damage type 3 explosive, subtracts corpse life, and removes it only below zero.
void __cdecl rf_corpse_apply_explosive_damage(int a1, float a2, int a3, int a4)
{
  if ( a4 == 3 )
  {
    *(float *)(a1 + 52) = *(float *)(a1 + 52) - a2;
    if ( *(float *)(a1 + 52) < 0.0 )
    {
      rf_disabled_seven_piece_debris_stub();
      rf_object_mark_for_deferred_delete(a1);
    }
  }
}

