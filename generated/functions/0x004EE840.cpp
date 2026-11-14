// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EE840 rf_fplegs_load_model_and_animation_handles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Loads parker_enviro_legs with flags1,0 into663038 and gets definition without own NULL checks. Iterates six filename pointers663020: parker_lowerbody_stand.mvf, walk.mvf, run.mvf, crouch.mvf, crouch_walk.mvf, freefall.mvf (all with parker_lowerbody_ prefix). Constructs virtual file, opens mode1/context98967F; negative result stores handle-1, otherwise closes then animation-registry-loads(definition,filename,1,0) into87FBDC[i]. Destructs file each iteration and on SEH cleanup. Finally gets runtime pointer (incidental EAX) and sets current state66303C=0. Does not initialize pending663040 or blend duration/elapsed87FBF8/FC, play animation or register teardown. No current code callers.
int rf_fplegs_load_model_and_animation_handles()
{
  int v0; // eax
  int result; // eax
  int self[70]; // [esp+4h] [ebp-134h] BYREF
  int i; // [esp+124h] [ebp-14h]
  _DWORD *definition_pointer; // [esp+128h] [ebp-10h]
  int v5; // [esp+134h] [ebp-4h]

  dword_663038 = (int)rf_model_handle_load_character_instance("parker_enviro_legs", 1, 0);
  definition_pointer = (_DWORD *)rf_model_handle_get_definition_pointer(dword_663038);
  for ( i = 0; i < 6; ++i )
  {
    rf_vfile_construct_unopened(self);
    v5 = 0;
    if ( rf_vfile_open_with_extension_cache_control_paths(self, (&off_663020)[i], 1, byte_98967F) < 0 )
    {
      dword_87FBDC[i] = -1;
    }
    else
    {
      rf_vfile_close_stdio_or_vpp(self);
      v0 = rf_animation_registry_load(definition_pointer, (int)(&off_663020)[i], 1u, 0);
      dword_87FBDC[i] = v0;
    }
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
  }
  result = rf_model_handle_get_runtime_pointer((int *)dword_663038);
  dword_66303C = 0;
  return result;
}

