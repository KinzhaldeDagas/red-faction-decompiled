// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558CC0 rf_vector_fast_length
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] FAST approximate length: sort absolute x/y/z descending as L>=M>=S; store float W=M/4+S/8; return float(L+W+W/2). Equivalent exact-real weights L+3M/8+3S/16, but preserve the intermediate float store. This makes mover sphere occupancy non-Euclidean; diagonal boundaries differ from sqrt(dot).
double __thiscall rf_vector_fast_length(float *this)
{
  float v2; // [esp+4h] [ebp-20h]
  float v3; // [esp+8h] [ebp-1Ch]
  float v4; // [esp+Ch] [ebp-18h]
  float v6; // [esp+14h] [ebp-10h]
  float v7; // [esp+18h] [ebp-Ch]
  float v8; // [esp+1Ch] [ebp-8h]
  float v9; // [esp+20h] [ebp-4h]

  if ( *this >= 0.0 )
    v8 = *this;
  else
    v8 = -*this;
  if ( *(this + 1) >= 0.0 )
    v7 = *(this + 1);
  else
    v7 = -*(this + 1);
  if ( *(this + 2) >= 0.0 )
    v6 = *(this + 2);
  else
    v6 = -*(this + 2);
  if ( v7 > (double)v8 )
  {
    v4 = v8;
    v8 = v7;
    v7 = v4;
  }
  if ( v6 > (double)v7 )
  {
    v3 = v7;
    v7 = v6;
    v6 = v3;
    if ( v7 > (double)v8 )
    {
      v2 = v8;
      v8 = v7;
      v7 = v2;
    }
  }
  v9 = v7 / 4.0 + v6 / 8.0;
  return (float)(v8 + v9 + v9 / 2.0);
}

