// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4DB0 rf_catmull_rom32_evaluate_position
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall padded-point object,destination,float value. Count<=0 copies global vector0x17F10B0. If integer TRUNC(value)>=count,copies last real point slot=count. Otherwise k=floor(value),t=value-k; combines slots k,k+1,k+2,k+3 with Catmull-Rom weights(-.5t^3+t^2-.5t),(1.5t^3-2.5t^2+1),(-1.5t^3+2t^2+.5t),(.5t^3-.5t^2). No negative-value or lower bound clamp; reads four slots even when a weight is0. Near upper end can read beyond initialized padding; count30,k29 reaches slot32(count field/adjacent storage). No null/alias/finite-value check. Interpolating branch returns this,endpoint/fallback branches vector-copy result; output is destination.
const float *__thiscall rf_catmull_rom32_evaluate_position(const float *this, float *destination, float value)
{
  int v4; // eax
  float v6[3]; // [esp+8h] [ebp-38h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-2Ch] BYREF
  float v8; // [esp+20h] [ebp-20h]
  int v9; // [esp+24h] [ebp-1Ch]
  float v10; // [esp+28h] [ebp-18h]
  int v11; // [esp+2Ch] [ebp-14h]
  float v12; // [esp+30h] [ebp-10h]
  float v13; // [esp+34h] [ebp-Ch]
  float v14; // [esp+38h] [ebp-8h]
  float v15; // [esp+3Ch] [ebp-4h]
  float v16; // [esp+4Ch] [ebp+Ch]

  v11 = (int)value;
  if ( *((int *)this + 96) <= 0 )
    return rf_vector_copy(destination, copy_result, flt_17F10B0);
  if ( v11 >= *((_DWORD *)this + 96) )
    return rf_vector_copy(destination, v6, this + 3 * *((_DWORD *)this + 96));
  v4 = (int)rf_floor_float(value);
  v16 = value - (double)v4;
  v8 = v16 * v16;
  v14 = v8 * v16;
  v9 = v4 + 1;
  v15 = v14 * -0.5 + v8 - v16 * 0.5;
  v12 = v14 * 1.5 + v8 * -2.5 + 1.0;
  v10 = v14 * -1.5 + v8 * 2.0 + v16 * 0.5;
  v13 = v14 * 0.5 - v8 * 0.5;
  *destination = v15 * *(this + 3 * v4)
               + v12 * *(this + 3 * v4 + 3)
               + v10 * *(this + 3 * v4 + 6)
               + v13 * *(this + 3 * v4 + 9);
  destination[1] = v15 * *(this + 3 * v9 - 2)
                 + v12 * *(this + 3 * v9 + 1)
                 + v10 * *(this + 3 * v9 + 4)
                 + v13 * *(this + 3 * v9 + 7);
  destination[2] = v15 * *(this + 3 * v9 - 1)
                 + v12 * *(this + 3 * v9 + 2)
                 + v10 * *(this + 3 * v9 + 5)
                 + v13 * *(this + 3 * v9 + 8);
  return this;
}

