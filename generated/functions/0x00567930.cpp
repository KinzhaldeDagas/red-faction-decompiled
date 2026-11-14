// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567930 rf_float_format_decimal_to_buffer_partial_limit
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(buffer,value,capacity),returns stored character count. NULL buffer0;otherwise writes initialNUL even if capacity<=0. Negative value writes minus+NUL BEFORE capacity check. Exact0 writes literal0.0 only if capacity>=4,else leaves empty/returns0. Nonzero magnitude builds integer digits by floor with float powers10,then decimal point;integer residual0 appends one0,positive residual emits up toSIX fractional digits by repeated floor/subtraction,not rounding. Several prefix stores occur before limit checks:subunit magnitude appends0 anddot without earlier capacity test. Digits appended via strlen/NUL copies;limit generally checked after stores. No NaN/Inf handling,positive infinity can keep
// integer-scale loop running. Not snprintf or precision-argument formatter.
int __cdecl rf_float_format_decimal_to_buffer_partial_limit(char *buffer, float value, int capacity)
{
  float v4; // [esp+34h] [ebp-60h]
  float v5; // [esp+68h] [ebp-2Ch]
  float v6; // [esp+6Ch] [ebp-28h]
  float v7; // [esp+70h] [ebp-24h]
  float v8; // [esp+74h] [ebp-20h]
  int v9; // [esp+78h] [ebp-1Ch]
  int v10; // [esp+78h] [ebp-1Ch]
  float v11; // [esp+7Ch] [ebp-18h]
  float v12; // [esp+80h] [ebp-14h]
  float v13; // [esp+80h] [ebp-14h]
  int v14; // [esp+84h] [ebp-10h]
  int i; // [esp+88h] [ebp-Ch]
  int j; // [esp+88h] [ebp-Ch]
  float v17; // [esp+8Ch] [ebp-8h]
  float v18; // [esp+8Ch] [ebp-8h]
  float v19; // [esp+8Ch] [ebp-8h]
  char v20[4]; // [esp+90h] [ebp-4h] BYREF

  v9 = 0;
  v20[0] = 0;
  v20[1] = 0;
  if ( !buffer )
    return 0;
  *buffer = 0;
  v8 = fabs(value);
  if ( value != v8 )
  {
    *(_WORD *)buffer = 45;
    v9 = 1;
    if ( capacity - 1 <= 1 )
      return 1;
  }
  if ( value == 0.0 )
  {
    if ( capacity >= 4 )
    {
      *(_DWORD *)buffer = 3157552;
      return 3;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v7 = fabs(value);
    v11 = v7;
    if ( v7 < 1.0 )
    {
      *(_WORD *)&buffer[strlen(buffer)] = 48;
      ++v9;
    }
    else
    {
      v6 = fabs(value);
      v17 = v6;
      v14 = -1;
      v12 = 0.1;
      while ( v17 >= 1.0 )
      {
        ++v14;
        v12 = v12 * 10.0;
        v17 = v17 / 10.0;
      }
      for ( i = v14; i >= 0; --i )
      {
        v5 = v11 / v12;
        v18 = (float)(int)rf_floor_float(v5);
        v20[0] = (int)v18 + 48;
        qmemcpy(&buffer[strlen(buffer)], v20, &v20[strlen(v20) + 1] - v20);
        if ( ++v9 >= capacity - 1 )
          return v9;
        v11 = v11 - v18 * v12;
        v12 = v12 * 0.1000000014901161;
      }
    }
    *(_WORD *)&buffer[strlen(buffer)] = 46;
    v10 = v9 + 1;
    if ( v10 >= capacity - 1 )
      return v10;
    if ( v11 <= 0.0 )
    {
      *(_WORD *)&buffer[strlen(buffer)] = 48;
      if ( ++v10 >= capacity - 1 )
        return v10;
    }
    else
    {
      v13 = 10.0;
      for ( j = 1; j < 7; ++j )
      {
        v4 = v11 * v13;
        v19 = (float)(int)rf_floor_float(v4);
        v20[0] = (int)v19 + 48;
        qmemcpy(&buffer[strlen(buffer)], v20, &v20[strlen(v20) + 1] - v20);
        if ( ++v10 >= capacity - 1 )
          return v10;
        v11 = v11 - v19 / v13;
        v13 = v13 * 10.0;
      }
    }
    return v10;
  }
}

