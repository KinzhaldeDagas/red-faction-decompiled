// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505830 rf_trigger_debug_draw_one
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Obtains view reference position via0x4118D0 using pointer at global0x87C640+196, sets render color blue RGBA(0,0,255,150). Shape dword+660==1 draws oriented wire box centered+60 with matrix+72 and full dimensions+712; flags+688 mask0x20 adds white thin box at center+forward(+96)*(depth(+720)/2), dimensions(width,height,0.0001). Shape0 tests geometry obstruction mask3 from view to center and draws wire sphere of radius+120 only when unobstructed. Other shapes draw nothing after color assignment. No restoration of prior render color; return register is branch-dependent, not boolean success.
char __cdecl rf_trigger_debug_draw_one(int a1)
{
  char result; // al
  float *v2; // eax
  float scalar; // [esp+Ch] [ebp-38h]
  int v4; // [esp+10h] [ebp-34h]
  float scaled_result[3]; // [esp+14h] [ebp-30h] BYREF
  float sum_result[3]; // [esp+20h] [ebp-24h] BYREF
  float v7[3]; // [esp+2Ch] [ebp-18h] BYREF
  float v8[3]; // [esp+38h] [ebp-Ch] BYREF

  rf_entity_view_copy_referenced_position(v8, *(_DWORD *)(unk_87C640 + 196));
  rf_render_color_set_rgba8(0, 0, 255, 150);
  result = a1;
  v4 = *(_DWORD *)(a1 + 660);
  if ( v4 )
  {
    if ( v4 == 1 )
    {
      rf_debug_draw_oriented_wire_box(a1 + 60, a1 + 72, a1 + 712, dword_182ABA0);
      result = a1;
      if ( (*(_DWORD *)(a1 + 688) & 0x20) != 0 )
      {
        rf_render_color_set_rgba8(255, 255, 255, 150);
        rf_vector3_set_components_return_destination(v7, *(float *)(a1 + 712), *(float *)(a1 + 716), 0.000099999997);
        scalar = *(float *)(a1 + 720) / 2.0;
        v2 = rf_vector_multiply_scalar((const float *)(a1 + 96), scaled_result, scalar);
        rf_vector_add((const float *)(a1 + 60), sum_result, v2);
        return rf_debug_draw_oriented_wire_box((int)sum_result, a1 + 72, (int)v7, dword_182ABA0);
      }
    }
  }
  else
  {
    result = rf_geometry_segment_is_obstructed(v8, (float *)(a1 + 60), 3, nullptr);
    if ( !result )
      return rf_debug_draw_wire_sphere_backend_dispatch(a1 + 60, *(float *)(a1 + 120), dword_187CC5C);
  }
  return result;
}

