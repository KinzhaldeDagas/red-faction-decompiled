// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511D90 rf_projectile_apply_common_object_penetration
// UNREALRED VERIFIED [weapon-penetration-radius] Scales piercing damage, subtracts 0.2 times target common-object collision radius +0x180, and on positive power advances from contact by that same radius along normalized travel.
int __cdecl rf_projectile_apply_common_object_penetration(int a1, float *lhs, int a3, float *a4, _BYTE *a5)
{
  float sum_result[3]; // [esp+4h] [ebp-24h] BYREF
  float rhs[3]; // [esp+10h] [ebp-18h] BYREF
  float vector[3]; // [esp+1Ch] [ebp-Ch] BYREF

  if ( *(int *)(*(_DWORD *)(a1 + 660) + 612) < 0 )
  {
    *a4 = (*(float *)(a1 + 752) / *(float *)(*(_DWORD *)(a1 + 660) + 636) * *a4 + *a4) * 0.5;
    *a5 = 1;
    *(float *)(a1 + 752) = *(float *)(a1 + 752) - *(float *)(a3 + 384) * 0.2000000029802322;
    if ( *(float *)(a1 + 752) > 0.0 )
    {
      rf_vector3_normalized_copy_unchecked((float *)(a1 + 324), (int)vector);
      rf_vector_multiply_scalar(vector, rhs, *(float *)(a3 + 384));
      rf_vector_add(lhs, sum_result, rhs);
      rf_object_publish_position_and_bounds(a1, sum_result);
      *a5 = 0;
    }
    return 1;
  }
  else
  {
    *a5 = 1;
    return 0;
  }
}

