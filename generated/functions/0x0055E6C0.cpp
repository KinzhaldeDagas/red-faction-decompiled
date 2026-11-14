// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E6C0 rf_affine48_repack_transposed_rows_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): In-place12float permutation using scalar temporaries. New array=(old0,old3,old6,old9,old1,old4,old7,old10,old2,old5,old8,old11), converting four packed3float rows into three packed4float rows. Not rigid inverse or same-layout3x3 transpose; translation components become fourth column. Returns receiver, no value arithmetic.
float *__thiscall rf_affine48_repack_transposed_rows_in_place(float *this)
{
  float v2; // [esp+4h] [ebp-Ch]
  float v3; // [esp+4h] [ebp-Ch]
  float v4; // [esp+4h] [ebp-Ch]
  float v5; // [esp+4h] [ebp-Ch]
  float v6; // [esp+8h] [ebp-8h]
  float v7; // [esp+8h] [ebp-8h]
  float v8; // [esp+8h] [ebp-8h]
  float v9; // [esp+8h] [ebp-8h]

  v2 = *(this + 1);
  *(this + 1) = *(this + 3);
  v6 = *(this + 4);
  *(this + 4) = v2;
  v3 = *(this + 5);
  *(this + 5) = v6;
  v7 = *(this + 9);
  *(this + 9) = v3;
  *(this + 3) = v7;
  v4 = *(this + 2);
  *(this + 2) = *(this + 6);
  v8 = *(this + 8);
  *(this + 8) = v4;
  v5 = *(this + 10);
  *(this + 10) = v8;
  v9 = *(this + 7);
  *(this + 7) = v5;
  *(this + 6) = v9;
  return this;
}

