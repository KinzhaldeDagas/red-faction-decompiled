// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DEC70 rf_renderer_draw_face_batch_alternate_backend_102
// UNREALRED VERIFIED [impact-callbacks-20261028]: Packs two render states(1,2,3,0,4,0) and(1,2,3,3,4,0), selects second if either trailing byteargument nonzero. For each face walks circular vertex loop+64. If vertex cached stamp+24<solid/context+860, writes current stamp, projects vertex via0x5817B0, stores returned clipcode+28 and copies projected vec3 to vertex+12. Aggregates clipcode AND/OR; AND nonzero skips face. For face passing ANDclipcode test lazily loads fallback blahblah.tga(global0x664A4C) when-1, uses face bitmap+48 if>=0, sets state selector0 and calls0x5D4390(solid,face,packedstate,bitmap,ORclipcode). Success increments0xA4205C and ORs temporary faceflags+40 bit0x80000000. After processing clears that temporary bit on EVERY input face. Room argument unused. Returns incidental AL loop value; no texture-release or state restoration here.
char __cdecl rf_renderer_draw_face_batch_alternate_backend_102(int a1, int a2, int a3, int a4, char a5, char a6)
{
  int *v6; // eax
  unsigned __int8 v7; // al
  int v9; // [esp+0h] [ebp-6Ch]
  float copy_result[3]; // [esp+4h] [ebp-68h] BYREF
  char v11; // [esp+13h] [ebp-59h]
  int v12; // [esp+14h] [ebp-58h]
  float source[12]; // [esp+18h] [ebp-54h] BYREF
  float *v14; // [esp+48h] [ebp-24h]
  int j; // [esp+4Ch] [ebp-20h]
  int v16; // [esp+50h] [ebp-1Ch]
  int v17; // [esp+54h] [ebp-18h]
  int v18; // [esp+58h] [ebp-14h] BYREF
  int v19; // [esp+5Ch] [ebp-10h] BYREF
  int *v20; // [esp+60h] [ebp-Ch]
  _DWORD *v21; // [esp+64h] [ebp-8h]
  int i; // [esp+68h] [ebp-4h]

  rf_render_state_pack(&v19, 1, 2, 3, 0, 4, 0);
  rf_render_state_pack(&v18, 1, 2, 3, 3, 4, 0);
  LOBYTE(v6) = a5;
  if ( a5 || a6 )
  {
    v20 = &v18;
  }
  else
  {
    v6 = &v19;
    v20 = &v19;
  }
  for ( i = 0; i < a3; ++i )
  {
    v21 = *(_DWORD **)(a4 + 4 * i);
    v16 = -1;
    v17 = 0;
    LOBYTE(v6) = (_BYTE)v21;
    for ( j = v21[16]; j; j = v9 )
    {
      v14 = *(float **)j;
      if ( *((_DWORD *)v14 + 6) < *(_DWORD *)(a1 + 860) )
      {
        v14[6] = *(float *)(a1 + 860);
        rf_vector_prefix_construct_noop(source);
        v7 = rf_renderer_transform_world_point_backend_wrapper((int)source, v14);
        *((_DWORD *)v14 + 7) = v7;
        rf_vector_copy(v14 + 3, copy_result, source);
      }
      v16 &= *((_DWORD *)v14 + 7);
      v17 |= *((_DWORD *)v14 + 7);
      LOBYTE(v6) = j;
      if ( *(_DWORD *)(j + 20) == v21[16] )
      {
        v9 = 0;
      }
      else
      {
        LOBYTE(v6) = j;
        v9 = *(_DWORD *)(j + 20);
      }
    }
    if ( !v16 )
    {
      if ( dword_664A4C == -1 )
        dword_664A4C = rf_bitmap_load_with_optional_mipmap_generation("blahblah.tga", (void *)0xFFFFFFFF, 1);
      v12 = dword_664A4C;
      if ( (int)v21[12] > -1 )
        v12 = v21[12];
      rf_renderer_set_auxiliary_mode_clamped_0_16(0);
      LOBYTE(v6) = rf_renderer_draw_single_face_backend_102(a1, (int)v21, *v20, v12, v17);
      v11 = (char)v6;
      if ( (_BYTE)v6 )
      {
        ++*(_DWORD *)&byte_98967F[756189];
        LOBYTE(v6) = (_BYTE)v21;
        v21[10] |= 0x80000000;
      }
    }
  }
  for ( i = 0; i < a3; ++i )
  {
    *(_DWORD *)(*(_DWORD *)(a4 + 4 * i) + 40) &= ~0x80000000;
    LOBYTE(v6) = i + 1;
  }
  return (char)v6;
}

