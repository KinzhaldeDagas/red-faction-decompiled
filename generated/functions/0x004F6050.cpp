// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6050 rf_object_apply_queued_model_rebuilds
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Walk queued owner/name pairs0x8900A0/0x890100,count0x894D2C. Runtime types0/1/2/4/7 route to entity animation-table build (rf_entity_build_animation_tables), item0x474210, projectile0x50FAB0, clutter0x415FF0, or corpse0x41E360 model-name receivers respectively; others mark owner deferred-delete. Reset queue count0 at end. This consumer dispatches on owner+0x24, not stored model-kind parallel array0x890040, and has no per-entry success rollback.
int rf_object_apply_queued_model_rebuilds()
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < dword_894D2C; ++i )
  {
    switch ( *(_DWORD *)(dword_8900A0[i] + 36) )
    {
      case 0:
        rf_entity_build_animation_tables(dword_8900A0[i], &unk_890100[32 * i]);
        break;
      case 1:
        rf_item_apply_queued_model_filename(dword_8900A0[i], &unk_890100[32 * i]);
        break;
      case 2:
        rf_object_bind_v3d_or_vfx_model_or_mark_delete(dword_8900A0[i], &unk_890100[32 * i]);
        break;
      case 4:
        rf_clutter_bind_cached_static_model_or_mark_missing(dword_8900A0[i], &unk_890100[32 * i]);
        break;
      case 7:
        rf_corpse_rebind_cached_character_model(dword_8900A0[i], &unk_890100[32 * i]);
        break;
      default:
        rf_object_mark_for_deferred_delete(dword_8900A0[i]);
        break;
    }
    result = i + 1;
  }
  dword_894D2C = 0;
  return result;
}

