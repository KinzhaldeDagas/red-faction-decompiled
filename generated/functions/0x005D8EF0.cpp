// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D8EF0 rf_renderer_draw_instance_material_billboard_or_beam
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments instance,time. Resolves material through definition nested indices and200-byte materialtable; evaluates alpha. Definitionflags+276 bit1 chooses billboard,else bit0x800 chooses beam; other flags draw nothing. Billboard transforms instanceposition+4 through matrix+92 then adds translation+80 and globaloffset0xA5A0EC. Materialbyte+8 chooses glow vs standardbillboardstate. Definitionnested+204->float+32 nonnegative chooses explicitwidth/height from instance+16/+20; negative chooses aspectbillboard with size definition+160. MaterialmodeDWORD0 selects firsttexture slot+16,whiteRGB,evaluatedalpha*255 rounded; mode1 performs two draws with crossfade weights1-f/f,texture slots+16/+68,RGBweights*255 and alpha*weight*255. Other modes skip drawing. Beam branch constructs endpoints localposition +/-
// definitiondirection+280*instanceheight/2,transforms both,and draws camera-facingbeam with instancewidth and glowstate; supports same materialmodes0/1 and weightedcolor logic. No materialindex,range or ownership validation; leaves color/textures changed. Returned byte may be incidental on skipped paths,not reliable success.
char __cdecl rf_renderer_draw_instance_material_billboard_or_beam(float *a1, float a2)
{
  float *v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v19; // [esp+Ch] [ebp-C0h]
  int v20; // [esp+Ch] [ebp-C0h]
  int v21; // [esp+Ch] [ebp-C0h]
  int v22; // [esp+Ch] [ebp-C0h]
  float v23; // [esp+10h] [ebp-BCh]
  float v24; // [esp+14h] [ebp-B8h]
  float v25; // [esp+18h] [ebp-B4h]
  float v26; // [esp+20h] [ebp-ACh]
  float v27; // [esp+24h] [ebp-A8h]
  float v28; // [esp+28h] [ebp-A4h]
  float v29[3]; // [esp+30h] [ebp-9Ch] BYREF
  float v30[3]; // [esp+3Ch] [ebp-90h] BYREF
  float v31[3]; // [esp+48h] [ebp-84h] BYREF
  float v32[3]; // [esp+54h] [ebp-78h] BYREF
  float v33[3]; // [esp+60h] [ebp-6Ch] BYREF
  float scaled_result[3]; // [esp+6Ch] [ebp-60h] BYREF
  float sum_result[3]; // [esp+78h] [ebp-54h] BYREF
  float v36; // [esp+84h] [ebp-48h]
  float v37; // [esp+88h] [ebp-44h]
  float v38[3]; // [esp+8Ch] [ebp-40h] BYREF
  float out_vector[3]; // [esp+98h] [ebp-34h] BYREF
  float v40; // [esp+A4h] [ebp-28h]
  float v41; // [esp+A8h] [ebp-24h]
  int v42[3]; // [esp+ACh] [ebp-20h] BYREF
  unsigned int v43; // [esp+B8h] [ebp-14h] BYREF
  float v44; // [esp+BCh] [ebp-10h]
  int v45; // [esp+C0h] [ebp-Ch]
  int v46; // [esp+C4h] [ebp-8h]
  int *v47; // [esp+C8h] [ebp-4h]

  v46 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 184) + 32);
  v45 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 192) + 4 * v46);
  v47 = (int *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 132) + 140) + 200 * v45);
  v44 = rf_material_evaluate_alpha(v47, a2);
  if ( (*(_DWORD *)(*(_DWORD *)a1 + 276) & 1) != 0 )
  {
    rf_vector3_copy_return_destination((float *)v42, a1 + 1);
    rf_vector_rotate_by_matrix3((float *)v42, a1 + 23);
    v2 = rf_vector_add(a1 + 20, sum_result, &flt_A5A0EC);
    rf_vector_accumulate((float *)v42, v2);
    rf_dword_construct_invalid_minus_one(&v43);
    if ( *((_BYTE *)v47 + 8) )
      v43 = LODWORD(rf_particle_glow_billboard_render_state);
    else
      v43 = rf_particle_standard_billboard_render_state;
    v3 = *v47;
    if ( *v47 )
    {
      if ( *v47 != 1 )
        return v3;
      v41 = rf_material_evaluate_texture_crossfade(v47, a2);
      v40 = 1.0 - v41;
      v6 = rf_material_texture_slot_select_frame((int)(v47 + 4), a2);
      rf_renderer_set_pending_texture_handles(v6, -1);
      v27 = v44 * 255.0 * v40;
      v19 = rf_round_nonnegative_float_to_int(v27);
      rf_render_color_set_rgba8((int)(v40 * 255.0), (int)(v40 * 255.0), (int)(v40 * 255.0), v19);
      if ( *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 204) + 32) >= 0.0 )
        rf_renderer_draw_world_billboard_rectangle((float *)v42, 0.0, a1[4], a1[5], v43);
      else
        rf_renderer_draw_world_billboard_aspect((float *)v42, 0.0, *(float *)(*(_DWORD *)a1 + 160), v43);
      v7 = rf_material_texture_slot_select_frame((int)(v47 + 17), a2);
      rf_renderer_set_pending_texture_handles(v7, -1);
      v26 = v44 * 255.0 * v41;
      v20 = rf_round_nonnegative_float_to_int(v26);
      rf_render_color_set_rgba8((int)(v41 * 255.0), (int)(v41 * 255.0), (int)(v41 * 255.0), v20);
      if ( *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 204) + 32) >= 0.0 )
        goto LABEL_15;
    }
    else
    {
      v4 = rf_material_texture_slot_select_frame((int)(v47 + 4), a2);
      rf_renderer_set_pending_texture_handles(v4, -1);
      v28 = v44 * 255.0;
      v5 = rf_round_nonnegative_float_to_int(v28);
      rf_render_color_set_rgba8(255, 255, 255, v5);
      if ( *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 204) + 32) >= 0.0 )
      {
LABEL_15:
        LOBYTE(v3) = rf_renderer_draw_world_billboard_rectangle((float *)v42, 0.0, a1[4], a1[5], v43);
        return v3;
      }
    }
    LOBYTE(v3) = rf_renderer_draw_world_billboard_aspect((float *)v42, 0.0, *(float *)(*(_DWORD *)a1 + 160), v43);
  }
  else
  {
    v3 = *(_DWORD *)(*(_DWORD *)a1 + 276) & 0x800;
    if ( v3 )
    {
      v8 = rf_vector_multiply_scalar((const float *)(*(_DWORD *)a1 + 280), scaled_result, a1[5]);
      v9 = rf_vector_multiply_scalar(v8, v33, 0.5);
      rf_vector_add(a1 + 1, v38, v9);
      rf_vector_rotate_by_matrix3(v38, a1 + 23);
      v10 = rf_vector_add(a1 + 20, v32, &flt_A5A0EC);
      rf_vector_accumulate(v38, v10);
      v11 = rf_vector_multiply_scalar((const float *)(*(_DWORD *)a1 + 280), v31, a1[5]);
      v12 = rf_vector_multiply_scalar(v11, v30, 0.5);
      rf_vector_subtract(a1 + 1, out_vector, v12);
      rf_vector_rotate_by_matrix3(out_vector, a1 + 23);
      v13 = rf_vector_add(a1 + 20, v29, &flt_A5A0EC);
      rf_vector_accumulate(out_vector, v13);
      LOBYTE(v3) = (_BYTE)v47;
      if ( *v47 )
      {
        if ( *v47 == 1 )
        {
          v37 = rf_material_evaluate_texture_crossfade(v47, a2);
          v36 = 1.0 - v37;
          v16 = rf_material_texture_slot_select_frame((int)(v47 + 4), a2);
          rf_renderer_set_pending_texture_handles(v16, -1);
          v24 = v44 * 255.0 * v36;
          v21 = rf_round_nonnegative_float_to_int(v24);
          rf_render_color_set_rgba8((int)(v36 * 255.0), (int)(v36 * 255.0), (int)(v36 * 255.0), v21);
          rf_renderer_draw_camera_facing_beam_quad(
            v38,
            out_vector,
            a1[4],
            SLODWORD(rf_particle_glow_billboard_render_state));
          v17 = rf_material_texture_slot_select_frame((int)(v47 + 17), a2);
          rf_renderer_set_pending_texture_handles(v17, -1);
          v23 = v44 * 255.0 * v37;
          v22 = rf_round_nonnegative_float_to_int(v23);
          rf_render_color_set_rgba8((int)(v37 * 255.0), (int)(v37 * 255.0), (int)(v37 * 255.0), v22);
          LOBYTE(v3) = rf_renderer_draw_camera_facing_beam_quad(
                         v38,
                         out_vector,
                         a1[4],
                         SLODWORD(rf_particle_glow_billboard_render_state));
        }
      }
      else
      {
        v14 = rf_material_texture_slot_select_frame((int)(v47 + 4), a2);
        rf_renderer_set_pending_texture_handles(v14, -1);
        v25 = v44 * 255.0;
        v15 = rf_round_nonnegative_float_to_int(v25);
        rf_render_color_set_rgba8(255, 255, 255, v15);
        LOBYTE(v3) = rf_renderer_draw_camera_facing_beam_quad(
                       v38,
                       out_vector,
                       a1[4],
                       SLODWORD(rf_particle_glow_billboard_render_state));
      }
    }
  }
  return v3;
}

