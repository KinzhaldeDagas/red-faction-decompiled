// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB060 rf_event_create_fullscreen_image_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event85 Display_Fullscreen_Image. Load input C-string bitmap through0x574E90(name,-1,1) and store returned handle+0x2B8 including -1 on load failure. Return allocated event regardless of bitmap success; does not publish global selected image during creation.
int __cdecl rf_event_create_fullscreen_image_record(float *a1, char *a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x55u);
  if ( v3 )
    *(_DWORD *)(v3 + 696) = rf_bitmap_load_with_optional_mipmap_generation(a2, (void *)0xFFFFFFFF, 1);
  return v3;
}

