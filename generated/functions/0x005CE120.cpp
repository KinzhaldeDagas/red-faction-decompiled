// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE120 rf_scene_instance_draw_flat_object
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): If inactive flag0x4 and draw-override flag0x8 clear,returns. Decodes flat index via5CDFF0. Type1 draws one particle using emitter state+28,stride164,selected particle slot and currentFrame16. Type0 draws model state+20,stride152 only if not draining or override0x8; forwards current frame and supplied origin/orientation to model renderer5B5CD0. Types2/3/4 do nothing. Does not validate index,array pointers,particle count or transform pointers.
void __thiscall rf_scene_instance_draw_flat_object(void *this, int a2, float *position, float *orientation)
{
  int v5; // [esp+14h] [ebp-Ch] BYREF
  int v6; // [esp+18h] [ebp-8h] BYREF
  int v7; // [esp+1Ch] [ebp-4h] BYREF

  if ( ((*(_DWORD *)this >> 2) & 1) == 0 || ((*(_DWORD *)this >> 3) & 1) != 0 )
  {
    rf_scene_definition_decode_flat_object_index(*((_DWORD **)this + 2), a2, &v7, &v6, &v5);
    if ( v7 )
    {
      if ( v7 == 1 )
        rf_particle_instance_draw_one((float *)(*((_DWORD *)this + 7) + 164 * v6), v5, *((float *)this + 4));
    }
    else if ( (*(_DWORD *)this & 1) == 0 || ((*(_DWORD *)this >> 3) & 1) != 0 )
    {
      rf_scene_model_instance_draw(
        (char *)(*((_DWORD *)this + 5) + 152 * a2),
        *((float *)this + 4),
        position,
        orientation);
    }
  }
}

