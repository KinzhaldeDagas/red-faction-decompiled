// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00508240 rf_rail_trail_render_crossed_triangles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Lazy guard911C60 bits1/2 packs states911C5C=(2,2,3,2,1,0),911C58=(2,1,3,2,1,0); bits4/8 invoke no-op vector construction on two global3-vertex arrays911C34/911C10. Both actual draws use911C5C; second packed state remains unused in this body. Scans active circular ring911708 through+72 without unlinking. Per node t=F32(age+64 * DOUBLE1) for ANY nonzero multiplayer byte, else F32(age*DOUBLE1.25). Width=F32(t*DOUBLE0.1669999957084656+DOUBLE0.3330000042915344), alpha=FTOL((1-t)*DOUBLE255), narrowed LOW BYTE without clamp. Uses basis right+24 and up+36 times width. Two triangles each share apex node+0 and have base vertices node+12 +/- right*width and +/- up*width. UVs
// are(0.5,1),(1,0),(0,0). Color bytes128,255,255,alpha; submits each triangle with bitmap663A28,state911C5C through580490. No culling/lifetime/UID checks, billboard camera-facing calculation, texture-load validation, alpha clamp, resource teardown or state restoration. Shared global vertex scratch is overwritten per node.
void __cdecl rf_rail_trail_render_crossed_triangles()
{
  double v0; // st7
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // [esp+8h] [ebp-CCh]
  float v6[3]; // [esp+Ch] [ebp-C8h] BYREF
  float v7[3]; // [esp+18h] [ebp-BCh] BYREF
  float v8[3]; // [esp+24h] [ebp-B0h] BYREF
  float v9[3]; // [esp+30h] [ebp-A4h] BYREF
  float v10[3]; // [esp+3Ch] [ebp-98h] BYREF
  float v11[3]; // [esp+48h] [ebp-8Ch] BYREF
  float out_vector[3]; // [esp+54h] [ebp-80h] BYREF
  float v13[3]; // [esp+60h] [ebp-74h] BYREF
  float sum_result[3]; // [esp+6Ch] [ebp-68h] BYREF
  float copy_result[3]; // [esp+78h] [ebp-5Ch] BYREF
  float v16; // [esp+84h] [ebp-50h]
  float v17[6]; // [esp+88h] [ebp-4Ch] BYREF
  float scalar; // [esp+A0h] [ebp-34h]
  float scaled_result[3]; // [esp+A4h] [ebp-30h] BYREF
  float rhs[3]; // [esp+B0h] [ebp-24h] BYREF
  int v21; // [esp+BCh] [ebp-18h]
  float *source; // [esp+C0h] [ebp-14h]
  char v23[3]; // [esp+C4h] [ebp-10h] BYREF
  char v24; // [esp+C7h] [ebp-Dh]
  int v25; // [esp+D0h] [ebp-4h]

  if ( (dword_911C60[0] & 1) == 0 )
  {
    dword_911C60[0] |= 1u;
    rf_render_state_pack(&dword_911C5C, 2, 2, 3, 2, 1, 0);
    v25 = -1;
  }
  if ( (dword_911C60[0] & 2) == 0 )
  {
    dword_911C60[0] |= 2u;
    rf_render_state_pack(&dword_911C58, 2, 1, 3, 2, 1, 0);
    v25 = -1;
  }
  if ( (dword_911C60[0] & 4) == 0 )
  {
    dword_911C60[0] |= 4u;
    rf_vector_construct_no_unwind((char *)unk_911C34, 0xCu, 3, rf_vector3_default_construct_noop);
    v25 = -1;
  }
  if ( (dword_911C60[0] & 8) == 0 )
  {
    dword_911C60[0] |= 8u;
    rf_vector_construct_no_unwind((char *)unk_911C10, 0xCu, 3, rf_vector3_default_construct_noop);
    v25 = -1;
  }
  v23[0] = 0x80;
  v23[1] = -1;
  v23[2] = -1;
  v24 = 0;
  for ( source = (float *)unk_911708; source; source = v5 )
  {
    rf_vector_construct_no_unwind((char *)v17, 8u, 3, rf_vector3_default_construct_noop);
    if ( rf_multiplayer_runtime_mode )
      v0 = source[16] * 1.0;
    else
      v0 = source[16] * 1.25;
    v16 = v0;
    scalar = v16 * 0.1669999957084656 + 0.3330000042915344;
    v21 = (int)((1.0 - v16) * 255.0);
    rf_vector_multiply_scalar(source + 6, rhs, scalar);
    rf_vector_multiply_scalar(source + 9, scaled_result, scalar);
    rf_vector_copy(unk_911C34, copy_result, source);
    v1 = rf_vector_add(source + 3, sum_result, rhs);
    rf_vector_copy(unk_911C40, v13, v1);
    v2 = rf_vector_subtract(source + 3, out_vector, rhs);
    rf_vector_copy(unk_911C4C, v11, v2);
    rf_vector_copy(unk_911C10, v10, source);
    v3 = rf_vector_add(source + 3, v9, scaled_result);
    rf_vector_copy(unk_911C1C, v8, v3);
    v4 = rf_vector_subtract(source + 3, v7, scaled_result);
    rf_vector_copy(unk_911C28, v6, v4);
    v17[0] = 0.5;
    v17[1] = 1.0;
    v17[2] = 1.0;
    v17[3] = 0.0;
    v17[4] = 0.0;
    v17[5] = 0.0;
    v24 = v21;
    rf_renderer_submit_textured_world_polygon_color4_dispatch(
      dword_663A28,
      3,
      (int)unk_911C34,
      (int)v17,
      dword_911C5C,
      v23);
    rf_renderer_submit_textured_world_polygon_color4_dispatch(
      dword_663A28,
      3,
      (int)unk_911C10,
      (int)v17,
      dword_911C5C,
      v23);
    if ( *((_DWORD *)source + 18) == unk_911708 )
      v5 = nullptr;
    else
      v5 = *((float **)source + 18);
  }
}

