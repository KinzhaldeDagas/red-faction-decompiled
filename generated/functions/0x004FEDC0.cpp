// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FEDC0 rf_event_give_item_to_player_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_give_item_to_player forward, vtable0x63E118 slot+4. Require global player entity0x681E38 and item definition event+0x2B8!=-1. Build identity orientation and spawn item at player position+0x3C. On successful spawn mark item hidden/inactive, initialize three output ints=-1, then use definition callback at item descriptor+0x48 when non-null, otherwise0x474D10(player id,item id,item+0x2A4,&outputs). Callback return and fallback boolean do not drive further cleanup or rollback in this body; spawning/dispatch alone does not prove item accepted.
void __thiscall rf_event_give_item_to_player_forward(int *this)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // [esp+Ch] [ebp-74h]
  float *v4; // [esp+10h] [ebp-70h]
  float v6[3]; // [esp+24h] [ebp-5Ch] BYREF
  float v7[3]; // [esp+30h] [ebp-50h] BYREF
  float v8[3]; // [esp+3Ch] [ebp-44h] BYREF
  _BYTE v9[36]; // [esp+48h] [ebp-38h] BYREF
  int *v10; // [esp+6Ch] [ebp-14h]
  int v11; // [esp+70h] [ebp-10h] BYREF
  int v12; // [esp+74h] [ebp-Ch] BYREF
  bool v13; // [esp+7Bh] [ebp-5h]
  int v14; // [esp+7Ch] [ebp-4h] BYREF

  if ( dword_681E38 )
  {
    if ( *(this + 174) != -1 )
    {
      v4 = rf_vector3_set_components_return_destination(v8, 0.0, 0.0, 1.0);
      v3 = rf_vector3_set_components_return_destination(v7, 0.0, 1.0, 0.0);
      v1 = rf_vector3_set_components_return_destination(v6, 1.0, 0.0, 0.0);
      v2 = (float *)rf_matrix3_construct_from_three_rows((int)v9, v1, v3, v4);
      v10 = (int *)rf_item_instance_spawn(
                     *(this + 174),
                     (char *)&byte_63D99E,
                     1,
                     -1,
                     (float *)(dword_681E38 + 60),
                     v2,
                     -1,
                     0,
                     0);
      if ( v10 )
      {
        rf_object_mark_hidden_inactive((int)v10);
        v13 = 0;
        v11 = -1;
        v12 = -1;
        v14 = -1;
        if ( *(_DWORD *)(v10[165] + 72) )
          (*(int (__cdecl **)(_DWORD, int, int))(v10[165] + 72))(*(_DWORD *)(dword_681E38 + 44), v10[11], v10[169]);
        else
          v13 = rf_item_apply_default_weapon_or_ammo_pickup(
                  *(_DWORD *)(dword_681E38 + 44),
                  v10[11],
                  v10[169],
                  &v11,
                  &v12,
                  &v14) != 0;
      }
    }
  }
}

