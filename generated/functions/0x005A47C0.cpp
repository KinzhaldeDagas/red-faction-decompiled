// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A47C0 rf_cubic_bezier_set_embedded_controls
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall64-byte object and4 vector pointers. Copies3 floats from each to embedded points+0,+12,+24,+36,then resets pointer table+48..60 to embedded points,returns this. No pointer/null validation or allocation; replaces any previous pointer-table bindings.
int __thiscall rf_cubic_bezier_set_embedded_controls(int this, float *source, float *a3, float *a4, float *a5)
{
  float v7[3]; // [esp+4h] [ebp-30h] BYREF
  float v8[3]; // [esp+10h] [ebp-24h] BYREF
  float v9[3]; // [esp+1Ch] [ebp-18h] BYREF
  float copy_result[3]; // [esp+28h] [ebp-Ch] BYREF

  rf_vector_copy((float *)this, copy_result, source);
  rf_vector_copy((float *)(this + 12), v9, a3);
  rf_vector_copy((float *)(this + 24), v8, a4);
  rf_vector_copy((float *)(this + 36), v7, a5);
  *(_DWORD *)(this + 48) = this;
  *(_DWORD *)(this + 52) = this + 12;
  *(_DWORD *)(this + 56) = this + 24;
  *(_DWORD *)(this + 60) = this + 36;
  return this;
}

