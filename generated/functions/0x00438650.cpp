// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438650 rf_entity_request_body_state
// UNREALRED VERIFIED [death-animation-decode]: Requests one of 23 body states with slot-0 fallback and midpoint-preserving transition retargeting.
unsigned int __cdecl rf_entity_request_body_state(int a1, unsigned int a2, float a3)
{
  unsigned int result; // eax
  double v4; // st7
  float v5; // [esp+0h] [ebp-4h]

  if ( a2 > 0x16 || *(_DWORD *)(a1 + 16 * a2 + 2276) == -1 )
    a2 = 0;
  result = a1;
  if ( *(_DWORD *)(a1 + 16 * a2 + 2276) != -1 )
  {
    if ( *(float *)(a1 + 5012) == 0.0 )
    {
      *(_DWORD *)(a1 + 5008) = a2;
      *(float *)(a1 + 5012) = a3;
      *(float *)(a1 + 5016) = 0.0;
      return a2;
    }
    else
    {
      v5 = *(float *)(a1 + 5016) / *(float *)(a1 + 5012);
      if ( v5 <= 0.5 )
      {
        v4 = a3 * v5;
      }
      else
      {
        *(_DWORD *)(a1 + 5004) = *(_DWORD *)(a1 + 5008);
        v4 = (1.0 - v5) * a3;
      }
      *(float *)(a1 + 5016) = v4;
      *(_DWORD *)(a1 + 5008) = a2;
      *(float *)(a1 + 5012) = a3;
      return a1;
    }
  }
  return result;
}

