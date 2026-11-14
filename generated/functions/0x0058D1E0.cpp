// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058D1E0 rf_font_draw_text_world_oriented
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Arguments world anchor, orientation basis pointer, scalar scale, byte string, font ID, render mode. Selects explicit nonnegative ID without upper bound or default, checks selected pointer and ensures atlas. Captures current RGBA once. Each valid glyph forms four world corners around pen center using +/-0.5*glyphWidth*scale*basisRow0 and +/-0.5*fontHeight*scale*basisRow1. UVs come from atlas positions/dimensions; dispatches textured world quad via580490. Advances along basisRow0 by glyph advance*scale. Consecutive LF resets pen to original anchor minus lineCount*fontHeight*scale*basisRow1. Missing glyph is skipped WITHOUT advance; unlike screen draw it checks index>=0. No string-NULL, font-index, scale or UV-dimension guards. EAX is incidental (normally pointer to
// terminal NUL), not a stable allocation/result object.
char *__cdecl rf_font_draw_text_world_oriented(float *lhs, float *vector, float a3, char *a4, int a5, int a6)
{
  char *result; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  float *v21; // eax
  float scalar; // [esp+0h] [ebp-1A4h]
  float scalara; // [esp+0h] [ebp-1A4h]
  float v24; // [esp+Ch] [ebp-198h]
  float v25; // [esp+1Ch] [ebp-188h]
  float v26[3]; // [esp+20h] [ebp-184h] BYREF
  float v27[3]; // [esp+2Ch] [ebp-178h] BYREF
  float v28[3]; // [esp+38h] [ebp-16Ch] BYREF
  float v29[3]; // [esp+44h] [ebp-160h] BYREF
  float v30[3]; // [esp+50h] [ebp-154h] BYREF
  float v31[3]; // [esp+5Ch] [ebp-148h] BYREF
  float v32[3]; // [esp+68h] [ebp-13Ch] BYREF
  float v33[3]; // [esp+74h] [ebp-130h] BYREF
  float v34[3]; // [esp+80h] [ebp-124h] BYREF
  float v35[3]; // [esp+8Ch] [ebp-118h] BYREF
  float v36[3]; // [esp+98h] [ebp-10Ch] BYREF
  float v37[3]; // [esp+A4h] [ebp-100h] BYREF
  float v38[3]; // [esp+B0h] [ebp-F4h] BYREF
  float sum_result[3]; // [esp+BCh] [ebp-E8h] BYREF
  float v40[3]; // [esp+C8h] [ebp-DCh] BYREF
  float v41[3]; // [esp+D4h] [ebp-D0h] BYREF
  float out_vector[3]; // [esp+E0h] [ebp-C4h] BYREF
  float v43[3]; // [esp+ECh] [ebp-B8h] BYREF
  float v44[3]; // [esp+F8h] [ebp-ACh] BYREF
  float copy_result[3]; // [esp+104h] [ebp-A0h] BYREF
  float scaled_result[3]; // [esp+110h] [ebp-94h] BYREF
  float rhs[3]; // [esp+11Ch] [ebp-88h] BYREF
  float v48[3]; // [esp+128h] [ebp-7Ch] BYREF
  float v49[3]; // [esp+134h] [ebp-70h] BYREF
  float v50[3]; // [esp+140h] [ebp-64h] BYREF
  float v51[3]; // [esp+14Ch] [ebp-58h] BYREF
  float v52; // [esp+158h] [ebp-4Ch] BYREF
  float v53; // [esp+15Ch] [ebp-48h]
  float v54; // [esp+160h] [ebp-44h]
  float v55; // [esp+164h] [ebp-40h]
  float v56; // [esp+168h] [ebp-3Ch]
  float v57; // [esp+16Ch] [ebp-38h]
  float v58; // [esp+170h] [ebp-34h]
  float v59; // [esp+174h] [ebp-30h]
  int v60; // [esp+178h] [ebp-2Ch] BYREF
  float v61[3]; // [esp+17Ch] [ebp-28h] BYREF
  int v62; // [esp+188h] [ebp-1Ch]
  int v63; // [esp+18Ch] [ebp-18h] BYREF
  char v64[4]; // [esp+190h] [ebp-14h] BYREF
  int v65; // [esp+194h] [ebp-10h]
  float destination[3]; // [esp+198h] [ebp-Ch] BYREF

  v65 = 0;
  result = (char *)rf_vector3_default_construct_noop(destination);
  if ( a5 >= 0 )
  {
    dword_193BB9C = (int)&unk_193B688 + 108 * a5;
  }
  else
  {
    result = (char *)unk_193BBA0;
    dword_193BB9C = unk_193BBA0;
  }
  if ( dword_193BB9C )
  {
    if ( *(int *)(dword_193BB9C + 84) >= 0
      || (result = (char *)rf_font_ensure_atlas_bitmap(dword_193BB9C), *(int *)(dword_193BB9C + 84) >= 0) )
    {
      v25 = (double)*(int *)(dword_193BB9C + 52) * 0.5;
      v7 = rf_vector_multiply_scalar(vector + 3, scaled_result, v25);
      rf_vector_multiply_scalar(v7, v61, a3);
      rf_vector_copy(destination, copy_result, lhs);
      v64[0] = rf_render_current_red;
      v64[1] = rf_render_current_green;
      v64[2] = rf_render_current_blue;
      v64[3] = rf_render_current_alpha;
      while ( 1 )
      {
        rf_vector_construct_no_unwind((char *)v48, 0xCu, 4, rf_vector3_default_construct_noop);
        rf_vector_construct_no_unwind((char *)&v52, 8u, 4, rf_vector3_default_construct_noop);
        while ( *a4 == 10 )
        {
          ++a4;
          scalar = (float)(++v65 * *(_DWORD *)(dword_193BB9C + 52));
          v8 = rf_vector_multiply_scalar(vector + 3, v44, scalar);
          v9 = rf_vector_multiply_scalar(v8, v43, a3);
          v10 = rf_vector_subtract(lhs, out_vector, v9);
          rf_vector_copy(destination, v41, v10);
        }
        result = a4;
        if ( !*a4 )
          break;
        v62 = rf_font_lookup_glyph_width_and_advance(*a4, a4[1], &v60, &v63);
        ++a4;
        if ( v62 >= 0 )
        {
          v52 = (double)*(int *)(*(_DWORD *)(dword_193BB9C + 96) + 4 * v62) / (double)*(int *)(dword_193BB9C + 88);
          v53 = (double)*(int *)(*(_DWORD *)(dword_193BB9C + 100) + 4 * v62) / (double)*(int *)(dword_193BB9C + 92);
          v54 = (double)(v60 + *(_DWORD *)(*(_DWORD *)(dword_193BB9C + 96) + 4 * v62))
              / (double)*(int *)(dword_193BB9C + 88);
          v55 = v53;
          v56 = v54;
          v57 = (double)(*(_DWORD *)(dword_193BB9C + 52) + *(_DWORD *)(*(_DWORD *)(dword_193BB9C + 100) + 4 * v62))
              / (double)*(int *)(dword_193BB9C + 92);
          v58 = v52;
          v59 = v57;
          v24 = (double)v60 * 0.5;
          v11 = rf_vector_multiply_scalar(vector, v40, v24);
          rf_vector_multiply_scalar(v11, rhs, a3);
          v12 = rf_vector_add(destination, sum_result, v61);
          v13 = rf_vector_subtract(v12, v38, rhs);
          rf_vector_copy(v48, v37, v13);
          v14 = rf_vector_add(destination, v36, v61);
          v15 = rf_vector_add(v14, v35, rhs);
          rf_vector_copy(v49, v34, v15);
          v16 = rf_vector_subtract(destination, v33, v61);
          v17 = rf_vector_add(v16, v32, rhs);
          rf_vector_copy(v50, v31, v17);
          v18 = rf_vector_subtract(destination, v30, v61);
          v19 = rf_vector_subtract(v18, v29, rhs);
          rf_vector_copy(v51, v28, v19);
          rf_renderer_submit_textured_world_polygon_color4_dispatch(
            *(_DWORD *)(dword_193BB9C + 84),
            4,
            (int)v48,
            (int)&v52,
            a6,
            v64);
          scalara = (float)v63;
          v20 = rf_vector_multiply_scalar(vector, v27, scalara);
          v21 = rf_vector_multiply_scalar(v20, v26, a3);
          rf_vector_accumulate(destination, v21);
        }
      }
    }
  }
  return result;
}

