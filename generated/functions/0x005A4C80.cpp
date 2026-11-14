// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4C80 rf_catmull_rom32_set_points_with_end_padding
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall object,signed count,contiguous3-float points. Count>30 stores count field+384=0 and returns this without copying. Other counts stored unchanged; copies count points into slots1..count. Computes leading slot0=P1+0.1*(P1-P2) and trailing slot(count+1)=Pcount+0.1*(Pcount-P(count-1)). Does NOT reject count<2,so extrapolation may use stale/uninitialized or negative-index storage. No input pointer,overlap or allocation handling. Returns last vector-copy helper result on accepted branch.
float *__thiscall rf_catmull_rom32_set_points_with_end_padding(int this, int a2, int a3)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float v11[3]; // [esp+8h] [ebp-70h] BYREF
  float v12[3]; // [esp+14h] [ebp-64h] BYREF
  float v13[3]; // [esp+20h] [ebp-58h] BYREF
  float v14[3]; // [esp+2Ch] [ebp-4Ch] BYREF
  float v15[3]; // [esp+38h] [ebp-40h] BYREF
  float sum_result[3]; // [esp+44h] [ebp-34h] BYREF
  float scaled_result[3]; // [esp+50h] [ebp-28h] BYREF
  float out_vector[3]; // [esp+5Ch] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+68h] [ebp-10h] BYREF
  int i; // [esp+74h] [ebp-4h]

  if ( a2 <= 30 )
  {
    *(_DWORD *)(this + 384) = a2;
    for ( i = 0; i < a2; ++i )
      rf_vector_copy((float *)(this + 12 * (i + 1)), copy_result, (const float *)(a3 + 12 * i));
    v4 = rf_vector_subtract((const float *)(this + 12), out_vector, (const float *)(this + 24));
    v5 = rf_vector_multiply_scalar(v4, scaled_result, 0.1);
    v6 = rf_vector_add((const float *)(this + 12), sum_result, v5);
    rf_vector_copy((float *)this, v15, v6);
    v7 = rf_vector_subtract(
           (const float *)(this + 12 * *(_DWORD *)(this + 384)),
           v14,
           (const float *)(this + 12 * (*(_DWORD *)(this + 384) - 1)));
    v8 = rf_vector_multiply_scalar(v7, v13, 0.1);
    v9 = rf_vector_add((const float *)(this + 12 * *(_DWORD *)(this + 384)), v12, v8);
    return rf_vector_copy((float *)(this + 12 * (*(_DWORD *)(this + 384) + 1)), v11, v9);
  }
  else
  {
    *(_DWORD *)(this + 384) = 0;
    return (float *)this;
  }
}

