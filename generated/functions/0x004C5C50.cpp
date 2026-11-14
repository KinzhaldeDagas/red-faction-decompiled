// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5C50 rf_glass_shard_system_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl no args. Sets free headNULL,activeCount0,bucketCount0, links384 preallocated200B records at823BD0 into circular FREE list (next0/prev4), preserving payload8..199. Clears64
// owner-key/head pairs stride8. No memset of shard payload, destruction of prior live shards or resource release. Resolves Glass Smash/Glass Drop Foley names through temporary
// RFStrings, destroys temporary strings; no failure checks. Zeros ten saved drop voices,position sum and speed sum, clears broken-face registry823B68 COUNT only (keeps backing),
// loads big_glassblast_A.tga with(-1,1) flags into shared texture handle. Calls empty4C5ED0 hook and writes DWORD8222F4=0. Does NOT reset accumulated impact count or shared sound
// deadline822764, stop previously playing voices, free old bitmap or initialize shard timers. Exception cleanup destroys currently constructed RFString; no pool rollback.
void rf_glass_shard_system_init()
{
  char *v0; // eax
  char *v1; // eax
  std::exception *v2; // [esp+4h] [ebp-30h]
  std::exception *v3; // [esp+Ch] [ebp-28h]
  _DWORD v4[2]; // [esp+14h] [ebp-20h] BYREF
  _DWORD v5[2]; // [esp+1Ch] [ebp-18h] BYREF
  int i; // [esp+24h] [ebp-10h]
  int v7; // [esp+30h] [ebp-4h]

  rf_glass_shard_free_head = 0;
  rf_glass_shard_active_count = 0;
  rf_glass_shard_bucket_count = 0;
  for ( i = 0; i < 384; ++i )
  {
    if ( rf_glass_shard_free_head )
    {
      unk_823BD4[50 * i] = *(_DWORD *)(rf_glass_shard_free_head + 4);
      rf_glass_shard_pool[50 * i] = rf_glass_shard_free_head;
      **(_DWORD **)(rf_glass_shard_free_head + 4) = &rf_glass_shard_pool[50 * i];
      *(_DWORD *)(rf_glass_shard_free_head + 4) = &rf_glass_shard_pool[50 * i];
    }
    else
    {
      rf_glass_shard_pool[50 * i] = (int)&rf_glass_shard_pool[50 * i];
      unk_823BD4[50 * i] = (int)&rf_glass_shard_pool[50 * i];
      rf_glass_shard_free_head = &rf_glass_shard_pool[50 * i];
    }
  }
  for ( i = 0; i < 64; ++i )
  {
    rf_glass_shard_bucket_keys[2 * i] = 0;
    rf_glass_shard_bucket_heads[2 * i] = 0;
  }
  v3 = (std::exception *)rf_string_construct_from_cstr(v5, "Glass Smash");
  v7 = 0;
  v0 = (char *)rf_string_object_c_str_or_empty(v3);
  rf_glass_smash_foley_id = rf_foley_definition_find_name(v0);
  v7 = -1;
  rf_string_destroy_buffer(v5);
  v2 = (std::exception *)rf_string_construct_from_cstr(v4, "Glass Drop");
  v7 = 1;
  v1 = (char *)rf_string_object_c_str_or_empty(v2);
  rf_glass_drop_foley_id = rf_foley_definition_find_name(v1);
  v7 = -1;
  rf_string_destroy_buffer(v4);
  for ( i = 0; i < 10; ++i )
    rf_glass_drop_sound_channels[i] = 0;
  rf_vector3_zero_return_destination(rf_glass_frame_impact_position_sum);
  rf_glass_frame_impact_speed_sum = 0.0;
  rf_pointer_array_clear_count_keep_storage(unk_823B68);
  rf_glass_blast_texture_handle = rf_bitmap_load_with_optional_mipmap_generation(aBigGlassblastA, (void *)0xFFFFFFFF, 1);
  sub_4C5ED0();
  unk_8222F4 = 0;
}

