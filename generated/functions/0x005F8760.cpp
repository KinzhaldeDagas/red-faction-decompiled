// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F8760 rf_scene_frame_channel_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 224-byte channel definition:common scene-node initializer clears name0,name65,owner132. Then writes literal Unknown plus NUL at name0 and name65 using two DWORD stores each;frameCount216=0,framePointer220=NULL. Does NOT initialize kind212,cache links136/140,source name144 or remaining name bytes. No allocation;not full zero-init.
void __thiscall rf_scene_frame_channel_construct(_DWORD *this)
{
  rf_scene_node_clear_names_and_link(this);
  *this = 1852534357;
  *(this + 1) = &unk_6E776F;
  *(_DWORD *)((char *)this + 65) = 1852534357;
  *(_DWORD *)((char *)this + 69) = &unk_6E776F;
  *(this + 54) = 0;
  *(this + 55) = 0;
}

