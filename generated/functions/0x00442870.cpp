// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442870 rf_debug_draw_georegion_registry_shapes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. BYTE6E6AC4==0 returns EAX0; ANY nonzero iterates SIGNED index0 while
// index<DWORD[registry6FC3DC], re-reading current count through486DE0 every condition.552200 returns unchecked backing-slot address; dereference obtains region pointer, whose
// firstDWORD is shape selector. EXACT2 sets RGBA(0,128,0,255), calls57EBB0(center=region+16,radius=FLOATregion64,DWORD187CC5C). EXACT4 sets RGBA(0,255,0,255),
// calls57F0D0(center+16,axes+28,FULLdimensions+68,DWORD182ABA0). Every other selector skips drawing but advances index. No registry/slot/region NULL, bounds beyond live signed count,
// shape-size/finite check, snapshot or draw-result test. Count<=0 executes no region accesses; active-path EAX on exit is count returned by final loop condition, not number drawn.
// Does not restore color; last recognized shape color persists.486DE0 is firstDWORD getter here, not a room resolver despite old contextual label.
int rf_debug_draw_georegion_registry_shapes()
{
  int result; // eax
  float **v1; // eax
  int v2; // [esp+8h] [ebp-Ch]
  float *v3; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  result = unk_6E6AC4;
  if ( unk_6E6AC4 )
  {
    for ( i = 0; ; ++i )
    {
      result = rf_receiver_get_first_dword(rf_geomod_georegion_registry);
      if ( i >= result )
        break;
      v1 = (float **)sub_552200(rf_geomod_georegion_registry, i);
      v3 = *v1;
      v2 = *(_DWORD *)*v1;
      if ( v2 == 2 )
      {
        rf_render_color_set_rgba8(0, 128, 0, 255);
        rf_debug_draw_wire_sphere_backend_dispatch((int)(v3 + 4), v3[16], dword_187CC5C);
      }
      else if ( v2 == 4 )
      {
        rf_render_color_set_rgba8(0, 255, 0, 255);
        rf_debug_draw_oriented_wire_box((int)(v3 + 4), (int)(v3 + 7), (int)(v3 + 17), dword_182ABA0);
      }
    }
  }
  return result;
}

