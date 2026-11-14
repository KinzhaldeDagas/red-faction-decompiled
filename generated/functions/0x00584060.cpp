// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584060 rf_short_quaternion_interpolate_wrapped
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl(destination s16[4],sourceA,sourceB,float t). While t<0 adds1,while t>1 subtracts1;not clamp,fmod or guard for infinity(nonterminating) or NaN. Constructs temporary;computes WRAPPED16 componentwise A-B and A+B,squared scaled dots,chooses -B when norm(A+B)<=norm(A-B),otherwiseB. Dot(A,chosenB) storedfloat;NaN dot copiesA. Dot+1<=~1e-6 uses sine half-pi weights and orthogonal vector(-B.y,B.x,-B.w,B.z). Otherwise if1-dot>~1e-6 uses angle=acos(dot),weights sin((1-t)*angle)/sin(angle) and sin(t*angle)/sin(angle);near-identical branch sets weights0 and1 (copies chosenB even when t0),not linear blend. Converts weighted float components by truncate-to-int then stores16bits;no saturation/renormalization. Every non-NaN branch forces destination.w=1 if computedw0. Return inconsistent
// coordinate/pointer,not status. Arithmetic/spherical formulas describe exact implementation,not a claim of robust general SLERP.
int __cdecl rf_short_quaternion_interpolate_wrapped(__int16 *a1, __int16 *a2, _WORD *a3, float a4)
{
  __int16 *v4; // eax
  __int16 *v5; // eax
  _WORD *v6; // eax
  int result; // eax
  double v8; // st7
  double v9; // st7
  __int16 *X_4; // [esp+4h] [ebp-A0h]
  __int16 *X_4a; // [esp+4h] [ebp-A0h]
  float v12; // [esp+28h] [ebp-7Ch]
  float v13; // [esp+2Ch] [ebp-78h]
  float v14; // [esp+50h] [ebp-54h]
  float v15; // [esp+54h] [ebp-50h]
  _WORD v16[4]; // [esp+58h] [ebp-4Ch] BYREF
  _WORD v17[4]; // [esp+60h] [ebp-44h] BYREF
  _WORD v18[4]; // [esp+68h] [ebp-3Ch] BYREF
  _WORD v19[4]; // [esp+70h] [ebp-34h] BYREF
  _WORD v20[4]; // [esp+78h] [ebp-2Ch] BYREF
  float v21; // [esp+80h] [ebp-24h]
  float v22; // [esp+84h] [ebp-20h]
  float v23; // [esp+88h] [ebp-1Ch]
  float v24; // [esp+8Ch] [ebp-18h]
  float v25; // [esp+90h] [ebp-14h]
  float v26; // [esp+94h] [ebp-10h]
  __int16 v27; // [esp+98h] [ebp-Ch] BYREF
  __int16 v28; // [esp+9Ah] [ebp-Ah]
  __int16 v29; // [esp+9Ch] [ebp-8h]
  __int16 v30; // [esp+9Eh] [ebp-6h]
  float v31; // [esp+A0h] [ebp-4h]

  while ( a4 < 0.0 )
    a4 = a4 + 1.0;
  while ( a4 > 1.0 )
    a4 = a4 - 1.0;
  rf_short_quaternion_construct_0001(&v27);
  X_4 = rf_short_quaternion_subtract_to_destination(a2, v20, a3);
  v4 = rf_short_quaternion_subtract_to_destination(a2, v19, a3);
  v26 = rf_short_quaternion_dot_scaled(v4, X_4);
  X_4a = rf_short_quaternion_add_to_destination(a2, v18, a3);
  v5 = rf_short_quaternion_add_to_destination(a2, v17, a3);
  v23 = rf_short_quaternion_dot_scaled(v5, X_4a);
  if ( v23 <= (double)v26 )
  {
    v6 = rf_short_quaternion_negate_to_destination(a3, v16);
    rf_short_quaternion_copy_words_return_this(&v27, v6);
  }
  else
  {
    rf_short_quaternion_copy_words_return_this(&v27, a3);
  }
  v31 = rf_short_quaternion_dot_scaled(a2, &v27);
  if ( _isnan(v31) )
    return (int)rf_short_quaternion_copy_words_return_this(a1, a2);
  if ( v31 + 1.0 <= 0.0000009999999974752427 )
  {
    v13 = (1.0 - a4) * 1.570796370506287;
    v24 = rf_sin_float(v13);
    v12 = a4 * 1.570796370506287;
    v25 = rf_sin_float(v12);
    *a1 = -v28;
    a1[1] = v27;
    a1[2] = -v30;
    a1[3] = v29;
    *a1 = (int)((double)*a2 * v24 + (double)*a1 * v25);
    a1[1] = (int)((double)a2[1] * v24 + (double)a1[1] * v25);
    a1[2] = (int)((double)a2[2] * v24 + (double)a1[2] * v25);
    a1[3] = (int)((double)a2[3] * v24 + (double)a1[3] * v25);
    result = a1[3];
    if ( !a1[3] )
      a1[3] = 1;
  }
  else
  {
    if ( 1.0 - v31 > 0.0000009999999974752427 )
    {
      v21 = rf_acos_float(v31);
      v22 = 1.0 / rf_sin_float(v21);
      v15 = (1.0 - a4) * v21;
      v8 = rf_sin_float(v15);
      v24 = v8 * v22;
      v14 = a4 * v21;
      v9 = rf_sin_float(v14);
      v25 = v9 * v22;
    }
    else
    {
      v24 = 0.0;
      v25 = 1.0;
    }
    *a1 = (int)((double)*a2 * v24 + (double)v27 * v25);
    a1[1] = (int)((double)a2[1] * v24 + (double)v28 * v25);
    a1[2] = (int)((double)a2[2] * v24 + (double)v29 * v25);
    a1[3] = (int)((double)a2[3] * v24 + (double)v30 * v25);
    result = (int)a1;
    if ( !a1[3] )
    {
      result = (int)a1;
      a1[3] = 1;
    }
  }
  return result;
}

