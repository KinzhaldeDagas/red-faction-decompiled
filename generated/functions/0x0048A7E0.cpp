// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A7E0 rf_mover_modify_first_key_travel_times
// UNREALRED VERIFIED [mission-mover-events-20261020] Mutates FIRST key forward/backward travel parameters at key+0x38/+0x3C. Operation true subtracts percentage/100 times the existing value; false adds it. Both results stored as float. No clamping, activation, angle/speed/elapsed reset or rotating-type test. Repeated/duplicate targets compound the changes.
int __cdecl rf_mover_modify_first_key_travel_times(int a1, char a2, float a3)
{
  int result; // eax
  double v4; // st7
  int v5; // [esp+0h] [ebp-4h]

  v5 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), 0);
  if ( a2 )
  {
    *(float *)(v5 + 56) = *(float *)(v5 + 56) - a3 / 100.0 * *(float *)(v5 + 56);
    result = v5;
    v4 = *(float *)(v5 + 60) - a3 / 100.0 * *(float *)(v5 + 60);
  }
  else
  {
    *(float *)(v5 + 56) = a3 / 100.0 * *(float *)(v5 + 56) + *(float *)(v5 + 56);
    result = v5;
    v4 = a3 / 100.0 * *(float *)(v5 + 60) + *(float *)(v5 + 60);
  }
  *(float *)(v5 + 60) = v4;
  return result;
}

