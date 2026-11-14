// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005357B0 rf_geomod_face_primary_uv_rebase
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Traverses face corner ring+64,accumulates primary U/V sums and FLOAT count;also computes minima but never uses them. Per axis average=sum/count. For average<0,offset=abs(int(floor(avg)));for average>1,offset=-abs(int(floor(avg)));for inclusive[0,1],offset0. Adds SAME integer-valued float offset to every corner primary UV. Not per-corner modulo:retains relative UV differences,and average EXACTLY1 remains1. Empty ring computes0/0,then no writes. Nonfinite/out-of-int-range conversion inherits helper/CPU behavior,no guard. Secondary UVs unchanged,return pointer incidental based on traversal;existing short description retained.
float *__thiscall rf_geomod_face_primary_uv_rebase(float *this)
{
  float *result; // eax
  float *v2; // [esp+4h] [ebp-4Ch]
  float v3; // [esp+8h] [ebp-48h]
  float v4; // [esp+10h] [ebp-40h]
  float v5; // [esp+18h] [ebp-38h]
  float v6; // [esp+20h] [ebp-30h]
  int v7; // [esp+28h] [ebp-28h]
  int i; // [esp+30h] [ebp-20h]
  float *j; // [esp+30h] [ebp-20h]
  float v11; // [esp+34h] [ebp-1Ch]
  float v12; // [esp+38h] [ebp-18h]
  float v13; // [esp+3Ch] [ebp-14h]
  float v14; // [esp+3Ch] [ebp-14h]
  float v15; // [esp+40h] [ebp-10h]
  float value; // [esp+40h] [ebp-10h]
  float v17; // [esp+44h] [ebp-Ch]
  float v18; // [esp+48h] [ebp-8h]
  float v19; // [esp+4Ch] [ebp-4h]

  v15 = 0.0;
  v13 = 0.0;
  v18 = 3.4028235e38;
  v19 = 3.4028235e38;
  v12 = 0.0;
  for ( i = *((_DWORD *)this + 16); i; i = v7 )
  {
    v15 = v15 + *(float *)(i + 4);
    v13 = v13 + *(float *)(i + 8);
    if ( v18 > (double)*(float *)(i + 4) )
      v18 = *(float *)(i + 4);
    if ( v19 > (double)*(float *)(i + 8) )
      v19 = *(float *)(i + 8);
    v12 = v12 + 1.0;
    if ( *(_DWORD *)(i + 20) == *((_DWORD *)this + 16) )
      v7 = 0;
    else
      v7 = *(_DWORD *)(i + 20);
  }
  value = v15 / v12;
  v14 = v13 / v12;
  v11 = 0.0;
  v17 = 0.0;
  if ( value >= 0.0 )
  {
    if ( value > 1.0 )
    {
      v5 = fabs((double)(int)rf_floor_float(value));
      v11 = -v5;
    }
  }
  else
  {
    v6 = fabs((double)(int)rf_floor_float(value));
    v11 = v6;
  }
  if ( v14 >= 0.0 )
  {
    if ( v14 > 1.0 )
    {
      v3 = fabs((double)(int)rf_floor_float(v14));
      v17 = -v3;
    }
  }
  else
  {
    v4 = fabs((double)(int)rf_floor_float(v14));
    v17 = v4;
  }
  result = *((float **)this + 16);
  for ( j = result; j; j = v2 )
  {
    j[1] = j[1] + v11;
    j[2] = j[2] + v17;
    result = this;
    if ( *((_DWORD *)j + 5) == *((_DWORD *)this + 16) )
    {
      v2 = nullptr;
    }
    else
    {
      result = *((float **)j + 5);
      v2 = result;
    }
  }
  return result;
}

