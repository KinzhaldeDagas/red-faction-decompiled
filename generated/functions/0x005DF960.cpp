// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF960 rf_clip_vertex48_copy_return_destination
// UNREALRED VERIFIED [renderer-mesh-20261028]: Copies complete48-byte vertex from stacksource into thisdestination: sixfloats0..23,fourbytes24..27,fourUVfloats28..43,and fourcolorbytes44..47. Returns destination. No ownership accounting; temporaryflag is copied unchanged,so copy does not allocate/release pool records.
int __thiscall rf_clip_vertex48_copy_return_destination(int this, float *source)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector_copy((float *)this, copy_result, source);
  *(float *)(this + 12) = source[3];
  *(float *)(this + 16) = source[4];
  *(float *)(this + 20) = source[5];
  *(_BYTE *)(this + 24) = *((_BYTE *)source + 24);
  *(_BYTE *)(this + 25) = *((_BYTE *)source + 25);
  *(_BYTE *)(this + 26) = *((_BYTE *)source + 26);
  *(_BYTE *)(this + 27) = *((_BYTE *)source + 27);
  *(float *)(this + 28) = source[7];
  *(float *)(this + 32) = source[8];
  *(float *)(this + 36) = source[9];
  *(float *)(this + 40) = source[10];
  *(_BYTE *)(this + 44) = *((_BYTE *)source + 44);
  *(_BYTE *)(this + 45) = *((_BYTE *)source + 45);
  *(_BYTE *)(this + 46) = *((_BYTE *)source + 46);
  *(_BYTE *)(this + 47) = *((_BYTE *)source + 47);
  return this;
}

