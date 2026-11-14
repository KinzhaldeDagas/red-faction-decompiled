// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437410 sub_437410
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Role correction: this activation/setup helper is NOT speech teardown merely because an old export key called it entity_cleanup. It writes retained speech handle1400=-1 and actionhandle1404=-1 at437473/480 without a speech-stop call. Other activation work includes OBB/climb,model/VFX,geometry and headlamp initialization. Do not invent a stop/countdown reset from that export label.
void __cdecl sub_437410(int a1)
{
  _DWORD *instance; // eax
  int **v2; // eax
  int *v3; // eax
  int *v4; // eax
  int v5; // [esp-4h] [ebp-28h]
  char v6; // [esp+0h] [ebp-24h]
  int attached_to_model_prop; // [esp+14h] [ebp-10h]
  _DWORD *v8; // [esp+18h] [ebp-Ch]
  _DWORD *containing_point; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]
  int j; // [esp+20h] [ebp-4h]

  containing_point = (_DWORD *)rf_world_obb_region_find_containing_point(a1 + 60);
  if ( containing_point )
    rf_entity_install_custom_movement2(a1, containing_point);
  *(float *)(a1 + 5044) = 1.0;
  *(_DWORD *)(a1 + 4984) = -1;
  *(_DWORD *)(a1 + 2060) = -1;
  *(_DWORD *)(a1 + 2052) = -1;
  *(_DWORD *)(a1 + 5120) = -1;
  *(_DWORD *)(a1 + 5124) = -1;
  *(_DWORD *)(a1 + 5232) = 0;
  if ( *(_DWORD *)(a1 + 5168) )
    *(float *)(*(_DWORD *)(a1 + 5168) + 4564) = 0.0;
  v8 = *(_DWORD **)(a1 + 660);
  for ( i = 0; i < v8[413]; ++i )
  {
    if ( (char *)&v8[8 * i + 157] + strlen((const char *)&v8[8 * i + 157]) + 1 == (char *)&v8[8 * i + 157] + 1 )
    {
      rf_pointer_array_append_dword((_DWORD *)(a1 + 2264), 0);
    }
    else
    {
      instance = rf_vfx_load_instance((char *)&v8[8 * i + 157], (int)byte_98967F);
      rf_pointer_array_append_dword((_DWORD *)(a1 + 2264), (int)instance);
      v2 = (int **)sub_552200((_DWORD *)(a1 + 2264), i);
      rf_model_handle_set_cyclic_mix_adapter(*v2, 0, 1.0);
    }
  }
  for ( j = 0; j < rf_receiver_get_first_dword(v8 + 414); ++j )
  {
    if ( *(int *)rf_inline_dword_array4_element_address_unchecked(v8 + 423, j) >= 0
      && *(int *)rf_inline_dword_array4_element_address_unchecked(v8 + 414, j) >= 0 )
    {
      v3 = (int *)rf_inline_dword_array4_element_address_unchecked(v8 + 423, j);
      v6 = rf_inline_pointer_array_find_first(v8 + 432, *v3) > -1;
      v5 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked(v8 + 423, j);
      v4 = (int *)rf_inline_dword_array4_element_address_unchecked(v8 + 414, j);
      attached_to_model_prop = rf_glare_create_attached_to_model_prop(*(_DWORD *)(a1 + 44), *v4, v5, v6);
      if ( attached_to_model_prop )
        rf_pointer_array_append_dword((_DWORD *)(a1 + 5144), attached_to_model_prop);
    }
  }
  if ( *(_DWORD *)(dword_681E38 + 512) == *(_DWORD *)(a1 + 44) )
    rf_entity_disable_headlamp_recursive((_DWORD *)a1);
}

