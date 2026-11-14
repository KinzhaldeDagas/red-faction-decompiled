// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587A60 rf_character_instance_set_bone_orientation_override
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Thiscall with48 stack argument bytes: node index, nine-float matrix BY VALUE, ancestor count, float falloff. For index>=base-character bone count reads mapping DWORD at base+4848+56*index WITHOUT subtracting bone count (preserve actual indexing). Writes instance override matrix at+5016+48*resolvedIndex, active byte+5052=1, weight+5056=1. Repeats ancestorCount times: weight*=falloff, follows primary-bone parent at base+148+76*index, writes same matrix/active byte and decayed weight. No index, root(-1), ancestor limit or falloff validation. No translation write; return register incidental.
int __thiscall rf_character_instance_set_bone_orientation_override(
        void *this,
        int a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        int a12,
        float a13)
{
  int result; // eax
  int i; // [esp+4h] [ebp-Ch]
  float v16; // [esp+8h] [ebp-8h]
  int v17; // [esp+Ch] [ebp-4h]

  v16 = 1.0;
  v17 = a2;
  if ( a2 >= *(_DWORD *)(*((_DWORD *)this + 1876) + 72) )
    v17 = *(_DWORD *)(*((_DWORD *)this + 1876) + 56 * a2 + 4848);
  *((_BYTE *)this + 48 * v17 + 5052) = 1;
  result = rf_matrix3_copy((float *)this + 12 * v17 + 1254, &a3);
  *((float *)this + 12 * v17 + 1264) = 1.0;
  for ( i = 0; i < a12; ++i )
  {
    v16 = v16 * a13;
    v17 = *(_DWORD *)(*((_DWORD *)this + 1876) + 76 * v17 + 148);
    *((_BYTE *)this + 48 * v17 + 5052) = 1;
    rf_matrix3_copy((float *)this + 12 * v17 + 1254, &a3);
    *((float *)this + 12 * v17 + 1264) = v16;
    result = i + 1;
  }
  return result;
}

