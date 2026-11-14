// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2710 rf_scene_model_definition292_construct_defaults
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): Thiscall292-byte model definition. Base5963D0 only clears name first bytes0/65 and owner132, then no-op vector defaults at148/228/256/280 leave those vectors uninitialized; float4 at240 set(0,0,0,1). Writes Unknown plus NUL to BOTH fixed name starts0 and65 using two DWORD literal copies each (second immediate006E776F is ASCII own+NUL, not a code pointer). Owner132=0; model handle144=-1; clears ONLY bit0 of WORD136, preserving other bits; float160=0. Sets DWORDs164,180,184,196,200,204,208,212,216,220,224,276=0 and DWORD272=-1. Does NOT initialize material-reference count188 or pointer192; loader postprocess reads them even for declared model slots lacking SFXO/CHNE chunks. Does not allocate arrays, zero
// whole object or release old pointers. EAX receiver at return despite current void declaration. Deletion5B28C0 releases only owned pointers208/216; other arrays are borrowed scene pools.
void __thiscall rf_scene_model_definition292_construct_defaults(char *this)
{
  rf_scene_node_clear_names_and_link(this);
  rf_vector3_default_construct_noop(this + 148);
  rf_vector3_default_construct_noop(this + 228);
  rf_float4_construct_zero_zero_zero_one((float *)this + 60);
  rf_vector3_default_construct_noop(this + 256);
  rf_vector3_default_construct_noop(this + 280);
  *((_DWORD *)this + 33) = 0;
  *(_DWORD *)this = 1852534357;
  *((_DWORD *)this + 1) = &unk_6E776F;
  *(_DWORD *)(this + 65) = 1852534357;
  *(_DWORD *)(this + 69) = &unk_6E776F;
  *((_DWORD *)this + 36) = -1;
  *((_WORD *)this + 68) &= ~1u;
  *((float *)this + 40) = 0.0;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 51) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 49) = 0;
  *((_DWORD *)this + 50) = 0;
  *((_DWORD *)this + 68) = -1;
  *((_DWORD *)this + 69) = 0;
  *((_DWORD *)this + 52) = 0;
  *((_DWORD *)this + 53) = 0;
  *((_DWORD *)this + 54) = 0;
  *((_DWORD *)this + 55) = 0;
  *((_DWORD *)this + 56) = 0;
}

