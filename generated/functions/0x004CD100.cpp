// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD100 rf_particle_allocate_and_initialize
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Direct VBM prototype radius copiedunchanged from+0x18 to live+0x38; life+0x28 to live+0x34; bitmap+0x2C tolive+0x48, framecount short+0x30 tolive+0x4C, colors+0x34/+0x38, flags+0x3C. Agezero; random_orientbit0x200 consumesone random range[0,2pi]. VBM caller passes parent-1,emitter0 andresolvedroom; do not route through emitter spawn sampling (extra randomdraws/radius/lifefloors).
char **__cdecl rf_particle_allocate_and_initialize(int a1, float *source, int a3, int a4, int a5, char **a6, int a7)
{
  char **result; // eax
  double v8; // st7
  float v9[3]; // [esp+8h] [ebp-2Ch] BYREF
  float v10[3]; // [esp+14h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-14h] BYREF
  char **v12; // [esp+2Ch] [ebp-8h]
  char *v13; // [esp+30h] [ebp-4h]

  result = (char **)((char *)&unk_866600 + 252 * a1);
  v12 = result;
  if ( result[2] != (char *)(result + 2) )
  {
    v13 = v12[2];
    **((_DWORD **)v13 + 1) = *(_DWORD *)v13;
    *(_DWORD *)(*(_DWORD *)v13 + 4) = *((_DWORD *)v13 + 1);
    *(_DWORD *)v13 = 0;
    *((_DWORD *)v13 + 1) = 0;
    if ( a7 )
    {
      *((_DWORD *)v13 + 1) = *(_DWORD *)(a7 + 180);
      *(_DWORD *)v13 = a7 + 176;
      **(_DWORD **)(a7 + 180) = v13;
      *(_DWORD *)(a7 + 180) = v13;
    }
    else
    {
      *((_DWORD *)v13 + 1) = v12[33];
      *(_DWORD *)v13 = v12 + 32;
      *(_DWORD *)v12[33] = v13;
      v12[33] = v13;
    }
    v13[80] = a1;
    *((_DWORD *)v13 + 26) = a7;
    *((_DWORD *)v13 + 2) = a5;
    rf_vector_copy((float *)v13 + 3, copy_result, source);
    rf_vector_copy((float *)v13 + 27, v10, (const float *)v13 + 3);
    rf_vector_copy((float *)v13 + 6, v9, source + 3);
    *((float *)v13 + 14) = source[6];
    *((float *)v13 + 13) = source[10];
    *((float *)v13 + 15) = source[7];
    *((float *)v13 + 16) = source[8];
    *((float *)v13 + 17) = source[9] * 9.800000190734863;
    *((float *)v13 + 18) = source[11];
    *((_WORD *)v13 + 38) = *((_WORD *)source + 24);
    *((float *)v13 + 10) = source[13];
    *((float *)v13 + 11) = source[14];
    *((_DWORD *)v13 + 12) = *((_DWORD *)v13 + 10);
    *((float *)v13 + 22) = source[15];
    *((_WORD *)v13 + 39) = *((_WORD *)source + 32);
    *((float *)v13 + 23) = source[17];
    *((float *)v13 + 24) = source[18];
    *((_DWORD *)v13 + 25) = a3;
    *((float *)v13 + 9) = 0.0;
    *((_DWORD *)v13 + 22) |= 1u;
    if ( (*((_DWORD *)v13 + 22) & 0x200) != 0 )
    {
      v8 = rf_random_float_range(0.0, 6.2831855);
      *((float *)v13 + 21) = v8;
    }
    else
    {
      *((float *)v13 + 21) = 0.0;
    }
    ++v12[62];
    result = (char **)v13;
    if ( !*((_DWORD *)v13 + 25) )
    {
      result = (char **)v13;
      *((_DWORD *)v13 + 22) &= ~0x10u;
    }
    if ( a6 )
      *a6 = v13;
  }
  return result;
}

