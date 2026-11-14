// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B3570 rf_motion_samples_locate_time_segment
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX buffer plus stack(queryWORD,outIndexDWORD*,outFractionF32*,outCurveParameterF32*),RET16. Native time difference D(q,s) for zero-extended16-bit values: if65535-q<5000 AND s<5000 ->q+s-65535;else if65535-s<5000 AND q<5000 ->q+65535-s;else q-s. This is ASYMMETRIC and uses65535,not ordinary signed modular subtraction. If D(query,timestamps1280[0])<0,returns0 BEFORE modifying any outputs. Otherwise index=0;while index!=count1332-1,stops at first interval whose D(query,t[index])>=0 AND D(query,t[index+1])<=0,else increments index. No own positive-count/capacity/monotonicity guard. At last index sets fraction0,otherwise fraction=float(D(query,t[index])/D(t[index+1],t[index])) with
// integer differences converted through x87;zero denominator gives0. Sets curveParameter=float(index+storedFraction),returns1EAX. Does not clamp fraction or parameter,handle finite/NaN separately,initialize sample data,or report extrapolation separately. Repeated XOR/JNZ pairs in disassembly are never-taken branches,not retries.
int __thiscall rf_motion_samples_locate_time_segment(int this, unsigned __int16 a2, int *a3, float *a4, float *a5)
{
  int v6; // [esp+4h] [ebp-8h]
  int v7; // [esp+4h] [ebp-8h]
  int v8; // [esp+8h] [ebp-4h]
  int v9; // [esp+8h] [ebp-4h]
  int v10; // [esp+8h] [ebp-4h]

  if ( 0xFFFF - a2 >= 5000 || *(unsigned __int16 *)(this + 1280) >= 0x1388u )
  {
    if ( 0xFFFF - *(unsigned __int16 *)(this + 1280) >= 5000 || a2 >= 0x1388u )
      v8 = a2 - *(unsigned __int16 *)(this + 1280);
    else
      v8 = a2 + 0xFFFF - *(unsigned __int16 *)(this + 1280);
  }
  else
  {
    v8 = *(unsigned __int16 *)(this + 1280) + a2 - 0xFFFF;
  }
  if ( v8 < 0 )
    return 0;
  for ( *a3 = 0; *a3 != *(_DWORD *)(this + 1332) - 1; ++*a3 )
  {
    if ( 0xFFFF - a2 >= 5000 || *(unsigned __int16 *)(this + 2 * *a3 + 1280) >= 0x1388u )
      v9 = 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1280) >= 5000 || a2 >= 0x1388u
         ? a2 - *(unsigned __int16 *)(this + 2 * *a3 + 1280)
         : a2 + 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1280);
    else
      v9 = *(unsigned __int16 *)(this + 2 * *a3 + 1280) + a2 - 0xFFFF;
    if ( 0xFFFF - a2 >= 5000 || *(unsigned __int16 *)(this + 2 * *a3 + 1282) >= 0x1388u )
      v6 = 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1282) >= 5000 || a2 >= 0x1388u
         ? a2 - *(unsigned __int16 *)(this + 2 * *a3 + 1282)
         : a2 + 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1282);
    else
      v6 = *(unsigned __int16 *)(this + 2 * *a3 + 1282) + a2 - 0xFFFF;
    if ( v9 >= 0 && v6 <= 0 )
      break;
  }
  if ( *a3 == *(_DWORD *)(this + 1332) - 1 )
  {
    *a4 = 0.0;
  }
  else
  {
    if ( 0xFFFF - a2 >= 5000 || *(unsigned __int16 *)(this + 2 * *a3 + 1280) >= 0x1388u )
    {
      if ( 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1280) >= 5000 || a2 >= 0x1388u )
        v10 = a2 - *(unsigned __int16 *)(this + 2 * *a3 + 1280);
      else
        v10 = a2 + 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1280);
    }
    else
    {
      v10 = *(unsigned __int16 *)(this + 2 * *a3 + 1280) + a2 - 0xFFFF;
    }
    if ( 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1282) >= 5000
      || *(unsigned __int16 *)(this + 2 * *a3 + 1280) >= 0x1388u )
    {
      if ( 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1280) >= 5000
        || *(unsigned __int16 *)(this + 2 * *a3 + 1282) >= 0x1388u )
      {
        v7 = *(unsigned __int16 *)(this + 2 * *a3 + 1282) - *(unsigned __int16 *)(this + 2 * *a3 + 1280);
      }
      else
      {
        v7 = *(unsigned __int16 *)(this + 2 * *a3 + 1282) + 0xFFFF - *(unsigned __int16 *)(this + 2 * *a3 + 1280);
      }
    }
    else
    {
      v7 = *(unsigned __int16 *)(this + 2 * *a3 + 1280) + *(unsigned __int16 *)(this + 2 * *a3 + 1282) - 0xFFFF;
    }
    if ( v7 )
      *a4 = (double)v10 / (double)v7;
    else
      *a4 = 0.0;
  }
  *a5 = (double)*a3 + *a4;
  return 1;
}

