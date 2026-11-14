// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004186A0 rf_physical_debris_render_with_lifetime_alpha
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Computes float seconds from signed timer remaining(+676)/1000. Default alpha255; when flags+668 bit1 is clear and ordered seconds<1, truncates seconds*255 toward zero using temporary x87 control-word adjustment and retains only low byte. No lower clamp: negative expired values can wrap; unarmed timer remains opaque. Nonnull backing solid+660 draws only for flags0x10 and passes solid,position+60,orientation+72,alpha as FOUR cdecl DWORD slots to 0x580120; no model fallback when solid exists with flag clear. The wrapper reads and forwards alpha low byte as a fourth argument to room-face submission; the current backend 0x5D75A0 does not read that argument, so solid alpha is ultimately unused (the wrapper previous three-argument
// type was incomplete). With no solid and model+128 nonnull, initializes 80-byte render options, writes alpha DWORD+8, ORs flag0x40 and draws model piece index+664. No index/finite/null-object guard.
int __cdecl rf_physical_debris_render_with_lifetime_alpha(int a1)
{
  int result; // eax
  _DWORD v2[20]; // [esp+10h] [ebp-58h] BYREF
  float v3; // [esp+60h] [ebp-8h]
  unsigned __int8 v4; // [esp+67h] [ebp-1h]

  v4 = -1;
  v3 = (double)rf_replicator_signed_remaining_milliseconds((int *)(a1 + 676)) / 1000.0;
  if ( (*(_DWORD *)(a1 + 668) & 1) == 0 && v3 < 1.0 )
    v4 = (int)(v3 * 255.0);
  result = a1;
  if ( *(_DWORD *)(a1 + 660) )
  {
    if ( (*(_DWORD *)(a1 + 668) & 0x10) != 0 )
      return rf_renderer_submit_room_faces_backend_wrapper(*(_DWORD *)(a1 + 660), (float *)(a1 + 60), a1 + 72, v4);
  }
  else if ( *(_DWORD *)(a1 + 128) )
  {
    rf_model_render_options_construct((char *)v2);
    v2[2] = v4;
    v2[0] |= 0x40u;
    return rf_model_handle_render_indexed_dispatch(
             *(int **)(a1 + 128),
             *(_DWORD *)(a1 + 664),
             a1 + 60,
             (float *)(a1 + 72),
             (int)v2);
  }
  return result;
}

