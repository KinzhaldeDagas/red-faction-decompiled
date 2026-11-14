// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B5CD0 rf_scene_model_instance_draw
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Minimal observed ABI THISCALL: ECX state,stack float timeline15,optional position vec3,optional orientation matrix3,RET12. Former fastcall EDX argument was unused and removed; return is unspecified backend/branch residue, sole caller ignores it, declared void. If active BYTE144==0 or state flags28 bit31 set,returns BEFORE copying render transforms. Otherwise nonnull position copies to80 and orientation to92; NULL preserves existing values. Definition subtype140:0 chooses billboard/beam adapter5B5DD0 when flags276&801h,else mesh-face adapter5B5DF0, forwarding float unchanged. Afterwards positive definition handle272 (>0,not>=0) also invokes glow adapter5B5DB0. Subtype1 invokes CHNE ribbon5B5E10 only; others
// do nothing. Does not update geometry,decode flat indices,sort materials or validate pointers/handles.
void __thiscall rf_scene_model_instance_draw(
        char *self,
        float render_time,
        const float *position,
        const float *orientation)
{
  int v4; // [esp+4h] [ebp-14h]
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  if ( *(self + 144) && *((int *)self + 7) >= 0 )
  {
    if ( position )
      rf_vector_copy((float *)self + 20, copy_result, position);
    if ( orientation )
      rf_matrix3_copy((float *)self + 23, orientation);
    v4 = *(_DWORD *)(*(_DWORD *)self + 140);
    if ( v4 )
    {
      if ( v4 == 1 )
        rf_scene_model_instance_draw_chne_ribbon((float *)self);
    }
    else
    {
      if ( (*(_DWORD *)(*(_DWORD *)self + 276) & 0x801) != 0 )
        rf_scene_model_instance_draw_billboard_beam_adapter((float *)self, render_time);
      else
        rf_scene_model_instance_draw_mesh_faces_adapter(self, render_time);
      if ( *(int *)(*(_DWORD *)self + 272) > 0 )
        rf_scene_model_instance_draw_glow_adapter((float *)self);
    }
  }
}

